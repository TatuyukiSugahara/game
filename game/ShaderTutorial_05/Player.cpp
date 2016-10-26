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
	position = D3DXVECTOR3(1.0f, 2.0f, 0.0f);

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
	//���C�g���������B
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	//���f�������[�h�B
	modelData.LoadModelData("Asset/model/Unity.X", &animation);

	skinmodel.Init(&modelData);
	skinmodel.SetLight(&light);
	animation.PlayAnimation(0, 0.3);

	IsIntersect.CollisitionInitialize(&position,radius);//�����蔻�菉����

	//AABB
	/*CalcAABBSizeFromMesh(model.GetMesh(), m_aabbMin, m_aabbMax);
	m_aabbMin += position;
	m_aabbMax += position;*/
	//�^�[��
	m_currentAngleY = 0.0f;
	m_targetAngleY = 0.0f;
	turn.Initialize();
	AnimationRun = false;			//�A�j���[�V�����������Ă���H
	skinmodel.SetShadowReceiverFlag(false);
	skinmodel.SetDrawToShadowMap(false);
}
//�X�V�B
void CPlayer::Update()
{
	//Move2D();//�ړ�2D
	Move3D();//�ړ�3D
	Jump();//�W�����v
	Died();//���S
	//�V��Ɠ��������H�������������̂�,�͂Ăȃ{�b�N�X�H
	if (IsIntersect.gethit() == true
		&& IsIntersect.getCollisionObj() == g_stage.GetHatena()->Get2DHatena())
	{
		g_stage.GetHatena()->SetState(hit);
		g_stage.GetKinoko()->SetState(Leave);//�L�m�R�o��
	}
	//�L�m�R�Ƃ����H&&��������ԁH
	if (g_stage.GetKinoko()->GetKinoko() == true && radius == 0.3f)
	{
		D3DXMatrixScaling(&mScale, 1.5f, 1.5f, 1.5f);
		radius *= 1.5f*1.5f;
		IsIntersect.CollisitionInitialize(&position, radius);//�����蔻�菉����
	}
	//�u���b�N�Ɠ��������H
	if (g_stage.GetNBlock()->Get2DBlock() == IsIntersect.getCollisionObj()
		&& IsIntersect.gethit() == true)
	{
		g_stage.GetNBlock()->SetState(no);
	}
	IsIntersect.Intersect(&position, &movespeed, callbackList);//m_position����̈ړ���(�����蔻��)
	//AABB
	m_aabbMax += IsIntersect.GetAddPos();
	m_aabbMin += IsIntersect.GetAddPos();

	//�����Ă��邩�n�ʂɂ��Ă���H
	if (fabs(D3DXVec3Length(&movespeed)) >= 0.001f && IsIntersect.GetGround() == true)
	{
		state = PlayerRun;
		if (AnimationRun == false)//�A�j���[�V�������?
		{
			animation.PlayAnimation(PlayerRun, 0.3);
			AnimationRun = true;
		}
	}
	else
	{
		AnimationRun = false;
	}
	if (IsIntersect.GetGround() && fabs(D3DXVec3Length(&movespeed)) <= 0.001f)//�n�ʂɂ��Ă��ē����Ă��Ȃ�
	{
		state = PlayerStay;
		animation.PlayAnimation(PlayerStay, 0.3);
	}

	//���[���h�s��̍X�V�B
	animation.Update(1.0f / 60.0f);
	skinmodel.UpdateWorldMatrix(position, rotation, D3DXVECTOR3(2.0f, 2.0f, 2.0f));
}
//�`��B
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
//�J���B
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

	//�J�����������Ă�������ɐi�ށB
	dirZ = g_stage.GetCamera()->GetCameraDir();
	D3DXVec3Normalize(&addmove, &addmove);
	//�J�����̌����Ă�������ƁA��x�N�g���Ƃ̊O�ς��v�Z����Ɖ��ړ��̃x�N�g�������܂�B
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
		&& state != PlayerJump)
	{
		if (g_pad.IsPress(EnButton::enButtonB))
		{
			movespeed.y += 18.0f;
		}
		else
		{
			movespeed.y += 15.0f;
		}
		state = PlayerJump;
		animation.PlayAnimation(PlayerJump, 0.3);

	}

}

void CPlayer::Died()
{
	if (position.y <= -10.0f)
	{
		PostQuitMessage(0);
	}
}

