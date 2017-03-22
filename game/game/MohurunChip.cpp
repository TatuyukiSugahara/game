#include "stdafx.h"
#include "MohurunChip.h"
#include "Stage.h"
#include "BallCollision.h"

SkinModelData*	CMohurunChip::orgSkinModelData = NULL;	//オリジナルスキンモデルデータ。

CMohurunChip::CMohurunChip()
{
	scale = D3DXVECTOR3(1.4f, 1.4f, 1.4f);
	rotation = CConst::QuaternionIdentity;
	moveSpeed = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);				//初期移動速度
}


CMohurunChip::~CMohurunChip()
{
}

//初期化。
void CMohurunChip::Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice)
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

	//スキンモデルをロード。
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

	state = MohurunState::Alive;

	param.texturePath = "Asset/model/star.png";
	param.w = 0.5f;
	param.h = 0.5f;
	param.intervalTime = 0.2f;
	param.life = 0.5f;
	param.gravity = D3DXVECTOR3(0.0f, -0.016f, 0.0f);
	param.initSpeed = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	parFlag = false;
	parTime = 0;
	count = 0;
	skinModel.SetDrawToShadowMap(false);
	skinModel.SetShadowReceiverFlag(true);
	skinModel.SetNormalMap(false);
	skinModel.SetSpecularMap(false);
	//キャラクターコントローラー初期化
	characterController.Init(0.3f, 1.0f, position);
	characterController.SetGravity(-30.0f);
	//サウンド初期化
	seEnemyDeath.reset(new CSoundSource);
	seEnemyDeath->Init("Asset/Sound/enemyDeath.wav");
}
//更新。
void CMohurunChip::Update()
{
	if (state == MohurunState::Alive)
	{

		D3DXVECTOR3 playerPos = g_stage->GetPlayer()->GetPos();
		float toLength = D3DXVec3Length(&D3DXVECTOR3(position - playerPos));

		if (fabs(toLength) < 10.0f)
		{
			
			if (BallCollision(position - D3DXVECTOR3(0.0f, 0.2f, 0.0f),
				g_stage->GetPlayer()->GetPos() + D3DXVECTOR3(0.0f, -0.1f, 0.0f), 0.7f, 0.3f) == true)
			{
				g_stage->GetPlayer()->SetLifeState(CPlayer::Life::Died);
			}
			if (BallCollision(position + D3DXVECTOR3(0.0f, 0.2f, 0.0f),
				g_stage->GetPlayer()->GetPos() + D3DXVECTOR3(0.0f, -0.2f, 0.0f), 0.7f, 0.3f) == true)
			{
				scale = D3DXVECTOR3(1.4f, 0.2f, 1.4f);
				parFlag = true;
				state = MohurunState::Dead;
				seEnemyDeath->Play(false);
				seEnemyDeath->SetVolume(0.25f);
				g_stage->GetPlayer()->SetMoveSpeed(D3DXVECTOR3(g_stage->GetPlayer()->GetMoveSpeed().x,
					-g_stage->GetPlayer()->GetMoveSpeed().y * 0.5f,
					g_stage->GetPlayer()->GetMoveSpeed().z));
				param.pos = position;

				CParticleEmitter* particleEmitter = new CParticleEmitter;
				particleEmitter->Init(param);
				particleEmitterList.push_back(particleEmitter);
			}

			

			characterController.SetMoveSpeed(moveSpeed);
			characterController.Execute();
			moveSpeed = characterController.GetMoveSpeed();
			position = characterController.GetPosition();
			characterController.SetPosition(position);
			if (characterController.IsKabe())
			{
				moveSpeed.x *= -1.0f;
			}
		}
		//ワールド行列の更新。
		animation.Update(CConst::DeltaTime);
		D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));
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
			for (auto p : particleEmitterList)
			{
				delete(p);
			}
			particleEmitterList.clear();
		}
		count++;
	}
}
//描画。
void CMohurunChip::Render(
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
