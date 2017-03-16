#include "stdafx.h"
#include "StageBack.h"
#include "Stage.h"

//�R���X�g���N�^
CStageBack::CStageBack()
{
	//�������B

	position = CConst::Vec3Zero;			//���W������
	scale = CConst::Vec3One;				//�傫��������
	rotation = CConst::QuaternionIdentity;	//��]������
}
//�f�X�g���N�^
CStageBack::~CStageBack()
{
}
//�������B
void CStageBack::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.1f, 1.1f, 1.1f, 1.0f));

	
	modelData.LoadModelData("Asset/model/sphere.x", &animation);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	skinModel.SetShadowReceiverFlag(false);
	skinModel.SetDrawToShadowMap(false);
	skinModel.SetNormalMap(false);
	skinModel.SetSpecularMap(false);
	skinModel.SetSkyCube(true);
	//�L���[�u�}�b�v���e�X�e�[�W���ƂɃZ�b�g�B
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		skinModel.SetTexture("Asset/model/skyCubeSunny.dds", true);	//��
		break;
	case CSceneManager::StageNumber::Stage2:
		skinModel.SetTexture("Asset/model/skyCubeMap.dds", true);	//��
		break;
	case CSceneManager::StageNumber::StageBoss:
		skinModel.SetTexture("Asset/model/skyCubeMap.dds", true);	//��
		break;
	}
	
}
//�X�V�B
void CStageBack::Update()
{	
	//�v���C���[�̃|�W�V�������Q�b�g�B
	//�v���C���[�ɒǏ]���邽��
	position = g_stage->GetPlayer()->GetPos();
	//�v���C���[�ɒǏ]����B
	skinModel.UpdateWorldMatrix(D3DXVECTOR3(position.x, position.y - 100.0f, position.z), rotation, scale);
	
}
//�`��B
void CStageBack::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix
	)
{
	//�w�i�p�J�������g�p����]������
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	skinModel.Render(&viewMatrix, &projMatrix, false);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//�J���B
void CStageBack::Release()
{

}