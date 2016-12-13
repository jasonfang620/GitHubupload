#include"EmptyScene.h"
#include <nclgl\Vector4.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\SceneManager.h>
#include <ncltech\CommonUtils.h>
#include <sstream>
#include <ncltech\ObjectMesh.h>
#include <ncltech\SphereCollisionShape.h>
#include <ncltech\CuboidCollisionShape.h>
#include <ncltech\NCLDebug.h>
#include <algorithm>

using namespace CommonUtils;


const Vector4 status_colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

EmptyScene::EmptyScene(const std::string& friendly_name)
	: Scene(friendly_name)
	, m_AccumTime(0.0f)
	, m_pPlayer(NULL), m_Rotating(true),m_MeshHouse(NULL), m_pServerConnection(NULL)
	, m_pObj(NULL)
{
	m_MeshHouse = new OBJMesh(MESHDIR"house.obj");
	glGenTextures(1, &m_whiteTexture);
	glBindTexture(GL_TEXTURE_2D, m_whiteTexture);
	int white_pixel = 0xFFFFFFFF;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, &white_pixel);


}

EmptyScene::~EmptyScene() {
	if (m_MeshHouse)
	{
		m_MeshHouse->SetTexture(NULL);
		delete m_MeshHouse;
		m_MeshHouse = NULL;
	}
	if (m_whiteTexture)
	{
		glDeleteTextures(1, &m_whiteTexture);
		m_whiteTexture = NULL;
	}
}
const Vector3 ss_pos = Vector3(0.0f, 0.0f, 0.0f);

