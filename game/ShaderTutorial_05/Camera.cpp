#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
#include "pad\Pad.h"

//�R���X�g���N�^�B
Camera::Camera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//�f�X�g���N�^
Camera::~Camera()
{
}

//�J�����̍X�V�����B
void Camera::Update()
{
	//�v���C���[�ǔ�
	D3DXVECTOR3 Pos = D3DXVECTOR3(player->GetPos().x, vEyePt.y, vEyePt.z);
	vEyePt = player->GetPos() + toPos;
	vLookatPt = player->GetPos();
	if (fabs(g_pad.GetRStickXF()) > 0.0f)
	{
		RotTransversal(g_pad.GetRStickXF() * 0.1f);
	}
	/*if (fabs(g_pad.GetRStickXF()) < 0.0f)
	{
		RotTransversal(0.05);
	}*/
	if (fabs(g_pad.GetRStickYF()) > 0.0f)
	{
		RotLongitudinal(g_pad.GetRStickYF() * 0.1f);
	}
	/*if (fabs(g_pad.GetRStickYF()) < 0.0f)
	{
		RotLongitudinal(0.05);
	}*/
	
	

	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}
//�J�����̏������B
void Camera::Init(CPlayer* player)
{
	vEyePt = D3DXVECTOR3(0.0f, 1.0f, -15.0f);
	vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	toPos = vEyePt - vLookatPt;						//���_ - �����_
	this->player = player;

	Update();
}
//============================================================
//�J���������ɉ�]�B
//============================================================
void Camera::RotTransversal(float roty)
{
	D3DXMATRIX mRot;
	D3DXQUATERNION mAxisY;
	D3DXVECTOR4 v;
	D3DXQuaternionRotationAxis(&mAxisY, &vUpVec, roty);
	D3DXMatrixRotationQuaternion(&mRot, &mAxisY);
	D3DXVec3Transform(&v, &toPos, &mRot);
	toPos.x = v.x;
	toPos.y = v.y;
	toPos.z = v.z;
	//SetEyePt(vLookatPt + toPos);
}

void Camera::RotLongitudinal(float rotx)
{
	D3DXVECTOR3 Cross;
	D3DXQUATERNION zAxis;
	D3DXMATRIX mRot;
	D3DXVECTOR4 v;
	D3DXVec3Cross(&Cross, &vUpVec, &toPos);
	D3DXQuaternionRotationAxis(&zAxis, &Cross, rotx);
	D3DXMatrixRotationQuaternion(&mRot, &zAxis);
	D3DXVec3Transform(&v, &toPos, &mRot);
	D3DXVECTOR3 toPosOld = toPos;
	toPos.x = v.x;
	toPos.y = v.y;
	toPos.z = v.z;
	D3DXVECTOR3 toPosDir;
	D3DXVec3Normalize(&toPosDir, &toPos);
	if (toPosDir.y < -0.5f)
	{
		toPos = toPosOld;
	}
	else if (toPosDir.y > 0.8f)
	{
		toPos = toPosOld;
	}

}
