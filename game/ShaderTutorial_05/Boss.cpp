#include "stdafx.h"
#include "Boss.h"
#include "Stage.h"
#include "BallCollision.h"

//�R���X�g���N�^
CBoss::CBoss()
{
	//�������B
	position = D3DXVECTOR3(75.0f, 3.0f, 0.0f);
	movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	D3DXQuaternionRotationAxis(&rotation, &D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXToRadian(180.0f));
	
}
//�f�X�g���N�^
CBoss::~CBoss()
{
}
//�������B
void CBoss::Init()
{
	//���C�g���������B
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
	animation.SetAnimationLoopFlag(BossFalter, false);

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

	state = BossState::BossMove;;

	characterController.Init(1.0f, 1.5f, position);
	characterController.SetGravity(-100.0f);

	//�^�[��
	currentAngleY = 0.0f;
	targetAngleY = 0.0f;
	turn.Initialize();
}
//�X�V�B
void CBoss::Update()
{
	if (cameraflag == true)
	{
		switch (state)
		{
		case BossMove:
			Move();
			break;
		case BossFalter:
			Falter();
			break;
		case BossDead:
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
	animation.Update(1.0f / 60.0f);
	skinmodel.UpdateWorldMatrix(position, rotation, scale);
}
//�`��B
void CBoss::Render(D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap)
{
	if (state != BossState::BossDead)
	{
		skinmodel.Draw(&viewMatrix, &projMatrix, isDrawToShadowMap);
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

	//�v���C���[�Ɍ������Ĉړ�
	D3DXVECTOR3 ToPos = g_stage->GetPlayer()->GetPos() - position;
	ToPos.y = 0.0f;
	D3DXVec3Normalize(&ToPos, &ToPos);
	movespeed = ToPos * 3.0f;

	//�v���C���[�Ɍ����B
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

	//�v���C���[�ƏՓˎ��v���C���[���S
	if (BallCollision(position - D3DXVECTOR3(0.0f, 0.2f, 0.0f),
		g_stage->GetPlayer()->GetPos(), 1.3f, 0.3f) == true)
	{
		g_stage->GetPlayer()->SetLifeState(Life::Died);
	}
	//�v���C���[�ɓ��𓥂܂��ƃ_���[�W�P
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
		CParticleEmitter* particleEmitter = new CParticleEmitter;
		particleEmitter->Init(param);
		particleEmitterList.push_back(particleEmitter);
		if (state != BossState::BossFalter)
		{
			animation.PlayAnimation(BossFalter, 0.05f);
		}
		state = BossState::BossFalter;
		life--;
		if (life == 0)
		{
			scale = D3DXVECTOR3(1.0f, 0.2f, 1.0f);
			state = BossDead;
		}
	}
	if (position.y <= -5.0f)
	{
		state = BossDead;
	}
}

void CBoss::Falter()
{
		static float count = 0.0f;
		if (count >= 2.0f)
		{
			count = 0.0f;
			animation.PlayAnimation(BossMove,0.2f);
			state = BossState::BossMove;
		}
		count += 1.0f / 60.0f;
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
		g_scenemanager->SetNonber(Stage1);
		g_scenemanager->ChangeScene(Title);
	}
	time += 1.0f / 60.0f;
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
			for (auto p : particleEmitterList)
			{
				delete(p);
			}
			particleEmitterList.clear();
		}
	}
}

bool CBoss::Start()
{
	if (BallCollision(position, g_stage->GetPlayer()->GetPos(), 22.5f, 0.5f))
	{
		return true;
	}
	return false;
}