void EmptyScene::OnInitializeScene() {

	//Initialize Client Network
	if (m_Network.Initialize(0))
	{
		NCLDebug::Log("Network: Initialized!");

		//Attempt to connect to the server on localhost:1234
		m_pServerConnection = m_Network.ConnectPeer(127, 0, 0, 1, 1234);
		NCLDebug::Log("Network: Attempting to connect to server.");
	}


	//PhysicsEngine::Instance()->SetPaused(false);
	PhysicsEngine::Instance()->SetDebugDrawFlags(DEBUGDRAW_FLAGS_COLLISIONNORMALS | DEBUGDRAW_FLAGS_COLLISIONVOLUMES);
	SceneManager::Instance()->GetCamera()->SetPosition(Vector3(40.0f, 10.0f, 40.0f));
	SceneManager::Instance()->GetCamera()->SetYaw(45.f);
	SceneManager::Instance()->GetCamera()->SetPitch(0.f);

	//PhysicsEngine::Instance()->SetDebugDrawFlags(DEBUGDRAW_FLAGS_CONSTRAINT);
	m_AccumTime = 0.0f;
	m_Rotating = true;
	m_pObj = CommonUtils::BuildCuboidObjectGroud(
		"target",
		ss_pos + Vector3(0.0f, 25.f, 0.0f),
		Vector3(0.2f, 5.f, 5.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(0.2f, 0.5f, 1.0f, 1.0f));

	this->AddGameObject(m_pObj);

	//add special cube
	{
	Object* plant1 = CommonUtils::BuildPlantObject(
		"Plant1",
		ss_pos + Vector3(5.0f, 0.f, -45.0f),
		Vector3(5.f, 5.0f, 0.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(.7f, 0.5f, 1.0f, 1.0f));
	this->AddGameObject(plant1);
	Object* Plant1 = this->FindGameObject("Plant1");
	Plant1->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0.0f, 0.0f, 0.0f));

	Object* plant2 = CommonUtils::BuildPlantObject(
		"Plant2",
		ss_pos + Vector3(5.0f, 0.f, -55.0f),
		Vector3(5.f, 5.0f, 0.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(.7f, 0.5f, 1.0f, 1.0f));


	this->AddGameObject(plant2);
	Object* Plant2 = this->FindGameObject("Plant2");
	Plant2->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-180.0f, .0f, 0.0f));

	Object* plant3 = CommonUtils::BuildPlantObject(
		"Plant3",
		ss_pos + Vector3(5.0f, 5.f, -50.0f),
		Vector3(5.f, 5.0f, 0.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(.7f, 0.5f, 1.0f, 1.0f));
	this->AddGameObject(plant3);
	Object* Plant3 = this->FindGameObject("Plant3");
	Plant3->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(270.0f, .0f, 0.0f));

	Object* plant4 = CommonUtils::BuildPlantObject(
		"Plant4",
		ss_pos + Vector3(5.0f, -5.f, -50.0f),
		Vector3(5.f, 5.0f, 0.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(.7f, 0.5f, 1.0f, 1.0f));


	this->AddGameObject(plant4);
	Object* Plant4 = this->FindGameObject("Plant4");
	Plant4->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(-270.0f, .0f, 0.0f));

	Object* plant5 = CommonUtils::BuildPlantObject(
		"Plant5",
		ss_pos + Vector3(10.0f, 0.f, -50.0f),
		Vector3(5.f, 5.0f, 0.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(.7f, 0.5f, 1.0f, 1.0f));


	this->AddGameObject(plant5);
	Object* Plant5 = this->FindGameObject("Plant5");
	Plant5->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0.0f, 90.0f, 0.0f));

	Object* plant6 = CommonUtils::BuildPlantObject(
		"Plant6",
		ss_pos + Vector3(0.0f, 0.f, -50.0f),
		Vector3(5.f, 5.0f, 0.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(.7f, 0.5f, 1.0f, 1.0f));


	this->AddGameObject(plant6);
	Object* Plant6 = this->FindGameObject("Plant6");
	Plant6->Physics()->SetOrientation(Quaternion::EulerAnglesToQuaternion(0.0f, -90.0f, 0.0f));


	}


	//m_pObj = CommonUtils::BuildCuboidObject(
	//	"Server",
	//	Vector3(0.0f, 0.0f, 25.0f),
	//	Vector3(0.5f, 0.5f, 0.5f),
	//	true,									//Physics Enabled here Purely to make setting position easier via Physics()->SetPosition()
	//	0.0f,
	//	false,
	//	false,
	//	Vector4(0.2f, 0.5f, 1.0f, 1.0f));
	//this->AddGameObject(m_pObj);



	//balls tower
	int balls_num = 0;

	ostringstream balls_name;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0;j < 3;++j)
		{
			
			Vector4 colour = CommonUtils::GenColour(0.7f + i * 0.05f, 1.0f);
			balls_name << "ballname" << balls_num;

			Object* obj = CommonUtils::BuildSphereObject(
				balls_name.str().c_str(),
				Vector3(-50.0f + i * 1.25f, j*1.25f +5.5f, 6.0f),
				0.5f,
				true,
				1.0f,
				true,
				false,
				colour);
			obj->Physics()->SetFriction(0.1f);
			obj->Physics()->SetElasticity(i * 0.1f + 0.5f);
			this->AddGameObject(obj);
			Object* balltower = this->FindGameObject(balls_name.str().c_str());
			balltower->Physics()->Setstate(true);
			
		}
	}
	
	//cube tower
	int box_num = 0;

	ostringstream box_name;

	for (int x = 0; x < 3; ++x)
	{
		for (int y = 0; y < 3; ++y){
			
			uint idx = x * 5 + y;
			Vector4 colour = GenColour(idx / 10.f, 0.5f);
			//Vector3 pos = Vector3(x - y * 0.5f+40.f, 0.5f + float(6 - 1 - y), -0.5f+15.f);
			Vector3 pos = Vector3(50.0f + x * 1.25f, y*1.25f + 5.5f,  6.0f);
			box_name << "boxname" << box_num;

			
			Object* cube = CommonUtils::BuildCuboidObject(
				box_name.str().c_str(),
				pos,					// Position
				Vector3(0.5f,0.5f,0.5f),				// Half-Dimensions
				true,
				0.1f,
				true,
				false,
				colour);
			
			cube->Physics()->SetFriction(1.0f);
			//cube->Physics()->SetElasticity(0.0f);	
			this->AddGameObject(cube);
			Object* cubetower = this->FindGameObject(box_name.str().c_str());
			cubetower->Physics()->Setstate(true);
		
			}
		}

	//big ball
	Object* ballF=CommonUtils::BuildSphereObject(
		"BallF",
		ss_pos,
		20.0f, 
		true, 
		0.0f, 
		true, 
		false,
		Vector4(0.6f, 0.6f, 0.6f, 1.0f));
	
		this->AddGameObject(ballF);

	//small ball
	Object* ballS=CommonUtils::BuildSphereObject1(
		"BallS",
		Vector3(20.f, 0.0f, 20.0f),
		1.25f,
		true,
		1.0f,
		true,
		true,
		Vector4(0.0f, 0.6f, 0.6f, 1.0f));
		
		this->AddGameObject(ballS);


		//DistanceConstraint* constraint = new DistanceConstraint(
		//	ballF->Physics(),					//Physics Object A
		//	ballS->Physics(),					//Physics Object B
		//	ballF->Physics()->GetPosition(),	//Attachment Position on Object A	-> Currently the centre
		//	ballS->Physics()->GetPosition());	//Attachment Position on Object B	-> Currently the centre  
		//PhysicsEngine::Instance()->AddConstraint(constraint);

		/*Create Some Objects*/
		{
			const Vector3 col_size = Vector3(2.0f, 2.f, 2.f);
			ObjectMesh* obj = new ObjectMesh("House");
			obj->SetLocalTransform(Matrix4::Translation(Vector3(0.0f, -0.71f, 0.0f)) * Matrix4::Scale(Vector3(2.0f, 2.0f, 2.f)));	//Translation here to move the mesh down, as it not centred on the origin *cry*
			obj->SetMesh(m_MeshHouse, false);
			obj->SetTexture(m_whiteTexture, false);
			obj->SetColour(Vector4(0.8f, 0.3f, 0.1f, 1.0f));
			obj->SetBoundingRadius(col_size.Length());
			obj->CreatePhysicsNode();
			obj->Physics()->SetPosition(ss_pos + Vector3(5.0f, -2.0f, -50.0f));
			obj->Physics()->SetCollisionShape(new CuboidCollisionShape(col_size));
			obj->Physics()->Setstate(true);


			obj->Physics()->SetOnCollisionCallback([](PhysicsObject* self, PhysicsObject* collidingObject) {
				NCLDebug::Log("You are inside the house!");

				//Returns false if the collision should /not/ be handled with a standard collision response (tut 6)
				//Returns true to handle collision as normal
				return false;
			});

			this->AddGameObject(obj);
		}



}

