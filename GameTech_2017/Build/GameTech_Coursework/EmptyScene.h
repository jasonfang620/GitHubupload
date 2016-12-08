#pragma once

#include <nclgl\Mesh.h>
#include <ncltech\Scene.h>
#include <ncltech\CommonUtils.h>

class EmptyScene : public Scene
{
public:
	EmptyScene(const std::string& friendly_name);
	virtual ~EmptyScene();

	virtual void OnInitializeScene()	 override;
	//{
		/*Scene::OnInitializeScene();
		SceneManager::Instance()->GetCamera()->SetPosition(Vector3(30.0f, 0.0f, 30.0f));
		SceneManager::Instance()->GetCamera()->SetYaw(45.f);
		SceneManager::Instance()->GetCamera()->SetPitch(0.f);
		this->AddGameObject(CommonUtils::BuildSphereObject("Ball", Vector3(0.0f, 0.0f, 0.0f), 20.0f, false, 0.0f, true, false, Vector4(0.2f, 0.5f, 1.0f, 1.0f)));*/
		//this->AddGameObject(CommonUtils::BuildCuboidObject("Ground", Vector3(0.0f, -1.0f, 0.0f), Vector3(20.0f, 1.0f, 20.0f), false, 0.0f, true, false, Vector4(0.2f, 0.5f, 1.0f, 1.0f)));
	//}

	virtual void OnCleanupScene()		 override;
	virtual void OnUpdateScene(float dt) override;

	bool m_Rotating;
	
protected:
	float m_AccumTime;
	Object* m_pPlayer;
	
	

};