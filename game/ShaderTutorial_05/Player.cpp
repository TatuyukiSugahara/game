#include "stdafx.h"
#include "Player.h"

//コンストラクタ
CPlayer::CPlayer()
{
	//初期化
	D3DXMatrixIdentity(&mWorld);
	position.x = 1.0f;
	position.y = 5.0f;
	position.z = 0.0f;

	movespeed.x = 0.0f;
	movespeed.y = 0.0f;
	movespeed.z = 0.0f;

	state = PlayerStay;
}
//デストラクタ
CPlayer::~CPlayer()
{
}
//初期化。
void CPlayer::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "unitychan.x");
	IsIntersect.CollisitionInitialize(&position);//あたり判定初期化
}
//更新。
void CPlayer::Update()
{
	Move();//移動
	Jump();//ジャンプ
	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_positionからの移動量(あたり判定)
	//ワールド行列の更新。
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//描画。
void CPlayer::Render(
	LPDIRECT3DDEVICE9 pd3dDevice,
	D3DXMATRIX viewMatrix,
	D3DXMATRIX projMatrix,
	D3DXVECTOR4* diffuseLightDirection,
	D3DXVECTOR4* diffuseLightColor,
	D3DXVECTOR4	 ambientLight,
	int numDiffuseLight
	)
{
	model.Render(
		pd3dDevice,
		mWorld,
		mRotation,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		numDiffuseLight
		);
}
//開放。
void CPlayer::Release()
{
	model.Release();
}

void CPlayer::Move()
{
	if (movespeed.x >= 0.001f)
	{
		state = PlayerRun;
	}
	else if (movespeed.x <= 0.001f)
	{
		state = PlayerStay;
	}
	movespeed.x = g_pad.GetLStickXF() * 5.0f;
	//movespeed.y = g_pad.GetLStickYF();
	
	//D3DXVec3Scale(&movespeed, &movespeed, 0.1f);

	if (GetAsyncKeyState(VK_RIGHT))
	{
		movespeed.x += MOVE_SPEED;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		movespeed.x -= MOVE_SPEED;
	}

	//position += movespeed;
}

void CPlayer::Jump()
{
	if (state != PlayerJump)
	{
		
		if (g_pad.IsTrigger(EnButton::enButtonA))
		{
			movespeed.y += 8.0f;
			state = PlayerJump;
		}
	}
	
}