void EmptyScene::OnCleanupScene()
{
	//Just delete all created game objects 
	//  - this is the default command on any Scene instance so we don't really need to override this function here.
	Scene::OnCleanupScene();

	m_pObj = NULL; // Deleted in above function

				   //Send one final packet telling the server we are disconnecting
				   // - We are not waiting to resend this, so if it fails to arrive
				   //   the server will have to wait until we time out naturally
	enet_peer_disconnect_now(m_pServerConnection, 0);

	//Release network and all associated data/peer connections
	m_Network.Release();
	m_pServerConnection = NULL;
}

void EmptyScene::OnUpdateScene(float dt) {
	static int n = 0;
	Scene::OnUpdateScene(dt);

	// You can add status entries to the top left from anywhere in the program
	//NCLDebug::AddStatusEntry(Vector4(1.0f, 0.2f, 0.2f, 1.0f), "Welcome to the Game Tech Framework!");
	//NCLDebug::AddStatusEntry(Vector4(1.0f, 0.4f, 0.4f, 1.0f), "   \x01 You can move the black car with the arrow keys");

	// You can print text using 'printf' formatting
	//bool donkeys = false;
	//NCLDebug::AddStatusEntry(Vector4(1.0f, 0.4f, 0.4f, 1.0f), "   \x01 The %s in this scene are dragable", donkeys ? "donkeys" : "cubes");

	/*bool drawConstraints = PhysicsEngine::Instance()->GetDebugDrawFlags() & DEBUGDRAW_FLAGS_CONSTRAINT;*/
	//NCLDebug::AddStatusEntry(Vector4(1.0f, 0.9f, 0.8f, 1.0f), "Physics:");
	//NCLDebug::AddStatusEntry(Vector4(1.0f, 0.9f, 0.8f, 1.0f), "     Draw Constraints : %s (Press C to toggle)", drawConstraints ? "Enabled" : "Disabled");

	//if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_C))
	//{
	//	drawConstraints = !drawConstraints;
	//}

	//PhysicsEngine::Instance()->SetDebugDrawFlags(drawConstraints ? DEBUGDRAW_FLAGS_CONSTRAINT : NULL);
	uint drawFlags = PhysicsEngine::Instance()->GetDebugDrawFlags();

	if (m_Rotating)
	{
		m_AccumTime += dt;
		Object* orbiting_sphere1 = this->FindGameObject("BallF");
		if (orbiting_sphere1 != NULL)
		{
			//Move orbiting sphere1 around centre object at 45 degrees per second with an orbiting radius of 75cm
			orbiting_sphere1->Physics()->SetAngularVelocity(Vector3(0.f, 0.5f, 0.f));
		}
		Object* orbiting_sphere2 = this->FindGameObject("BallS");
		if (orbiting_sphere2 != NULL)
		{
			//Move orbiting sphere1 around centre object at 45 degrees per second with an orbiting radius of 75cm
			orbiting_sphere2->Physics()->SetPosition(Vector3(
				ss_pos.x + 50*cos(DegToRad(m_AccumTime * 10.0f) * 2.f) * 0.75f,
				ss_pos.y,
				ss_pos.z + 40*sin(DegToRad(m_AccumTime * 10.0f) * 2.f) * 0.75f));

			orbiting_sphere2->Physics()->SetAngularVelocity(Vector3(0.f, 1.f, 0.f));
		}
	}
	Object* target = this->FindGameObject("target");
	

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_J)) {
		Matrix4 viewMtx = SceneManager::Instance()->GetCamera()->BuildViewMatrix();
		Vector3 viewDir = -Vector3(viewMtx[2], viewMtx[6], viewMtx[10]);

		ostringstream fireballName;
		fireballName << "ball" << n;

		Object* ballF = CommonUtils::BuildSphereObject2(
			fireballName.str().c_str(),
			SceneManager::Instance()->GetCamera()->GetPosition(),
			0.3f,
			true,
			0.1f,
			true,
			false,
			Vector4(0.6f, 0.6f, 0.6f, 1.0f));

		this->AddGameObject(ballF);

		Object* fireBall = this->FindGameObject(fireballName.str().c_str());
		//fireBall->Physics()->Setstate(flase);
		fireBall->Physics()->Setbullet(true);
		fireBall->Physics()->SetLinearVelocity(viewDir*20.f);

		n++;

	}


	if (PhysicsEngine::Instance()->GetPoints() > 0)
	{
		thispoints = (int)PhysicsEngine::Instance()->GetPoints();
		totalpoints += thispoints;
		//setstateifcollision(true);
		
	}
	else if (PhysicsEngine::Instance()->GetPoints() == -1)
	{
		thispoints = 0;
		
	}

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_0)) {
	
		savescore.push_back(totalpoints);
		compernumber();
		thispoints = 0;
		totalpoints = 0;

		

		
	}

	NCLDebug::AddStatusEntry(status_colour, "This  Score is: %d", thispoints);
	NCLDebug::AddStatusEntry(status_colour, "Total  Score is: %d", totalpoints);
	

	//NCLDebug::AddStatusEntry(status_colour, "Score: %d", s);
	
	
	

	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.9f, 0.8f, 1.0f), "Physics:");
	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.9f, 0.8f, 1.0f), "     (Arrow Keys to Move Player)");
	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.9f, 0.8f, 1.0f), "     Draw Collision Volumes : %s (Press C to toggle)", (drawFlags & DEBUGDRAW_FLAGS_COLLISIONVOLUMES) ? "Enabled" : "Disabled");
	NCLDebug::AddStatusEntry(Vector4(1.0f, 0.9f, 0.8f, 1.0f), "     Draw Collision Normals : %s (Press N to toggle)", (drawFlags & DEBUGDRAW_FLAGS_COLLISIONNORMALS) ? "Enabled" : "Disabled");

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_C))
		drawFlags ^= DEBUGDRAW_FLAGS_COLLISIONVOLUMES;

	if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_N))
		drawFlags ^= DEBUGDRAW_FLAGS_COLLISIONNORMALS;

	PhysicsEngine::Instance()->SetDebugDrawFlags(drawFlags);

	//target12 = this->FindGameObject("target");

	/*if (target12->Physics()->Getcolition() == true && PhysicsEngine::Instance()->GetPoints() > 0 || PhysicsEngine::Instance()->GetPoints() == -1)
	{
		setstateifcollision(true);
	}
	else
	{
		setstateifcollision(false);
	}*/

	//Update Network
	auto callback = std::bind(
		&EmptyScene::ProcessNetworkEvent,	// Function to call
		this,								// Associated class instance
		std::placeholders::_1);				// Where to place the first parameter
	m_Network.ServiceNetwork(dt, callback);


	

	//Add Debug Information to screen
	uint8_t ip1 = m_pServerConnection->address.host & 0xFF;
	uint8_t ip2 = (m_pServerConnection->address.host >> 8) & 0xFF;
	uint8_t ip3 = (m_pServerConnection->address.host >> 16) & 0xFF;
	uint8_t ip4 = (m_pServerConnection->address.host >> 24) & 0xFF;

	NCLDebug::DrawTextWs(m_pObj->Physics()->GetPosition() + Vector3(0.f, 5.f, 0.f), 14.f, TEXTALIGN_CENTRE, Vector4(),
		"Peer: %u.%u.%u.%u:%u", ip1, ip2, ip3, ip4, m_pServerConnection->address.port);

	Vector4 status_color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	NCLDebug::AddStatusEntry(status_color, "Network Traffic");
	NCLDebug::AddStatusEntry(status_color, "    Incoming: %5.2fKbps", m_Network.m_IncomingKb);
	NCLDebug::AddStatusEntry(status_color, "    Outgoing: %5.2fKbps", m_Network.m_OutgoingKb);
	if (target->Physics()->Getcolition() == true && PhysicsEngine::Instance()->GetPoints() > 0)
	{
		state_if_collision=true;
		//EmptyScene::setstateifcollision(true);
	}
	else
	{
		state_if_collision=false;
		//EmptyScene::setstateifcollision(false);
	}
	if (target != NULL) {
		target->Physics()->SetAngularVelocity(Vector3(0.f, 0.5f, 0.f));
		target->Physics()->Settarget(true);
	}
	if (state_if_collision== true) {
		char* text_data = "you got score!";

		ENetPacket* packet = enet_packet_create(text_data, strlen(text_data) + 1, 0);

		enet_peer_send(m_pServerConnection, 0, packet);
	}
	
}

