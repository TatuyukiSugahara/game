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
	if (normalMap != NULL)
	{
		normalMap->Release();
	}
}
void CCoinChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
{
	//�m�[�}���}�b�v���[�h
	HRESULT hr = D3DXCreateTextureFromFileA(
		g_pd3dDevice,
		"Asset/model/goldCoin_Normal.jpg",
		&normalMap);
	if (FAILED(hr))
	{
		MessageBox(NULL, "�e�N�X�`���̃��[�h�Ɏ��s���܂����B�w�肵���p�X�����������m�F���Ă��������B", "�G���[", MB_OK);
	}
	if (normalMap != NULL) {
		//�@���}�b�v�̓ǂݍ��݂����������̂ŁACSkinModel�ɖ@���}�b�v��ݒ肷��B
		skinmodel.SetNormalMap(normalMap);
	}

	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 10.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 10.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.4f, 1.4f, 0.6f, 1.0f));

	//�܂��̓X�L�����f�������[�h�B
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

	

	coinget = false;
}

void CCoinChip::Update()
{
	if (coinget == false)
	{
		//�R�C���ƃv���C���[�������������B
		if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 0.37f, 0.5f) == true)
		{
			coinget = true;
			g_scenemanager->AddNum();
			//�T�E���h
			CSoundSource* soundSource = new CSoundSource;
			soundSource->Init("Asset/Sound/coin.wav");
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
		//���[���h�s��̍X�V�B
		static float rot = 0.0f;
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), rot+=0.005f);
		
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