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
	if (soundSource)
	{
		delete soundSource;
	}
}
void CCoinChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
{

	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.4f, 1.4f, 0.6f, 1.0f));

	//まずはスキンモデルをロード。
	char modelPath[256];
	sprintf(modelPath, "Asset/model/%s.X", name);
	modelData = g_skinmodeldataManager->LoadSkinModelData(modelPath);
	//modelData.LoadModelData(modelPath, &animation);

	skinmodel.Init(modelData);
	skinmodel.SetLight(&light);
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetNormalMap(true);
	skinmodel.SetSpecularMap(false);

	soundSource = new CSoundSource;
	soundSource->Init("Asset/Sound/coin.wav");

	coinget = false;
}

void CCoinChip::Update()
{
	if (coinget == false)
	{
		//コインとプレイヤーが当たったか。
		if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 0.75f, 0.75) == true)
		{
			coinget = true;
			g_scenemanager->AddNum();
			g_stage->GetCoinSprite()->SetRotFlag(true);
			//サウンド
			soundSource->SetVolume(0.25f);
			soundSource->Play(false);
		}
		for (int i = 0; i < g_stage->GetMohu()->GetTableSize(); i++)
		{
			if (BallCollision(position, g_stage->GetMohu()->GetPos(i), 0.37f, 0.5f) == true)
			{
				coinget = true;
			}
		}
	}
}
void CCoinChip::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	if (coinget == false)
	{
		if (isDrawToShadowMap == true)
		{
			skinmodel.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 4.0f));
		}
		else
		{
			skinmodel.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(1.0f, 1.0f, 2.0f));
		}
		skinmodel.Draw(&viewMatrix, &projMatrix, isDrawToShadowMap);
	}
}