void EmptyScene::ProcessNetworkEvent(const ENetEvent& evnt)
{
	//Object* targetWhatever = this->FindGameObject("target");
	//if (true) {
	//}
	

	switch (evnt.type)
	{
		//New connection request or an existing peer accepted our connection request
	case ENET_EVENT_TYPE_CONNECT:
	{
		if (evnt.peer == m_pServerConnection)
		{
			NCLDebug::Log("Network: Successfully connected to server!");

			//Send a 'hello' packet
			char* text_data = "Hello!";
			
			ENetPacket* packet = enet_packet_create(text_data, strlen(text_data) + 1, 0);
			
			enet_peer_send(m_pServerConnection, 0, packet);
			
			
		
		}
	}
	break;


	//Server has sent us a new packet
	case ENET_EVENT_TYPE_RECEIVE:
	{
		if (evnt.packet->dataLength == sizeof(Vector3))
		{
			Vector3 pos;
			memcpy(&pos, evnt.packet->data, sizeof(Vector3));
			m_pObj->Physics()->SetPosition(pos);

		}
		else
		{
			NCLERROR("Recieved Invalid Network Packet!");
		}

	}
	break;


	//Server has disconnected
	case ENET_EVENT_TYPE_DISCONNECT:
	{
		NCLDebug::Log("Network: Server has disconnected!");

		

	}
	break;
	}
}

void EmptyScene::compernumber() {
	std::sort(savescore.begin(),savescore.end(),std::greater<int>());
	ostringstream f;
	for(std::vector<int>::iterator it = savescore.begin(); it != savescore.end(); ++it)
	{
		f << " " << *it;
	}
	//const char a=f.str().c_str();
	const char* text_data1 = f.str().c_str();

	ENetPacket* packet = enet_packet_create(text_data1, strlen(text_data1) + 1, 0);

	enet_peer_send(m_pServerConnection, 0, packet);
}