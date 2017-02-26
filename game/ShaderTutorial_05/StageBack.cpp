#include "stdafx.h"
#include "StageBack.h"
#include "Stage.h"

//コンストラクタ
CStageBack::CStageBack()
{
	//初期化。

	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetNormalMap(false);
	skinmodel.SetSpecularMap(false);
	skinmodel.SetSkyCube(true);
	switch (g_scenemanager->GetNomber())
	{
	case Stage1:
		skinmodel.SetTexture("Asset/model/skyCubeSunny.dds", true);
		break;
	case Stage2:
		skinmodel.SetTexture("Asset/model/skyCubeMap.dds", true);
		break;
	case StageBoss:
		skinmodel.SetTexture("Asset/model/skyCubeMap.dds", true);
		break;
	}
	
}
//更新。
void CStageBack::Update()
{	
	
	targetPos = g_stage->GetPlayer()->GetPos();
	static float rot = 0.0f;
	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rot += 0.001f);

	skinmodel.UpdateWorldMatrix(D3DXVECTOR3(targetPos.x, targetPos.y - 80.0f, targetPos.z), rotation, scale);
	
}
//描画。
void CStageBack::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix
	)
{
	
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	skinmodel.Draw(&viewMatrix, &projMatrix, false);
	pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	
}

//開放。
void CStageBack::Release()
{

}