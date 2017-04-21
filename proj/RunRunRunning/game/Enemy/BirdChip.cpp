#include "stdafx.h"
#include "BirdChip.h"
#include "Map\Stage.h"
#include "Frame\BallCollision.h"
#include "Sound\SoundSource.h"

SkinModelData*	CBirdChip::orgSkinModelData = NULL;	//オリジナルスキンモデルデータ。

CBirdChip::CBirdChip()
{
	scale = CConst::Vec3One;
	rotation = CConst::QuaternionIdentity;
}

CBirdChip::~CBirdChip()
{

}
void CBirdChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
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
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//まずはスキンモデルをロード。
	char modelPath[256];
	sprintf(modelPath, "Asset/model/%s.X", name);

	if (orgSkinModelData == NULL) {
		orgSkinModelData = new SkinModelData;
		orgAnimation = new Animation;
		orgSkinModelData->LoadModelData(modelPath, orgAnimation);
	}
	//オリジナルのモデルデータからクローンモデルを作成。
	modelData.CloneModelData(*orgSkinModelData, &animation);

	skinModel.Init(&modelData);
	skinModel.SetLight(&light);
	animation.PlayAnimation(0);

	state = BirdState::Alive;

	param.texturePath = "Asset/model/star.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.life = 0.5f;
	param.gravity = D3DXVECTOR3(0.0f, -0.016f, 0.0f);
	param.initSpeed = D3DXVECTOR3(0.0f, 1.0f, 0.0f);


	parFlag = false;
	parTime = 0;

	count = 0;
	skinModel.SetDrawToShadowMap(false);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetNormalMap(false);
	skinModel.SetSpecularMap(false);

	seEnemyDeath.reset( new CSoundSource);
	seEnemyDeath->Init("Asset/Sound/enemyDeath.wav");

}

void CBirdChip::Update()
{
	if (state == BirdState::Alive)
	{


		D3DXVECTOR3 playerPos = g_stage->GetPlayer()->GetPos();
		float toLength = D3DXVec3Length(&D3DXVECTOR3(position - playerPos));

		if (toLength < 10.0f)
		{
			//ワールド行列の更新。
			animation.Update(CConst::DeltaTime);
			if (BallCollision(position + D3DXVECTOR3(0.0f, -0.2f, 0.0f), g_stage->GetPlayer()->GetPos() + D3DXVECTOR3(0.0f, -0.3f, 0.0f), 0.4f, 0.4f) == true)
			{
				g_stage->GetPlayer()->SetLifeState(CPlayer::Life::Died);
			}
			if (BallCollision(position + D3DXVECTOR3(0.0f, 0.2f, 0.0f),
				g_stage->GetPlayer()->GetPos() + D3DXVECTOR3(0.0f, -0.2f, 0.0f), 0.4f, 0.4f) == true)
			{
				scale = D3DXVECTOR3(1.0f, 0.2f, 1.0f);
				parFlag = true;
				state = BirdState::Dead;
				
				seEnemyDeath->Play(false);
				seEnemyDeath->SetVolume(0.25f);
				g_stage->GetPlayer()->SetMoveSpeed(D3DXVECTOR3(g_stage->GetPlayer()->GetMoveSpeed().x,
					-g_stage->GetPlayer()->GetMoveSpeed().y * 0.5f,
					g_stage->GetPlayer()->GetMoveSpeed().z));

				param.pos = position;

				CParticleEmitterPtr particleEmitter(new CParticleEmitter);
				particleEmitter->Init(param);
				particleEmitterList.push_back(particleEmitter);
			}

			position.x -= 0.05f;
			
		}
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(-90.0f));
		skinModel.UpdateWorldMatrix(position, rotation, scale);

	}
	if (parFlag == true)
	{
		if (MAXPAR >= parTime)
		{
			parTime++;
			for (auto p : particleEmitterList)
			{
				p->Update();
			}
		}
		else
		{
			parFlag = false;
			particleEmitterList.clear();
		}
		count++;
	}
}
void CBirdChip::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	if (count < 50)
	{
		skinModel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
	}
	else if (MAXPAR >= parTime)
	{
		for (auto p : particleEmitterList)
		{
			p->Render(viewMatrix, projMatrix);
		}
	}
}