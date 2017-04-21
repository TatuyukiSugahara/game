#include "stdafx.h"
#include "Goal.h"
#include "Frame\CalcAABBSizeFromMesh.h"
#include "Map\Stage.h"
#include "Result/ResultScene.h"
#include "Sound\SoundSource.h"

namespace
{
	const float oku = 3.0f;
}

//コンストラクタ
CGoal::CGoal()
{
	//初期化。
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
	aabbMax = CConst::Vec3Zero;
	aabbMin = CConst::Vec3Zero;
}
//デストラクタ
CGoal::~CGoal()
{
}
//初期化。
void CGoal::Init()
{
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//モデルをロード。
	modelData.LoadModelData("Asset/model/goal.X", NULL);
	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	//AABB
	CalcAABBSizeFromMesh(skinModel.GetOrgMeshFirst(), aabbMin, aabbMax);
	aabbMin += position;
	aabbMax += position;
}
//更新。
void CGoal::Update()
{
	//AABBの範囲に入っているか。
	AabbUpdate();
	//ワールド行列の更新。
	skinModel.UpdateWorldMatrix(position, CConst::QuaternionIdentity, scale);
}
//描画。
void CGoal::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix
	)
{
	skinModel.Render(&viewMatrix, &projMatrix, false);
}

void CGoal::AabbUpdate()
{
	
	D3DXVECTOR3 playermax = g_stage->GetPlayer()->GetAABBMax();
	D3DXVECTOR3 playermin = g_stage->GetPlayer()->GetAABBMin();
	/*AABB*/
	if (aabbMax.x > g_stage->GetPlayer()->GetAABBMin().x
		&& aabbMin.x < g_stage->GetPlayer()->GetAABBMax().x
		&& aabbMax.y > g_stage->GetPlayer()->GetAABBMin().y
		&& aabbMin.y < g_stage->GetPlayer()->GetAABBMax().y
		&& aabbMax.z + oku > g_stage->GetPlayer()->GetAABBMin().z
		&& aabbMin.z - oku < g_stage->GetPlayer()->GetAABBMax().z

		)
	{
		g_scenemanager->SetResult(0);//ゴールした場合
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Result);
	}
}