#include "stdafx.h"
#include "HatenaBox.h"
#include "stage.h"
#include "CalcAABBSizeFromMesh.h"

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

	Item = false;
	//AABB
	CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;
	m_aabbMin += D3DXVECTOR3(0.2f, -0.3f, 0.2f);
	m_aabbMax -= D3DXVECTOR3(0.2f, 0.2f, 0.2f);
}
//更新。
void CHatenaBox::Update()
{
	/*  obj1の右側がobj2の左側より大きい　かつ
		obj1の左側がobj2の右側より小さい　かつ
		obj1の上側がobj2の下側より大きい　かつ
		obj1の下側がobj2の上側より小さい*/
	if (m_aabbMax.x > g_stage.GetPlayer()->GetAABBMin().x
		&& m_aabbMin.x < g_stage.GetPlayer()->GetAABBMax().x
		&& m_aabbMax.y > g_stage.GetPlayer()->GetAABBMin().y
		&& m_aabbMin.y < g_stage.GetPlayer()->GetAABBMax().y

		)
	{
		Item = true;
	}

	
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