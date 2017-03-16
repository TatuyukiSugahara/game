#include "stdafx.h"
#include "ResultScene.h"
#include "Stage.h"

CResultScene* g_resultscene;

void CResultScene::Init()
{
	this->CreateSprite();

	resultcamera.Init();
	resultlight.Init();
	fade.Init();
	coinnumber.Init();
	coinnumber.Set1keta(D3DXVECTOR2(540.0f, 300.0f));
	coinnumber.Set2keta(D3DXVECTOR2(510.0f, 300.0f));
	coinnumber.Set3keta(D3DXVECTOR2(480.0f, 300.0f));
	coinnumber.SetColor(255, 0, 0);
	//coinsprite.Init();

	if (g_scenemanager->GetResult() == 0)
	{
		state = ResultState::Goal;
		resultGoal.Init();
	}
	else if (g_scenemanager->GetResult() == 1)
	{
		state = ResultState::Death;
		resultDeat.Init();
	}
}

void CResultScene::Update()
{
	

	if (state == ResultState::Goal)
	{
		resultGoal.Update();
		coinnumber.Update();		
	}
	else if (state == ResultState::Death)
	{
		resultDeat.Update();
	}
	if (g_pad.IsPress(enButtonA))
	{
		fade.SetFade(true);
	}
	if (fade.GetNext() <= fade.GetTimer())
	{
		if (state == ResultState::Goal)
		{
			switch (g_scenemanager->GetNumber())
			{
			case CSceneManager::StageNumber::Stage1:
				g_scenemanager->SetNumber((int)CSceneManager::StageNumber::Stage2);
				g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
				break;
			case CSceneManager::StageNumber::Stage2:
				g_scenemanager->SetNumber((int)CSceneManager::StageNumber::StageBoss);
				g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
				break;
			case CSceneManager::StageNumber::StageBoss:
				g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Title);
				break;
			}
		}
		else if (state == ResultState::Death)
		{
			g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
		}
		
		
	}
	resultcamera.Update();
	resultlight.Update();
	fade.Update();
	
	
}

void CResultScene::Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	if (state == ResultState::Goal)
	{
		resultGoal.Render(m_pSprite);
		coinnumber.Render(m_pSprite);
		//coinsprite.Render();
	}
	else if (state == ResultState::Death)
	{
		resultDeat.Render(m_pSprite);
	}
	fade.Render(m_pSprite);

	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT CResultScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}
