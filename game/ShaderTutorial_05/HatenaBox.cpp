#include "stdafx.h"
#include "HatenaBox.h"

//コンストラクタ
CHatenaBox::CHatenaBox()
{
	//初期化。

	D3DXMatrixIdentity(&mWorld);
	position.x = 8.0f;
	position.y = 4.0f;
	position.z = 0.0f;
}
//デストラクタ
CHatenaBox::~CHatenaBox()
{
}
//初期化。
void CHatenaBox::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "hatena_box.x");
}
//更新。
void CHatenaBox::Update()
{
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CHatenaBox::Render(
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
		numDiffuseLight
		);
}
//開放。
void CHatenaBox::Release()
{
	model.Release();
}