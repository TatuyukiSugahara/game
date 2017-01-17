#include "stdafx.h"
#include "ResultScene.h"
#include "Stage.h"

CResultScene* g_resultscene;

void CResultScene::Init()
{
	this->CreateSprite();

	resultcamera.Init();
	resultlight.Init();
	resultDeat.Init();
	resultGoal.Init();
	fade.Init();
	coinnumber.Init();
	coinnumber.Set1keta(D3DXVECTOR2(540.0f, 300.0f));
	coinnumber.Set2keta(D3DXVECTOR2(510.0f, 300.0f));
	coinnumber.SetColor(255, 0, 0);
	coinsprite.Init();
	coinsprite.SetPos(D3DXVECTOR2(440.0f, 302.5f));

	if (g_scenemanager->GetResult() == 0)
	{
		state = ResultState::Goal;
	}
	else if (g_scenemanager->GetResult() == 1)
	{
		state = ResultState::Death;
	}
}

void CResultScene::Update()
{
	

	if (state == ResultState::Goal)
	{
		resultGoal.Update();
		coinnumber.Update();
		coinsprite.Update();
	}
	else if (state == ResultState::Death)
	{
		resultDeat.Update();
	}
	resultcamera.Update();
	resultlight.Update();
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

void CResultScene::Render()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	if (state == ResultState::Goal)
	{
		resultGoal.Render(m_pSprite);
		coinnumber.Render(m_pSprite);
		coinsprite.Render(m_pSprite);
	}
	else if (state == ResultState::Death)
	{
		resultDeat.Render(m_pSprite);
	}
	fade.Render(m_pSprite);

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

HRESULT CResultScene::CreateSprite()
{
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
		return E_FAIL;//���s�ԋp
	}
	return S_OK;
}
