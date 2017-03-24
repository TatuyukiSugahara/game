#include "stdafx.h"
#include "StageBack.h"
#include "Stage.h"

//コンストラクタ
CStageBack::CStageBack()
{
	//初期化。

	position = CConst::Vec3Zero;			//座標初期化
	scale = CConst::Vec3One;				//大きさ初期化
	rotation = CConst::QuaternionIdentity;	//回転初期化
}
//デストラクタ
CStageBack::~CStageBack()
{
}
//初期化。
void CStageBack::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//ライトを初期化。
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
	//キューブマップを各ステージごとにセット。
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		skinModel.SetTexture("Asset/model/skyCubeSunny.dds", true);	//朝
		break;
	case CSceneManager::StageNumber::Stage2:
		skinModel.SetTexture("Asset/model/skyCubeMap.dds", true);	//夜
		break;
	case CSceneManager::StageNumber::StageBoss:
		skinModel.SetTexture("Asset/model/skyCubeMap.dds", true);	//夜
		break;
	}
	
}
//更新。
void CStageBack::Update()
{	
	//プレイヤーのポジションをゲット。
	//プレイヤーに追従するため
	position = g_stage->GetPlayer()->GetPos();
	//プレイヤーに追従する。
	skinModel.UpdateWorldMatrix(D3DXVECTOR3(position.x, position.y - 100.0f, position.z), rotation, scale);
	
}
//描画。
void CStageBack::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix
	)
{
	//背景用カメラを使用し回転させる
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	skinModel.Render(&viewMatrix, &projMatrix, false);
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//開放。
void CStageBack::Release()
{

}