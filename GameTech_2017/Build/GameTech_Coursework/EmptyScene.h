#pragma once

#include <nclgl\Mesh.h>
#include <ncltech\Scene.h>
#include <ncltech\CommonUtils.h>
#include <nclgl\OBJMesh.h>
#include <ncltech\NetworkBase.h>

class EmptyScene : public Scene
{
public:
	EmptyScene(const std::string& friendly_name);
	virtual ~EmptyScene();

	virtual void OnInitializeScene()	 override;
	virtual void OnCleanupScene()		 override;
	virtual void OnUpdateScene(float dt) override;

	void ProcessNetworkEvent(const ENetEvent& evnt);

	bool m_Rotating;
	
	virtual void setstateifcollision(bool a) { state_if_collision = a; }
	virtual bool getstateifcollision() { return state_if_collision; }

protected:
	float m_AccumTime;
	Object* m_pPlayer;

	OBJMesh *m_MeshHouse;

	GLuint	m_whiteTexture;

	Object*     m_pObj;
	//Object*		target12;
	Object*		target;


	NetworkBase m_Network;

	ENetPeer*	m_pServerConnection;
	
	bool state_if_collision;
	
	int thispoints = 0;
	int totalpoints = 0;

};