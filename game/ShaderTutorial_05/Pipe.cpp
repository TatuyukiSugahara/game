#include "stdafx.h"
#include "Pipe.h"

//コンストラクタ
CPipe::CPipe()
{
	//初期化。

	D3DXMatrixIdentity(&mWorld);
	position.x = 3.0f;
	position.y = 0.25f;
	position.z = 0.0f;
}
//デストラクタ
CPipe::~CPipe()
{
}
//初期化。
void CPipe::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/pipe.x");
}
//更新。
void CPipe::Update()
{
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CPipe::Render(
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
void CPipe::Release()
{
	model.Release();
}