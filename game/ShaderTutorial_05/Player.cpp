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
	model.Init(pd3dDevice, "Asset/model/unitychan.x");
	model.SetShadowReceiverFlag(false);
	IsIntersect.CollisitionInitialize(&position,radius);//�����蔻�菉����

	//AABB
	CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;
	//�^�[��
	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	turn.Initialize();
}
//�X�V�B
void CPlayer::Update()
{
	//Move2D();//�ړ�2D
	Move3D();//�ړ�3D
	Jump();//�W�����v
	Died();//���S

	//�V��Ɠ��������H�������������̂�,�͂Ăȃ{�b�N�X�H
	if (IsIntersect.gethit() == true && IsIntersect.getCollisionObj() == g_stage.GetHatena()->Get2DHatena())
	{
		g_stage.GetHatena()->SetItem(true);
	}
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
	int numDiffuseLight,
	bool isDrawToShadowMap
	)
{
	D3DXMATRIX mRot;
	D3DXMatrixRotationY(&mRot, m_currentAngleY);
	mWorld = mScale * mRot * mWorld;

	model.Render(
		pd3dDevice,
		mWorld,
		mRotation,
		viewMatrix,
		projMatrix,
		diffuseLightDirection,
		diffuseLightColor,
		ambientLight,
		numDiffuseLight,
		isDrawToShadowMap
		);
}
//�J���B
void CPlayer::Release()
{
	model.Release();
}

void CPlayer::Move2D()
{
	if (fabs(movespeed.x) >= 0.001f)
	{
		state = PlayerRun;
	}
	else
	{
		state = PlayerStay;
	}
	movespeed.x = g_pad.GetLStickXF() * MOVE_SPEED;
}

void CPlayer::Move3D()
{
	if (fabs(D3DXVec3Length(&movespeed)) > 0.01f)
	{
		state = PlayerRun;
	}
	else
	{
		state = PlayerStay;
	}
	bool isTurn = false;
	Camera* cam = g_stage.GetCamera();
	D3DXMATRIX mCam = cam->GetViewMatrix();
	//�J�����s��̋t�s��������āA���[���h�s������߂�B
	D3DXMatrixInverse(&mCam, NULL, &mCam);
	//X���W
	D3DXVECTOR3 xAxisInCamera;
	xAxisInCamera.x = mCam.m[0][0];
	xAxisInCamera.y = mCam.m[0][1];
	xAxisInCamera.z = mCam.m[0][2];
	xAxisInCamera.y = 0.0f;
	D3DXVec3Normalize(&xAxisInCamera, &xAxisInCamera);
	//Y���W
	D3DXVECTOR3 yAxisInCamera;
	yAxisInCamera.x = mCam.m[1][0];
	yAxisInCamera.y = mCam.m[1][1];
	yAxisInCamera.z = mCam.m[1][2];
	yAxisInCamera.x = 0.0f;
	yAxisInCamera.z = 0.0f;
	D3DXVec3Normalize(&yAxisInCamera, &yAxisInCamera);
	//Z���W
	D3DXVECTOR3 zAxisInCamera;
	zAxisInCamera.x = mCam.m[2][0];
	zAxisInCamera.y = mCam.m[2][1];
	zAxisInCamera.z = mCam.m[2][2];
	zAxisInCamera.y = 0.0f;
	D3DXVec3Normalize(&zAxisInCamera, &zAxisInCamera);
	D3DXVECTOR3 add(0.0f, 0.0f, 0.0f);
	//�E
	if (g_pad.GetLStickXF() > 0.0f)
	{
		add += xAxisInCamera * MOVE_SPEED;
	}
	//��
	if (g_pad.GetLStickXF() < 0.0f)
	{
		add -= xAxisInCamera * MOVE_SPEED;
	}
	//��
	if (g_pad.GetLStickYF() > 0.0f)
	{
		add += zAxisInCamera * MOVE_SPEED;
	}
	if (g_pad.GetLStickYF() < 0.0f)
	{
		add -= zAxisInCamera * MOVE_SPEED;
	}
	D3DXVECTOR3 dir(0.0f,0.0f,0.0f);
	dir = add - dir;
	dir.y = 0.0f;
	D3DXVec3Normalize(&dir, &dir);

	movespeed.x = add.x;
	movespeed.z = add.z;

	D3DXVECTOR3 Axix(1.0f, 0.0f, 0.0f);
	m_targetAngleY = D3DXVec3Dot(&dir, &Axix);
	m_targetAngleY = acosf(m_targetAngleY);
	D3DXVECTOR3 v;
	D3DXVec3Cross(&v, &dir, &Axix);
	if (v.x > 0.0f)
	{
		m_targetAngleY *= -1.0f;
	}
	isTurn = true;

	m_currentAngleY = turn.Update(isTurn, m_targetAngleY);
}

void CPlayer::Jump()
{
	if(IsIntersect.GetGround() == true)
	{
		
		if (g_pad.IsTrigger(EnButton::enButtonA))
		{
			movespeed.y += 8.0f;
			state = PlayerJump;
		}
	}
	
}

void CPlayer::Died()
{
	if (position.y <= -10.0f)
	{
		PostQuitMessage(0);
	}
}
