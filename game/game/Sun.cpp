#include "stdafx.h"
#include "Sun.h"
#include "Stage.h"

//�R���X�g���N�^
CSun::CSun()
{
	//�������B
	position = D3DXVECTOR3(20.0f, 3.0f, 70.0f);	//���W������
	scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);		//�傫��������
	rotation = CConst::QuaternionIdentity;		//��]������
}
//�f�X�g���N�^
CSun::~CSun()
{
}
//�������B
void CSun::Init()
{
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		//���C�g���������B
		light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

		light.SetDiffuseLightColor(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetAmbientLight(D3DXVECTOR4(1.5f, 1.5f, 1.5f, 1.0f));
		break;
	case CSceneManager::StageNumber::Stage2:
		//���C�g���������B
		light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

		light.SetDiffuseLightColor(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetAmbientLight(D3DXVECTOR4(1.5f, 1.5f, 2.0f, 1.0f));
		break;
	case CSceneManager::StageNumber::StageBoss:
		//���C�g���������B
		light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

		light.SetDiffuseLightColor(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetDiffuseLightColor(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
		light.SetAmbientLight(D3DXVECTOR4(1.5f, 1.5f, 2.0f, 1.0f));
		break;
	}
	modelData.LoadModelData("Asset/model/sun.x", &animation);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	skinModel.SetShadowReceiverFlag(false);	//�e���󂯂Ȃ�
	skinModel.SetDrawToShadowMap(false);	//�e�`�悵�Ȃ�
	skinModel.SetNormalMap(false);			//�m�[�}���}�b�v�Ȃ�	
	skinModel.SetSpecularMap(false);		//���؂����Ȃ�
}
//�X�V�B
void CSun::Update()
{
	//�v���C���[�ɒǏ]����B
	//��ɉ�ʂɓ��邽��
	D3DXVECTOR3 playerPos = g_stage->GetPlayer()->GetPos();	//�v���C���[�̃|�W�V�����Q�b�g
	skinModel.UpdateWorldMatrix({ position.x + playerPos.x,
		position.y + playerPos.y,
		position.z + playerPos.z }
	, rotation, scale);

}
//�`��B
void CSun::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	skinModel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
}
