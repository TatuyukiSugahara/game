#include "stdafx.h"
#include "Player.h"
#include "CalcAABBSizeFromMesh.h"
#include "Stage.h"
#include "Sound\SoundSource.h"
#include "ResultScene.h"

//コンストラクタ
CPlayer::CPlayer()
{
	//初期化
	D3DXMatrixIdentity(&mWorld);
	position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);		//初期位置
	movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//初期移動速度
	Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);			//初期スケール
	addmove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aabbMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aabbMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	radius = 0.3f;
	friction = 0.2f;
	state = PlayerStay;
}
//デストラクタ
CPlayer::~CPlayer()
{
}
//初期化。
void CPlayer::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	//ライトを初期化。
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, 0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, 0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 0.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.6f, 0.6f, 0.6f, 0.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 0.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.5f, 0.5f, 0.5f, 0.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.4f, 0.4f, 0.4f, 1.0f));

	//モデルをロード。
	modelData.LoadModelData("Asset/model/Unity.X", &animation);

	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	animation.PlayAnimation(0, 0.3);
	animation.SetAnimationEndTime(2, 0.79f);
	animation.SetAnimationEndTime(PlayerIsJump, 0.33f);
	animation.SetAnimationEndTime(PlayerJumpNow, 0.016);
	animation.SetAnimationEndTime(PlayerJumpWas, 0.33f);
	animation.SetAnimationLoopFlag(PlayerIsJump, false);
	animation.SetAnimationLoopFlag(PlayerJumpWas, false);


	IsIntersect.CollisitionInitialize(&position,radius);//あたり判定初期化

	//AABB
	CalcAABBSizeFromMesh(modelData.GetOrgMeshFirst(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;
	//ターン
	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	turn.Initialize();
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(false);
}
//更新。
void CPlayer::Update()
{
	if (g_pad.IsPress(enButtonB))
	{
		Move(7.5f);//移動
	}
	else
	{
		Move(5.0f);//移動
	}
	
	Jump();//ジャンプ
	Died();//死亡
	//天井と当たった？＆＆当たったのは,はてなボックス？
	if (IsIntersect.gethit() == true
		&& IsIntersect.getCollisionObj() == g_stage->GetHatena()->Get2DHatena())
	{
		g_stage->GetHatena()->SetState(hit);
		g_stage->GetKinoko()->SetState(Leave);//キノコ出現
	}
	//キノコとった？&&小さい状態？
	if (g_stage->GetKinoko()->GetKinoko() == true && radius == 0.3f)
	{
		D3DXVec3Scale(&Scale, &Scale, 1.5f);
		radius = 0.45;
		IsIntersect.CollisitionInitialize(&position, radius);//あたり判定初期化
	}
	
	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_positionからの移動量(あたり判定)
	//AABB
	m_aabbMax += IsIntersect.GetAddPos();
	m_aabbMin += IsIntersect.GetAddPos();

	State();//アニメーション状態変更

	//Bダッシュ時のアニメーション速度
	if (g_pad.IsPress(enButtonB))
	{
		animation.SetAnimationSpeedRate(2.0f);
	}
	else//通常時
	{
		animation.SetAnimationSpeedRate(1.0f);
	}
	animation.Update(1.0f / 60.0f);
	//ワールド行列の更新。
	skinmodel.UpdateWorldMatrix(position, rotation, Scale);
}
//描画。
void CPlayer::Render(
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	bool isDrawToShadowMap
	)
{
	/*D3DXMATRIX mRot;
	D3DXMATRIX AddRot;
	D3DXMatrixRotationQuaternion(&mRot, &rotation);
	D3DXMatrixRotationY(&AddRot, D3DXToRadian(-90.0f));
	D3DXMatrixMultiply(&mRot, &mRot, &AddRot);
	mWorld = mScale * mRot * mWorld;*/
	skinmodel.Draw(&viewMatrix, &projMatrix, isDrawToShadowMap);
}
//開放。
void CPlayer::Release()
{
}

void CPlayer::Move(float maxmove)
{
	bool isTurn = false;

	static D3DXVECTOR3 dirX(1.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 dirZ(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 dirpad(g_pad.GetLStickXF(), 0.0f, g_pad.GetLStickYF());

	

	addmove.x = dirX.x * dirpad.x - dirZ.x * dirpad.z;
	addmove.z = dirX.z * dirpad.x - dirZ.z * dirpad.z;
	
	//カメラが向いている方向に進む。
	dirZ = g_stage->GetCamera()->GetCameraDir();
	D3DXVec3Normalize(&addmove, &addmove);
	//カメラの向いている方向と、上ベクトルとの外積を計算すると横移動のベクトルが求まる。
	D3DXVec3Cross(&dirX, &dirZ, &D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	if (D3DXVec3Length(&addmove) > 0.0f){
		D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		m_targetAngleY = acos(D3DXVec3Dot(&forward, &addmove));
		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &forward, &addmove);
		if (axis.x > 0.0f)
		{
			m_targetAngleY *= -1.0f;
		}
		isTurn = true;
		m_currentAngleY = turn.Update(isTurn, m_targetAngleY);
		D3DXQuaternionRotationAxis(&rotation, &axis, m_currentAngleY);
	}
	D3DXVECTOR3 v1;//現在の進行方向
	D3DXVec3Normalize(&v1, &movespeed);
	D3DXVECTOR3 v2;//次の進行方向
	D3DXVec3Normalize(&v2, &addmove);
	//内積
	float naiseki = D3DXVec3Dot(&v1, &v2);
	//移動量があるなら
	if (D3DXVec3Length(&addmove) > 0.0f)
	{
		friction = 0.8f + 2.6f * (1.0f - fabs(naiseki));
	}
	else
	{
		friction = 0.4f;
	}
	//速度の上限
	D3DXVECTOR3 moveSpeedXZ = movespeed;
	moveSpeedXZ.y = 0.0f;
	D3DXVec3Normalize(&v1, &moveSpeedXZ);
	/*if (!IsIntersect.GetGround()){
		addmove *= 0.2f;
	}*/
	if (D3DXVec3Length(&moveSpeedXZ) <= maxmove || D3DXVec3Dot(&v1, &v2) < 0.0f)
	{
		movespeed.x += addmove.x;
		movespeed.z += addmove.z;
	}

	
	if (IsIntersect.GetGround())
	{
		//地面で移動中
		D3DXVECTOR3 masatu(0.0f, 0.0f, 0.0f);
		D3DXVec3Normalize(&masatu, &movespeed);
		masatu *= -friction;
		if (D3DXVec3Length(&moveSpeedXZ) < D3DXVec3Length(&masatu))
		{
			masatu = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}
		movespeed.x += masatu.x;
		movespeed.z += masatu.z;
	}
}

void CPlayer::Jump()
{
	if (g_pad.IsTrigger(EnButton::enButtonA)
		&& state != PlayerIsJump
		&& state != PlayerJumpNow
		)
	{
		if (g_pad.IsPress(EnButton::enButtonB))
		{
			movespeed.y = 18.0f;
		}
		else
		{
			movespeed.y = 15.0f;
		}
		CSoundSource* SEjump = new CSoundSource;
		SEjump->Init("Asset/Sound/jump.wav");
		SEjump->Play(false);
		SEjump->SetVolume(0.25f);
		state = PlayerIsJump;
		animation.PlayAnimation(PlayerIsJump,0.05f);

	}

}

void CPlayer::State()
{
	//動いているかつ地面についている？
	if (fabs(D3DXVec3Length(&movespeed)) >= 0.1f && IsIntersect.GetGround() == true)
	{
		if (state != PlayerRun)
		{
			state = PlayerRun;
			animation.PlayAnimation(PlayerRun, 0.3);
		}
	}
	//地面についていて動いていない
	if (IsIntersect.GetGround() == true && fabs(D3DXVec3Length(&movespeed)) <= 0.1f)
	{
		if (state != PlayerStay)
		{
			//着地時
			if (state == PlayerJumpNow)
			{
				state = PlayerJumpWas;
				animation.PlayAnimation(PlayerJumpWas, 0.3f);
				friction = 0.8f;
			}
			//ステイ状態
			if (!animation.IsPlay() || state == PlayerRun)
			{
				state = PlayerStay;
				animation.PlayAnimation(PlayerStay, 0.3);
				movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}

		}
		
	}
	//ジャンプ中
	if (!IsIntersect.GetGround())
	{
		if (state != PlayerJumpNow && !animation.IsPlay())
		{
			state = PlayerJumpNow;
			animation.PlayAnimation(PlayerJumpNow, 0.2f);
		}
		/*if (D3DXVec3Length(&addmove) > 0.0f)
		{
			D3DXVECTOR3 masatu(0.0f, 0.0f, 0.0f);
			D3DXVec3Normalize(&masatu, &movespeed);
			D3DXVECTOR3 moveSpeedXZ = movespeed;
			moveSpeedXZ.y = 0.0f;
			masatu *= -friction;
			if (D3DXVec3Length(&moveSpeedXZ) > D3DXVec3Length(&masatu))
			{
				movespeed.x += masatu.x;
				movespeed.z += masatu.z;
			}
			
		}*/
	}
}

void CPlayer::Died()
{
	if (position.y <= -10.0f)
	{
		CSoundSource* SEDeath = new CSoundSource;
		SEDeath->Init("Asset/Sound/death.wav");
		SEDeath->Play(false);
		g_resultscene.SetState(ResultState::Death);
		scene = GameScene::Result;
	}
}

