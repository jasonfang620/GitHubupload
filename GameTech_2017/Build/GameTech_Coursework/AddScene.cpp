#include"EmptyScene.h"

#include <nclgl\Vector4.h>
#include <ncltech\PhysicsEngine.h>
#include <ncltech\DistanceConstraint.h>
#include <ncltech\SceneManager.h>
#include <ncltech\CommonUtils.h>
#include <sstream>
using namespace CommonUtils;


const Vector4 status_colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

EmptyScene::EmptyScene(const std::string& friendly_name)
	: Scene(friendly_name)
	, m_AccumTime(0.0f)
	, m_pPlayer(NULL), m_Rotating(true)
{
}

EmptyScene::~EmptyScene() {}
const Vector3 ss_pos = Vector3(0.0f, 0.0f, 0.0f);

void EmptyScene::OnInitializeScene() {

	PhysicsEngine::Instance()->SetPaused(false);

	SceneManager::Instance()->GetCamera()->SetPosition(Vector3(30.0f, 0.0f, 40.0f));
	SceneManager::Instance()->GetCamera()->SetYaw(45.f);
	SceneManager::Instance()->GetCamera()->SetPitch(0.f);
	PhysicsEngine::Instance()->SetDebugDrawFlags(DEBUGDRAW_FLAGS_CONSTRAINT);
	m_AccumTime = 0.0f;
	m_Rotating = true;
	Object* ground = CommonUtils::BuildCuboidObjectGroud(
		"target",
		ss_pos+Vector3(0.0f, 15.f, 0.0f),
		Vector3(0.5f, 5.0f, 5.0f),
		true,
		0.0f,
		true,
		false,
		Vector4(0.2f, 0.5f, 1.0f, 1.0f));
	
	this->AddGameObject(ground);

	
	int box_num = 0;

	ostringstream box_name;


	
	for (int x = 0; x < 2; ++x)
	{
		for (int y = 0; y < 6; ++y){

			uint idx = x * 5 + y;
			Vector4 colour = GenColour(idx / 10.f, 0.5f);
			Vector3 pos = Vector3(x - y * 0.5f+20.f, 0.5f + float(6 - 1 - y), -0.5f);
			
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

	Object* ballF=CommonUtils::BuildSphereObject(
		"BallF",
		ss_pos,
		10.0f, 
		true, 
		0.0f, 
		true, 
		false,
		Vector4(0.6f, 0.6f, 0.6f, 1.0f));
	
		this->AddGameObject(ballF);
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

}

void EmptyScene::OnCleanupScene()
{
	//Just delete all created game objects 
	//  - this is the default command on any Scene instance so we don't really need to override this function here.
	Scene::OnCleanupScene();
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
				ss_pos.x + 30*cos(DegToRad(m_AccumTime * 10.0f) * 2.f) * 0.75f,
				ss_pos.y,
				ss_pos.z + 20*sin(DegToRad(m_AccumTime * 10.0f) * 2.f) * 0.75f));

			orbiting_sphere2->Physics()->SetAngularVelocity(Vector3(0.f, 1.f, 0.f));
		}
		Object* target = this->FindGameObject("target");
		if (target != NULL) {
			target->Physics()->SetAngularVelocity(Vector3(0.f, 0.5f, 0.f));
		}
		
		
	}


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
	
	
	//NCLDebug::AddStatusEntry(status_colour, "Score: %d", s);
	Object* target = this->FindGameObject("target");
	target->Physics()->Settarget(true);

	//if (target->Physics()->Getcolition() == true) {

		
	//}
	


	//uint drawFlags = PhysicsEngine::Instance()->GetDebugDrawFlags();
	//PhysicsEngine::Instance()->SetDebugDrawFlags(drawFlags);
}