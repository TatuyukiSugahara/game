#include "stdafx.h"
#include "Boss.h"
#include "Stage.h"
#include "BallCollision.h"

//コンストラクタ
CBoss::CBoss()
{
	//初期化。
	position = D3DXVECTOR3(75.0f, 3.0f, 0.0f);
	movespeed = CConst::Vec3Zero;
	scale = CConst::Vec3One;
	rotation = CConst::QuaternionIdentity;
	D3DXQuaternionRotationAxis(&rotation, &CConst::Vec3Up, CConst::Radian180);
	life = 5;
}
//デストラクタ
CBoss::~CBoss()
{
}
//初期化。
void CBoss::Init()
{
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(1.5f, 1.5f, 1.5f, 1.0f));

	modelData.LoadModelData("Asset/model/boss.X", &animation);
	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	animation.PlayAnimation(0, 0.3f);
	animation.SetAnimationLoopFlag((int)BossState::Falter, false);

	skinmodel.SetShadowReceiverFlag(true);
	skinmodel.SetDrawToShadowMap(false);
	skinmodel.SetNormalMap(false);
	skinmodel.SetSpecularMap(false);

	param.texturePath = "Asset/model/star.png";
	param.w = 1.0f;
	param.h = 1.0f;
	param.intervalTime = 0.2f;
	param.life = 0.5f;
	param.gravity = D3DXVECTOR3(0.0f, -0.16f, 0.0f);
	param.initSpeed = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	parflag = false;
	parTime = 0;

	state = BossState::Move;

	characterController.Init(1.0f, 1.5f, position);
	characterController.SetGravity(-100.0f);

	//ターン
	currentAngleY = 0.0f;
	targetAngleY = 0.0f;
	turn.Init();
}
//更新。
void CBoss::Update()
{
	if (cameraflag == true)
	{
		switch (state)
		{
		case BossState::Move:
			Move();
			break;
		case BossState::Falter:
			Falter();
			break;
		case BossState::Dead:
			Dead();
			break;
		}

		Particle();
		characterController.SetMoveSpeed(movespeed);
		characterController.Execute();
		movespeed = characterController.GetMoveSpeed();
		position = characterController.GetPosition();
		characterController.SetPosition(position);
		
	}
	animation.Update(CConst::DeltaTime);
	skinmodel.UpdateWorldMatrix(position, rotation, scale);
}
//描画。
void CBoss::Render(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	if (state != BossState::Dead)
	{
		skinmodel.Render(&viewMatrix, &projMatrix, isDrawToShadowMap);
	}
	if (MAXPAR >= parTime && parflag == true)
	{
		for (auto p : particleEmitterList)
		{
			p->Render(viewMatrix, projMatrix);
		}
	}
}

void CBoss::Move()
{
	bool isTurn = false;

	//プレイヤーに向かって移動
	D3DXVECTOR3 ToPos = g_stage->GetPlayer()->GetPos() - position;
	ToPos.y = 0.0f;
	D3DXVec3Normalize(&ToPos, &ToPos);
	movespeed = ToPos * 3.0f;

	//プレイヤーに向く。
	D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	targetAngleY = acos(D3DXVec3Dot(&forward, &ToPos));
	D3DXVECTOR3 axis;
	D3DXVec3Cross(&axis, &forward, &ToPos);
	if (axis.x > 0.0f)
	{
		targetAngleY *= -1.0f;
	}
	isTurn = true;
	currentAngleY = turn.Update(isTurn, targetAngleY);
	D3DXQuaternionRotationAxis(&rotation, &axis, currentAngleY);

	//プレイヤーと衝突時プレイヤー死亡
	if (BallCollision(position - D3DXVECTOR3(0.0f, 0.2f, 0.0f),
		g_stage->GetPlayer()->GetPos(), 1.3f, 0.3f) == true)
	{
		g_stage->GetPlayer()->SetLifeState(CPlayer::Life::Died);
	}
	//プレイヤーに頭を踏まれるとダメージ１
	if (BallCollision(position + D3DXVECTOR3(0.0f, 2.3f, 0.0f),
		g_stage->GetPlayer()->GetPos() + D3DXVECTOR3(0.0f, -0.2f, 0.0f), 1.3f, 0.3f) == true)
	{
		g_stage->GetPlayer()->SetMoveSpeed(D3DXVECTOR3(g_stage->GetPlayer()->GetMoveSpeed().x,
			g_stage->GetPlayer()->GetMoveSpeed().y * -1.0f,
			g_stage->GetPlayer()->GetMoveSpeed().z));

		CSoundSource* SEenemyDeath = new CSoundSource;
		SEenemyDeath->Init("Asset/Sound/enemyDeath.wav");
		SEenemyDeath->Play(false);

		parflag = true;
		param.pos = D3DXVECTOR3(position.x, position.y += 3.0f, position.z);
		CParticleEmitterPtr particleEmitter(new CParticleEmitter);
		particleEmitter->Init(param);
		particleEmitterList.push_back(particleEmitter);
		if (state != BossState::Falter)
		{
			animation.PlayAnimation((int)BossState::Falter, 0.05f);
		}
		state = BossState::Falter;
		life--;
		if (life == 0)
		{
			scale = D3DXVECTOR3(1.0f, 0.2f, 1.0f);
			state = BossState::Dead;
		}
	}
	if (position.y <= -5.0f)
	{
		state = BossState::Dead;
	}
}

void CBoss::Falter()
{
		static float count = 0.0f;
		if (count >= 2.0f)
		{
			count = 0.0f;
			animation.PlayAnimation((int)BossState::Move,0.2f);
			state = BossState::Move;
		}
		count += CConst::DeltaTime;
}

void CBoss::Dead()
{
	static float time = 0.0f;
	g_stage->MusicStop();
	
	g_stage->GetBossClear()->SetClear(true);
	if (time >= 3.0f)
	{
		g_stage->GetPlayer()->Clear();
	}
	if (time >= 5.0f)
	{
		time = 0.0f;
		g_stage->GetBossClear()->SetClear(false);
		g_scenemanager->SetNumber((int)CSceneManager::StageNumber::Stage1);
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Title);
	}
	time += CConst::DeltaTime;
}

void CBoss::Particle()
{
	if (parflag == true)
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
			parTime = 0;
			parflag = false;
			
			particleEmitterList.clear();
		}
	}
}

//ボスとの戦闘がスタートするフラグ
bool CBoss::Start()
{
	//ボスの初期ポジションとプレイヤーのポジションの球が当たったら
	if (BallCollision(D3DXVECTOR3(75.0f, 3.0f, 0.0f), g_stage->GetPlayer()->GetPos(), 22.5f, 0.5f))
	{
		return true;
	}
	return false;
}