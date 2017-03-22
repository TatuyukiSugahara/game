#include "stdafx.h"
#include "GoalFlag.h"
#include "Stage.h"
#include "ResultScene.h"
#include "Sound\SoundSource.h"

//�R���X�g���N�^
CGoalFlag::CGoalFlag()
{
	//�������B
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		position.x = 385.0f;
		position.y = 37.0f;
		position.z = -24.5f;
		break;
	case CSceneManager::StageNumber::Stage2:
		position.x = 349.0f;
		position.y = 140.5f;
		position.z = 11.0f;
		break;
	}
	scale = CConst::Vec3One;
}
//�f�X�g���N�^
CGoalFlag::~CGoalFlag()
{
}
//�������B
void CGoalFlag::Init()
{
	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//���f�������[�h�B
	modelData.LoadModelData("Asset/model/goalflag.X", &animation);
	animation.PlayAnimation(0);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
}
//�X�V�B
void CGoalFlag::Update()
{
	//���[���h�s��̍X�V�B
	skinModel.UpdateWorldMatrix(position, CConst::QuaternionIdentity, scale);
}
//�`��B
void CGoalFlag::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	skinModel.Render(&viewMatrix, &projMatrix, false);
}