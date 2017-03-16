#include "stdafx.h"
#include "Goal.h"
#include "CalcAABBSizeFromMesh.h"
#include "Stage.h"
#include "ResultScene.h"
#include "Sound\SoundSource.h"

//�R���X�g���N�^
CGoal::CGoal()
{
	//�������B
	D3DXMatrixIdentity(&mWorld);
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		position = D3DXVECTOR3(385.0f, 30.0f, -24.5f);
		break;
	case CSceneManager::StageNumber::Stage2:
		position = D3DXVECTOR3(349.0f, 133.0f, 11.0f);
		break;
	}
	scale = CConst::Vec3One;
	m_aabbMax = CConst::Vec3Zero;
	m_aabbMin = CConst::Vec3Zero;
}
//�f�X�g���N�^
CGoal::~CGoal()
{
}
//�������B
void CGoal::Init()
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
	modelData.LoadModelData("Asset/model/goal.X", NULL);
	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	//AABB
	CalcAABBSizeFromMesh(skinmodel.GetOrgMeshFirst(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;

	
}
//�X�V�B
void CGoal::Update()
{
	//AABB�͈̔͂ɓ����Ă��邩�B
	AabbUpdate();
	//���[���h�s��̍X�V�B
	skinmodel.UpdateWorldMatrix(position, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), scale);
}
//�`��B
void CGoal::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix
	)
{
	skinmodel.Render(&viewMatrix, &projMatrix, false);
}

void CGoal::AabbUpdate()
{
	static float tyousei = 0.8f;
	/*AABB*/
	if (m_aabbMax.x - tyousei > g_stage->GetPlayer()->GetAABBMin().x + tyousei
		&& m_aabbMin.x + tyousei < g_stage->GetPlayer()->GetAABBMax().x - tyousei
		&& m_aabbMax.y - tyousei > g_stage->GetPlayer()->GetAABBMin().y + tyousei
		&& m_aabbMin.y + tyousei < g_stage->GetPlayer()->GetAABBMax().y - tyousei
		&& m_aabbMax.z + 3.0f > g_stage->GetPlayer()->GetAABBMin().z + tyousei
		&& m_aabbMin.z - 3.0f < g_stage->GetPlayer()->GetAABBMax().z - tyousei

		)
	{
		g_scenemanager->SetResult(0);//�S�[�������ꍇ
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Result);
	}
}