#include "stdafx.h"
#include "StageBack.h"

//コンストラクタ
CStageBack::CStageBack()
{
	//初期化。

	D3DXMatrixIdentity(&mWorld);
	position.x = 0.0f;
	position.y = 0.0f;
	position.z = 0.0f;
}
//デストラクタ
CStageBack::~CStageBack()
{
}
//初期化。
void CStageBack::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/sky.x");
}
//更新。
void CStageBack::Update()
{
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CStageBack::Render(
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
void CStageBack::Release()
{
	model.Release();
}