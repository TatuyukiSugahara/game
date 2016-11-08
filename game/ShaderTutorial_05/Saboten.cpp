#include "stdafx.h"
#include "Saboten.h"
#include "stage.h"

//コンストラクタ
CSaboten::CSaboten()
{
	//初期化。

	D3DXMatrixIdentity(&mWorld);
	position.x = 39.0f;
	position.y = 1.25f;
	position.z = 0.0f;
}
//デストラクタ
CSaboten::~CSaboten()
{
}
//初期化。
void CSaboten::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "Asset/model/sabo.x");
}
//更新。
void CSaboten::Update()
{
	BOOL hit;//ヒットしたか
	FLOAT distance;	//距離
	D3DXVECTOR3 dir = position - g_stage->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = g_stage->GetPlayer()->GetPos();
	D3DXVec3Normalize(&dir, &dir);
	D3DXMATRIX InverseMat;
	D3DXMATRIX InverseRot;
	D3DXMatrixInverse(&InverseMat, NULL, &mWorld);
	D3DXMatrixInverse(&InverseRot, NULL, &mRotation);

	D3DXVec3TransformCoord(&pos, &pos, &InverseMat);
	D3DXVec3TransformCoord(&dir, &dir, &InverseRot);

	D3DXIntersect(model.GetMesh(), &pos,
		&dir, &hit, NULL, NULL, NULL, &distance, NULL, NULL);
	if (hit)
	{
		if (fabs(distance) <= 0.1f)
		{
			MessageBox(NULL, "GAME OVER", 0, MB_OK);
			exit(0);
		}
	}
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CSaboten::Render(
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
void CSaboten::Release()
{
	model.Release();
}
