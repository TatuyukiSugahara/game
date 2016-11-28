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
void CPipeChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
{
	//まずはスキンモデルをロード。
	char modelPath[256];
	sprintf(modelPath, "Asset/model/%s.X", name);
	model.Init(pd3dDevice, modelPath);
	model.SetShadowReceiverFlag(true);
	//ワールド行列のバッファを作成。
	D3DXMatrixRotationQuaternion(&mRot, &rotation);
	D3DXMatrixScaling(&mScale, Scale.x, Scale.y, Scale.z);
}

void CPipeChip::Update()
{
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);

}
void CPipeChip::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	mWorld = mScale * mRot * mWorld;
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