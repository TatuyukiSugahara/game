#include "stdafx.h"
#include "Sun.h"
#include "Stage.h"

//コンストラクタ
CSun::CSun()
{
	//初期化。
	position = D3DXVECTOR3(20.0f, 3.0f, 70.0f);
	scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}
//デストラクタ
CSun::~CSun()
{
}
//初期化。
void CSun::Init()
{
	switch (g_scenemanager->GetNomber())
	{
	case Stage1:
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
	case Stage2:
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
	case StageBoss:
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
	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetNormalMap(false);
	skinmodel.SetSpecularMap(false);
}
//更新。
void CSun::Update()
{

	skinmodel.UpdateWorldMatrix({ position.x + g_stage->GetPlayer()->GetPos().x, position.y + g_stage->GetPlayer()->GetPos().y, position.z + g_stage->GetPlayer()->GetPos().z }, rotation, scale);

}
//描画。
void CSun::Render()
{
	skinmodel.Draw(&g_stage->GetCamera()->GetViewMatrix(), &g_stage->GetCamera()->GetProjectionMatrix(), false);
}
