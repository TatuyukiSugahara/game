#include "stdafx.h"
#include "TitleScene.h"
#include "Map\Stage.h"

CTitleScene g_titlescene;

CTitleScene::~CTitleScene()
{ 
}

void CTitleScene::Init()
{
	SETitle.reset( new CSoundSource);
	SETitle->Init("Asset/Sound/CandyCrush.wav");
	SETitle->SetVolume(0.25f);
	SETitle->Play(true);
	this->CreateSprite();
	title.Init();
	titlestart.Init();
	titlestartBG.Init();
	fade.Init();
	camera.Init();
	light.Init();
	
}

void CTitleScene::Update()
{
	title.Update();
	titlestart.Update();
	titlestartBG.Update();
	fade.Update();
	camera.Update();
	light.Update();
	if (g_pad.IsTrigger(enButtonA))
	{
		fade.SetFade(true);
		SETitles.reset (new CSoundSource);
		SETitles->Init("Asset/Sound/ta_ta_pi03.wav");
		SETitles->Play(false);
	}
	if (fade.GetNext() <= fade.GetTimer())
	{
		SETitle->Stop();
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
	}
}

void CTitleScene::Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();
	title.Render(m_pSprite);
	titlestart.Render(m_pSprite);
	titlestartBG.Render(m_pSprite);
	fade.Render(m_pSprite);
	// シーンの描画終了。
	g_pd3dDevice->EndScene();
	// バックバッファとフロントバッファを入れ替える。
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT CTitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		MessageBox(0, TEXT("スプライト作成失敗"), NULL, MB_OK);
		return E_FAIL;//失敗返却
	}
	return S_OK;
}
