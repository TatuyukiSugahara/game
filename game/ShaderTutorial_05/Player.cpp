#include "stdafx.h"
#include "Player.h"
#include "CalcAABBSizeFromMesh.h"
#include "Stage.h"

//コンストラクタ
CPlayer::CPlayer()
{
	//初期化
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mScale);
	position = D3DXVECTOR3(1.0f, 1.0f, 0.0f);

	movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_aabbMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aabbMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	radius = 0.3f;

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
	/*CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;*/
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
	//Move2D();//移動2D
	Move3D();//移動3D
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
		D3DXMatrixScaling(&mScale, 1.5f, 1.5f, 1.5f);
		radius *= 1.5f*1.5f;
		IsIntersect.CollisitionInitialize(&position, radius);//あたり判定初期化
	}
	//ブロックと当たった？
	if (g_stage->GetNBlock()->Get2DBlock() == IsIntersect.getCollisionObj()
		&& IsIntersect.gethit() == true)
	{
		g_stage->GetNBlock()->SetState(no);
	}
	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_positionからの移動量(あたり判定)
	//AABB
	m_aabbMax += IsIntersect.GetAddPos();
	m_aabbMin += IsIntersect.GetAddPos();

	State();//アニメーション状態変更

	//ワールド行列の更新。
	animation.Update(1.0f / 60.0f);
	skinmodel.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(2.0f, 2.0f, 2.0f));
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

void CPlayer::Move2D()
{
	movespeed.x = g_pad.GetLStickXF() * MOVE_SPEED;
}

void CPlayer::Move3D()
{
	bool isTurn = false;

	static D3DXVECTOR3 dirX(1.0f, 0.0f, 0.0f);
	static D3DXVECTOR3 dirZ(0.0f, 0.0f, 1.0f);
	D3DXVECTOR3 dirpad(g_pad.GetLStickXF(), 0.0f, g_pad.GetLStickYF());

	D3DXVECTOR3 addmove(0.0f, 0.0f, 0.0f);

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
	if (g_pad.IsPress(enButtonB))
	{
		movespeed.x = addmove.x * MOVE_SPEED * 1.5f;
		movespeed.z = addmove.z * MOVE_SPEED * 1.5f;
		return;
	}
	movespeed.x = addmove.x * MOVE_SPEED;
	movespeed.z = addmove.z * MOVE_SPEED;

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
			movespeed.y += 18.0f;
		}
		else
		{
			movespeed.y += 15.0f;
		}
		state = PlayerIsJump;
		animation.PlayAnimation(PlayerIsJump,0.05f);

	}

}

void CPlayer::State()
{
	//動いているかつ地面についている？
	if (fabs(D3DXVec3Length(&movespeed)) >= 0.001f && IsIntersect.GetGround() == true)
	{
		if (state != PlayerRun)
		{
			state = PlayerRun;
			animation.PlayAnimation(PlayerRun, 0.3);
		}
	}
	//地面についていて動いていない
	if (IsIntersect.GetGround() == true && fabs(D3DXVec3Length(&movespeed)) <= 0.001f)
	{
		if (state != PlayerStay)
		{
			//着地時
			if (state == PlayerJumpNow)
			{
				state = PlayerJumpWas;
				animation.PlayAnimation(PlayerJumpWas, 0.3f);
			}
			//ステイ状態
			if (!animation.IsPlay() || state == PlayerRun)
			{
				state = PlayerStay;
				animation.PlayAnimation(PlayerStay, 0.3);
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
	}
}

void CPlayer::Died()
{
	if (position.y <= -10.0f)
	{
		scene = GameScene::Result;
	}
}

