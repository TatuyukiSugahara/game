#include "stdafx.h"
#include "GoalFlag.h"
#include "Stage.h"
#include "ResultScene.h"
#include "Sound\SoundSource.h"

//�R���X�g���N�^
CGoalFlag::CGoalFlag()
{
	//�������B
	D3DXMatrixIdentity(&mWorld);
	position.x = 465.0f;
	position.y = 8.5f;
	position.z = 0.0f;
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
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

	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
}
//�X�V�B
void CGoalFlag::Update()
{
	//���[���h�s��̍X�V�B
	skinmodel.UpdateWorldMatrix(position, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), scale);
}
//�`��B
void CGoalFlag::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	skinmodel.Draw(&viewMatrix, &projMatrix, false);
}
//�J���B
void CGoalFlag::Release()
{

}