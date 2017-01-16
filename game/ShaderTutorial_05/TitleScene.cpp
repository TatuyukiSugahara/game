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
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	title.Render(m_pSprite);
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
