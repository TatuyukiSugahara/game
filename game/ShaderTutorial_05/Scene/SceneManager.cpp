#include "../stdafx.h"
#include "SceneManager.h"
#include "../TitleScene.h"
#include "..\Stage.h"
#include "../ResultScene.h"

void CSceneManager::InitializeScene()
{
	ChangeScene(GameScene::Title);
}

void CSceneManager::UpdateScene()
{
	if (m_scenes){
		m_scenes->Update();
	}
	if (nextScene != -1){
		if (m_scenes != NULL)
		{
			delete m_scenes;
		}
		if (nextScene == GameScene::Title)
		{
			m_scenes = new CTitleScene;
		}
		if (nextScene == GameScene::Game)
		{
			m_scenes = new CStage;
		}
		if (nextScene == GameScene::Result)
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
