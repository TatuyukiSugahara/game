#include "stdafx.h"
#include "Player.h"
#include "CalcAABBSizeFromMesh.h"
#include "Stage.h"

//�R���X�g���N�^
CPlayer::CPlayer()
{
	//������
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixIdentity(&mScale);
	position = D3DXVECTOR3(1.0f, 5.0f, 0.0f);

	movespeed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_aabbMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_aabbMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	radius = 0.3f;

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
	IsIntersect.CollisitionInitialize(&position,radius);//�����蔻�菉����

	//AABB
	CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;

}
//�X�V�B
void CPlayer::Update()
{
	Move();//�ړ�
	Jump();//�W�����v

	if (g_stage.GetKinoko()->GetKinoko() == true && radius == 0.3f)
	{
		D3DXMatrixScaling(&mScale, 1.5f, 1.5f, 1.5f);
		radius *= 1.5f*1.5f;
		IsIntersect.CollisitionInitialize(&position, radius);//�����蔻�菉����
	}

	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_position����̈ړ���(�����蔻��)

	m_aabbMax += IsIntersect.GetAddPos();
	m_aabbMin += IsIntersect.GetAddPos();

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
	mWorld = mScale * mWorld;

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

	if (GetAsyncKeyState(VK_RIGHT))
	{
		movespeed.x += MOVE_SPEED;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		movespeed.x -= MOVE_SPEED;
	}
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