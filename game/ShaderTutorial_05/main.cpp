/*!
 *@brief	�V�F�[�_�[�̃`���[�g���A��00
 */
#include "stdafx.h"
#include "stage.h"
#include "TitleScene.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��B
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	scene = GameScene::Title;
	//�^�C�g���V�[��������
	g_titlescene.Init();
	//�X�e�[�W������
	g_stage = new CStage;
	g_stage->Initialize();

	
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	switch (scene)
	{
	case Title:
		//�^�C�g���V�[���`��
		g_titlescene.Render();
		break;
	case Game:
		//�X�e�[�W�`��
		g_stage->Render();
		break;
	case Result:
		break;
	}
	
	
}
/*!-----------------------------------------------------------------------------
 *@brief	�X�V�����B
 -----------------------------------------------------------------------------*/
void Update()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		PostQuitMessage(0);
	}
	switch (scene)
	{
	case Title:
		//�^�C�g���V�[���X�V
		g_titlescene.Update();
		break;
	case Game:
		//�X�e�[�W�X�V
		g_stage->Update();
		break;
	case Result:
		break;
	}
	
	
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	//�X�e�[�W�����[�X
	g_stage->Release();
	delete g_stage;
	delete g_effectManager;
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
