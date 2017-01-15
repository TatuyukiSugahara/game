/*!
 *@brief	�V�F�[�_�[�̃`���[�g���A��00
 */
#include "stdafx.h"
#include "stage.h"
#include "TitleScene.h"
#include "ResultScene.h"
#include "Scene\SceneManager.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��B
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//scene = GameScene::Title;
	////�^�C�g���V�[��������
	//g_titlescene.Init();
	////�X�e�[�W������
	//g_stage->Init();
	////���U���g���
	//g_resultscene.Init();
	//�T�E���h�G���W��
	g_soundengine->Init();
	g_scenemanager->InitializeScene();
	
}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	//switch (scene)
	//{
	//case Title:
	//	//�^�C�g���V�[���`��
	//	g_titlescene.Render();
	//	break;
	//case Game:
	//	//�X�e�[�W�`��
	//	g_stage->Render();
	//	break;
	//case Result:
	//	//���U���g���
	//	g_resultscene.Render();
	//	break;
	//}
	g_scenemanager->RenderScene();
	
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
	//switch (scene)
	//{
	//case Title:
	//	//�^�C�g���V�[���X�V
	//	g_titlescene.Update();
	//	break;
	//case Game:
	//	//�X�e�[�W�X�V
	//	g_stage->Update();
	//	break;
	//case Result:
	//	//���U���g���
	//	g_resultscene.Update();
	//	break;
	//}
	//�T�E���h�G���W��
	g_soundengine->Update();
	g_soundsource->Update();
	g_scenemanager->UpdateScene();
	
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	//�X�e�[�W�����[�X
	if (g_stage){
		g_stage->Release();
		delete g_stage;
	}
	if (g_effectManager){
		delete g_effectManager;
	}
	g_pd3dDevice->Release();
	g_pD3D->Release();
}
