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
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();
	title.Render(m_pSprite);
	titlestart.Render(m_pSprite);
	titlestartBG.Render(m_pSprite);
	fade.Render(m_pSprite);
	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT CTitleScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}
