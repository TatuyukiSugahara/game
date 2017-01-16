#include "stdafx.h"
#include "TitleScene.h"
#include "Stage.h"

CTitleScene g_titlescene;

void CTitleScene::Init()
{
	this->CreateSprite();

	camera.Init();
	light.Init();
	title.Init();
	fade.Init();
}

void CTitleScene::Update()
{
	camera.Update();
	light.Update();
	title.Update();
	fade.Update();

	if (g_pad.IsPress(enButtonA))
	{
		fade.SetFade(true);
	}
	if (fade.GetNext() <= fade.GetTimer())
	{
		g_scenemanager->ChangeScene(GameScene::Game);
	}
}

void CTitleScene::Render()
{
	// 画面をクリア。
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//シーンの描画開始。
	g_pd3dDevice->BeginScene();

	title.Render(m_pSprite);
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
