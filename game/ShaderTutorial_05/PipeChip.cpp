#include "stdafx.h"
#include "PipeChip.h"
#include "Stage.h"

CPipeChip::CPipeChip()
{
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixIdentity(&mScale);
}

CPipeChip::~CPipeChip()
{
}
void CPipeChip::Init()
{
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.6f, 0.6f, 1.0f));

	//まずはスキンモデルをロード。
	modelData = g_skinmodeldataManager->LoadSkinModelData("Asset/model/pipe.X");
	//modelData.LoadModelData("Asset/model/pipe.X", &animation);
	skinmodel.Init(modelData);
	skinmodel.SetLight(&light);
	skinmodel.SetShadowReceiverFlag(true);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetGround(true);
	skinmodel.SetNormalMap(false);
	skinmodel.SetSpecularMap(false);
	//ワールド行列のバッファを作成。
	D3DXMatrixScaling(&mScale, Scale.x, Scale.y, Scale.z);
}

void CPipeChip::Update()
{

}
void CPipeChip::Render()
{
	//ワールド行列の更新。
	skinmodel.UpdateWorldMatrix(position, rotation, Scale);

	skinmodel.Draw(&g_stage->GetCamera()->GetViewMatrix(),
		&g_stage->GetCamera()->GetProjectionMatrix(),
		false);
}