#include "stdafx.h"
#include "RotationGimmick.h"
#include "Map\Stage.h"
#include "Frame\BallCollision.h"


CRotationGimmick::CRotationGimmick()
{
	
	vector = CConst::Vec3Right;					//回転用
	originPos = D3DXVECTOR3(15.0f, 3.0f, 0.0f);	//オリジナルのポジション
	position[0] = originPos + vector * 1.0f;	//1つめ
	position[1] = originPos + vector * 1.5f;	//2つめ
	position[2] = originPos + vector * 2.0f;	//3つめ
	scale = CConst::Vec3One;					//大きさ
	D3DXMatrixIdentity(&rotation);				//回転
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

		skinModel[i].Init(&modelData[i]);
		skinModel[i].SetLight(&light);

		skinModel[i].SetDrawToShadowMap(false);
		skinModel[i].SetShadowReceiverFlag(false);
		skinModel[i].SetNormalMap(false);
		skinModel[i].SetSpecularMap(false);
	}

	
}
//更新。
void CRotationGimmick::Update()
{
	D3DXMatrixRotationZ(&rotation, D3DXToRadian(1.0f));
	D3DXVec3TransformCoord(&vector, &vector, &rotation);
	position[0] = originPos + vector * 1.0f;
	position[1] = originPos + vector * 1.5f;
	position[2] = originPos + vector * 2.0f;
	
	for (int i = 0; i < 3; i++)
	{
		skinModel[i].UpdateWorldMatrix(position[i], CConst::QuaternionIdentity, scale);
	}
	
}
//描画。
void CRotationGimmick::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	for (int i = 0; i < 3; i++)
	{
		skinModel[i].Render(&viewMatrix, &projMatrix, false);
	}
}
