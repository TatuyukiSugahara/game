#include "stdafx.h"
#include "Kinoko.h"

//コンストラクタ
CKinoko::CKinoko()
{
	//初期化。

	D3DXMatrixIdentity(&mWorld);
	position.x = 8.0f;
	position.y = 5.0f;
	position.z = 0.0f;

	movespeed.x = 0.0f;
	movespeed.y = 0.0f;
	movespeed.z = 0.0f;
}
//デストラクタ
CKinoko::~CKinoko()
{
}
//初期化。
void CKinoko::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "kinoko.x");
	IsIntersect.CollisitionInitialize(&position);//あたり判定初期化
}
//更新。
void CKinoko::Update()
{
	movespeed.x = 0.1f;
	D3DXVec3Scale(&movespeed, &movespeed, 0.1f);
	
	position += movespeed;

	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_positionからの移動量(あたり判定)
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CKinoko::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	g_pd3dDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
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
	g_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}
//開放。
void CKinoko::Release()
{
	model.Release();
}