#include "stdafx.h"
#include "GoalFlag.h"
#include "Stage.h"
#include "ResultScene.h"
#include "Sound\SoundSource.h"

//コンストラクタ
CGoalFlag::CGoalFlag()
{
	//初期化。
	D3DXMatrixIdentity(&mWorld);
	position.x = 465.0f;
	position.y = 8.5f;
	position.z = 0.0f;
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}
//デストラクタ
CGoalFlag::~CGoalFlag()
{
}
//初期化。
void CGoalFlag::Init()
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
	modelData.LoadModelData("Asset/model/goalflag.X", &animation);

	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
}
//更新。
void CGoalFlag::Update()
{
	//ワールド行列の更新。
	skinmodel.UpdateWorldMatrix(position, D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), scale);
}
//描画。
void CGoalFlag::Render()
{
	skinmodel.Draw(&g_stage->GetCamera()->GetViewMatrix(), &g_stage->GetCamera()->GetProjectionMatrix(), false);
}
//開放。
void CGoalFlag::Release()
{

}