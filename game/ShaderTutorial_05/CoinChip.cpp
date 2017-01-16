#include "stdafx.h"
#include "CoinChip.h"
#include "Stage.h"
#include "BallCollision.h"
#include "Sound\SoundSource.h"

CCoinChip::CCoinChip()
{
	position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
}

CCoinChip::~CCoinChip()
{
}
void CCoinChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
{
	size = g_stage->GetMap()->GetSize();

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

	//まずはスキンモデルをロード。
	char modelPath[256];
	sprintf(modelPath, "Asset/model/%s.X", name);
	modelData.LoadModelData(modelPath, &animation);

	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	skinmodel.SetShadowReceiverFlag(true);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetNormalMap(false);
	skinmodel.SetSpecularMap(false);

	

	coinget = false;
}

void CCoinChip::Update()
{
	if (coinget == false)
	{
		//コインとプレイヤーが当たったか。
		if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 0.37, 0.5f) == true)
		{
			coinget = true;
			g_stage->GetCoinNum()->AddNum(1);
			//サウンド
			CSoundSource* soundSource = new CSoundSource;
			soundSource->Init("Asset/Sound/coin.wav");
			soundSource->Play(false);
		}
		//ワールド行列の更新。
		static float rot = 0.0f;
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rot+=0.005f);
		skinmodel.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}
}
void CCoinChip::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix)
{
	if (coinget == false)
	{
		skinmodel.Draw(&viewMatrix, &projMatrix, false);
	}
}