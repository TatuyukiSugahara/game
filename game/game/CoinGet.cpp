#include "stdafx.h"
#include "CoinGet.h"
#include "Stage.h"


CCoinGet::CCoinGet()
{
	position = D3DXVECTOR3(-4.8f, 3.07f, 0.0f);
	rotation = CConst::QuaternionIdentity;
	scale = D3DXVECTOR3(0.8f, 0.8f, 0.8f);
}


CCoinGet::~CCoinGet()
{
	if (normalMap != NULL)
	{
		normalMap->Release();
	}
}

void CCoinGet::Init()
{
	//ノーマルマップロード
	HRESULT hr = D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Asset/model/goldCoin_Normal.jpg",
		&normalMap);
	if (FAILED(hr))
	{
		MessageBox(NULL, "テクスチャのロードに失敗しました。指定したパスが正しいか確認してください。", "エラー", MB_OK);
	}
	if (normalMap != NULL) {
		//法線マップの読み込みが成功したので、CskinModelに法線マップを設定する。
		skinModel.SetNormalMap(normalMap);
	}

	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.2f, 1.2f, 0.6f, 1.0f));

	//まずはスキンモデルをロード。
	modelData.LoadModelData("Asset/model/coin.X", &animation);

	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	skinModel.SetShadowReceiverFlag(false);
	skinModel.SetDrawToShadowMap(false);
	skinModel.SetNormalMap(true);
	skinModel.SetSpecularMap(false);
}

void CCoinGet::Update()
{
	if (rot == true)
	{
		if (time <= 1.0f)
		{
			static float angle = 0.0f;
			if (angle >= 3.0f)
			{
				angle = 0.0f;
			}
			D3DXQuaternionRotationAxis(&rotation, &CConst::Vec3Up, angle += 0.05f);
			time += CConst::DeltaTime;
		}
		else
		{
			rot = false;
			time = 0.0f;
		}
		
	}
}

void CCoinGet::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	skinModel.UpdateWorldMatrix(position + g_stage->GetPlayer()->GetPos(), rotation, scale);
	skinModel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
}
