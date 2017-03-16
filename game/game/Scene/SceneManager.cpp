#include "../stdafx.h"
#include "SceneManager.h"
#include "../TitleScene.h"
#include "..\Stage.h"
#include "../ResultScene.h"

CSceneManager::CSceneManager()
{
	m_scenes = NULL;
	Number = StageNumber::Stage1;
}

void CSceneManager::InitializeScene()
{
	ChangeScene((int)GameScene::Title);
}

void CSceneManager::UpdateScene()
{
	if (m_scenes){
		m_scenes->Update();
	}
	if (nextScene != -1){
		if (m_scenes != NULL)
		{
			delete g_physicsWorld;
			g_physicsWorld = NULL;
			delete m_scenes;
		}
		if (nextScene == (int)GameScene::Title)
		{
			m_scenes = new CTitleScene;
		}
		if (nextScene == (int)GameScene::Game)
		{
			m_scenes = new CStage;
			num = 0;
		}
		if (nextScene == (int)GameScene::Result)
		{
			m_scenes = new CResultScene;
		}
		m_scenes->Init();
		nextScene = -1;
	}
}

void CSceneManager::RenderScene()
{

	m_scenes->Render();
}

void CSceneManager::ChangeScene(const int& key)
{
	nextScene = key;
}
