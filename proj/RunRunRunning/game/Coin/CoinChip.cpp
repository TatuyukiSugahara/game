#include "stdafx.h"
#include "CoinChip.h"
#include "Map\Stage.h"
#include "Frame\BallCollision.h"
#include "Sound\SoundSource.h"

CCoinChip::CCoinChip()
{
	position = CConst::Vec3Zero;
	scale = D3DXVECTOR3(1.0f, 1.0f, 2.0f);
	scaleShadow = D3DXVECTOR3(1.0f, 1.0f, 4.0f);
	rotation = CConst::QuaternionIdentity;
}

CCoinChip::~CCoinChip()
{
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

	skinModel.Init(modelData);
	skinModel.SetLight(&light);
	skinModel.SetShadowReceiverFlag(false);
	skinModel.SetDrawToShadowMap(false);
	skinModel.SetNormalMap(true);
	skinModel.SetSpecularMap(false);

	soundSource.reset(new CSoundSource);
	soundSource->Init("Asset/Sound/coin.wav");

	coinGet = false;
}

void CCoinChip::Update()
{
	if (coinGet == false)
	{
		//コインとプレイヤーが当たったか。
		if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 0.75f, 0.75) == true)
		{
			coinGet = true;
			g_scenemanager->AddNum();
			g_stage->GetCoinSprite()->SetRotFlag(true);
			g_stage->GetPlayer()->SetDiedTime(0.0f);
			//サウンド
			soundSource->SetVolume(0.25f);
			soundSource->Play(false);
		}
		for (int i = 0; i < g_stage->GetMohu()->GetTableSize(); i++)
		{
			if (BallCollision(position, g_stage->GetMohu()->GetPos(i), 0.37f, 0.5f) == true)
			{
				coinGet = true;
			}
		}
	}
}
void CCoinChip::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	if (coinGet == false)
	{
		if (isDrawToShadowMap == true)
		{
			skinModel.UpdateWorldMatrix(position, rotation, scaleShadow);
		}
		else
		{
			skinModel.UpdateWorldMatrix(position, rotation, scale);
		}
		skinModel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
	}
}