/*!
 *@brief	�V�F�[�_�[�̃`���[�g���A��00
 */
#include "stdafx.h"
#include "Camera.h"
#include "Light.h"
#include "Player.h"
#include "Block.h"
#include "Stage.h"
#include "HatenaBox.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ��B
//-----------------------------------------------------------------------------
Camera camera;				//�J�����B
CLight light;				//���C�g
CPlayer player;				//�v���C���[
CBlock block;				//�u���b�N
CStage stage;				//�X�e�[�W
CHatenaBox	hanatebox;		//�͂Ăȃ{�b�N�X

/*!-----------------------------------------------------------------------------
 *@brief	���C�g���X�V�B
 -----------------------------------------------------------------------------*/
void UpdateLight()
{
	light.Update();
}
//-----------------------------------------------------------------------------
// Name: �Q�[�����������B
//-----------------------------------------------------------------------------
void Init()
{
	//���C�g���������B
	light.Init();
	//�X�e�[�W������
	stage.Initialize();
	//�u���b�N������
	block.Init(g_pd3dDevice);
	//�͂Ăȃ{�b�N�X������
	hanatebox.Init(g_pd3dDevice);
	//�v���C���[������
	player.Init(g_pd3dDevice);
	//�J�����̏������B
	camera.Init(&player);

}
//-----------------------------------------------------------------------------
// Name: �`�揈���B
//-----------------------------------------------------------------------------
VOID Render()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();
	//�u���b�N��`��
	block.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//�͂Ăȃ{�b�N�X�`��
	hanatebox.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//�v���C���[��`��
	player.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
/*!-----------------------------------------------------------------------------
 *@brief	�X�V�����B
 -----------------------------------------------------------------------------*/
void Update()
{
	//���C�g�̍X�V�B
	UpdateLight();
	//�X�e�[�W�X�V
	stage.Update();
	//�u���b�N���X�V
	block.Update();
	//�͂Ăȃ{�b�N�X�X�V
	hanatebox.Update();
	//�v���C���[���X�V�B
	player.Update();
	//�J�����̍X�V
	camera.Update();
	
}
//-----------------------------------------------------------------------------
//�Q�[�����I������Ƃ��ɌĂ΂�鏈���B
//-----------------------------------------------------------------------------
void Terminate()
{
	//�u���b�N�����[�X
	block.Release();
	//�͂Ăȃ{�b�N�X�����[�X
	hanatebox.Release();
	//�v���C���[�����[�X
	player.Release();
}
