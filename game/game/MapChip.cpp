#include "stdafx.h"
#include "MapChip.h"
#include "Stage.h"

CMapChip::CMapChip()
{
	position = CConst::Vec3Zero;
}

CMapChip::~CMapChip()
{
}
void CMapChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
{
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//まずはスキンモデルをロード。
	char modelPath[256];
	sprintf(modelPath, "Asset/model/%s.X", name);
	modelData = g_skinmodeldataManager->LoadSkinModelData(modelPath);
	skinmodel.Init(modelData);
	skinmodel.SetLight(&light);
	skinmodel.SetShadowReceiverFlag(true);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetGround(true);
	skinmodel.SetNormalMap(false);
	skinmodel.SetSpecularMap(false);
}

void CMapChip::Update()
{
	
}
void CMapChip::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	//ワールド行列の更新。
	skinmodel.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	skinmodel.Render(&viewMatrix, &projMatrix, false);
}