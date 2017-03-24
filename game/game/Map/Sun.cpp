#include "stdafx.h"
#include "Sun.h"
#include "Stage.h"

//コンストラクタ
CSun::CSun()
{
	//初期化。
	position = D3DXVECTOR3(20.0f, 3.0f, 70.0f);	//座標初期化
	scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);		//大きさ初期化
	rotation = CConst::QuaternionIdentity;		//回転初期化
}
//デストラクタ
CSun::~CSun()
{
}
//初期化。
void CSun::Init()
{
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		//ライトを初期化。
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
		//ライトを初期化。
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
		//ライトを初期化。
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
	skinModel.SetShadowReceiverFlag(false);	//影を受けない
	skinModel.SetDrawToShadowMap(false);	//影描画しない
	skinModel.SetNormalMap(false);			//ノーマルマップなし	
	skinModel.SetSpecularMap(false);		//すぺきゅらなし
}
//更新。
void CSun::Update()
{
	//プレイヤーに追従する。
	//常に画面に入るため
	D3DXVECTOR3 playerPos = g_stage->GetPlayer()->GetPos();	//プレイヤーのポジションゲット
	skinModel.UpdateWorldMatrix({ position.x + playerPos.x,
		position.y + playerPos.y,
		position.z + playerPos.z }
	, rotation, scale);

}
//描画。
void CSun::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	skinModel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
}
