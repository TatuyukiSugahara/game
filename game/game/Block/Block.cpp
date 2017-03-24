#include "stdafx.h"
#include "Block.h"

//コンストラクタ
CBlock::CBlock()
{
	//初期化。

	D3DXMatrixIdentity(&mWorld);
	position.x = 0.0f;
	position.y =- 0.5f;
	position.z = 0.0f;
}
//デストラクタ
CBlock::~CBlock()
{
}
//初期化。
void CBlock::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/stage1.x");
	model.SetShadowReceiverFlag(true);
}
//更新。
void CBlock::Update()
{
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CBlock::Render(
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
		mRotation,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		numDiffuseLight,
		false
		);
}
//開放。
void CBlock::Release()
{
	model.Release();
}