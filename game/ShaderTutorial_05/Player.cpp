#include "stdafx.h"
#include "Player.h"

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//������
	D3DXMatrixIdentity(&mWorld);
	position.x = 1.0f;
	position.y = 5.0f;
	position.z = 0.0f;

	movespeed.x = 0.0f;
	movespeed.y = 0.0f;
	movespeed.z = 0.0f;

	state = PlayerStay;
}
//�f�X�g���N�^
CPlayer::~CPlayer()
{
}
//�������B
void CPlayer::Init(LPDIRECT3DDEVICE9 pd3dDevice)
{
	model.Init(pd3dDevice, "unitychan.x");
	IsIntersect.CollisitionInitialize(&position);//�����蔻�菉����
}
//�X�V�B
void CPlayer::Update()
{
	Move();//�ړ�
	Jump();//�W�����v
	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_position����̈ړ���(�����蔻��)
	//���[���h�s��̍X�V�B
	D3DXMatrixTranslation(&mWorld, position.x, position.y, position.z);
}
//�`��B
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
//�J���B
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