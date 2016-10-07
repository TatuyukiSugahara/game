#include "stdafx.h"
#include "MapChip.h"
#include "Stage.h"

CMapChip::CMapChip()
{
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXMatrixIdentity(&mRot);
	D3DXMatrixIdentity(&mWorld);
}

CMapChip::~CMapChip()
{
}
void CMapChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
{
	size = g_stage.GetMap()->GetSize();
	//まずはスキンモデルをロード。
	char modelPath[256];
	sprintf(modelPath, "Asset/model/%s.X", name);
	model.Init(pd3dDevice, modelPath);
	model.SetShadowReceiverFlag(true);
	
}

void CMapChip::Update()
{
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
	D3DXMatrixRotationQuaternion(&mRot, &rotation);
	mWorld = mRot * mWorld;
	
	
}
void CMapChip::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	model.Render(
		pd3dDevice,
		mWorld,
		mRot,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		numDiffuseLight,
		false
		);
}