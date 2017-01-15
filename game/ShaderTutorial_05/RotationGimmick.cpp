#include "stdafx.h"
#include "RotationGimmick.h"
#include "Stage.h"
#include "BallCollision.h"


CRotationGimmick::CRotationGimmick()
{
	
	vector = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	originPos = D3DXVECTOR3(15.0f, 3.0f, 0.0f);
	position[0] = originPos + vector * 1.0f;
	position[1] = originPos + vector * 1.5f;
	position[2] = originPos + vector * 2.0f;
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	D3DXMatrixIdentity(&mRotation);
}


CRotationGimmick::~CRotationGimmick()
{
}

//初期化。
void CRotationGimmick::Init()
{
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.4f, 0.4f, 0.4f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//モデルをロード。
	for (int i = 0; i < 3; i++)
	{
		modelData[i].LoadModelData("Asset/model/coin.X", &animation);

		skinmodel[i].Init(&modelData[i]);
		skinmodel[i].SetLight(&light);

		skinmodel[i].SetDrawToShadowMap(false);
		skinmodel[i].SetShadowReceiverFlag(false);
		skinmodel[i].SetNormalMap(false);
		skinmodel[i].SetSpecularMap(false);
	}

	
}
//更新。
void CRotationGimmick::Update()
{
	D3DXMatrixRotationZ(&mRotation, D3DXToRadian(1.0f));
	D3DXVec3TransformCoord(&vector, &vector, &mRotation);
	position[0] = originPos + vector * 1.0f;
	position[1] = originPos + vector * 1.5f;
	position[2] = originPos + vector * 2.0f;
	
	for (int i = 0; i < 3; i++)
	{
		skinmodel[i].UpdateWorldMatrix(position[i], D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f), scale);
	}
	
}
//描画。
void CRotationGimmick::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	for (int i = 0; i < 3; i++)
	{
		skinmodel[i].Draw(&viewMatrix, &projMatrix, false);
	}
}
