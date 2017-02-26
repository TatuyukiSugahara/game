#include "stdafx.h"
#include "SkyCamera.h"
#include "Player.h"
#include "pad\Pad.h"
#include "Stage.h"

//�R���X�g���N�^�B
CSkyCamera::CSkyCamera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//�f�X�g���N�^
CSkyCamera::~CSkyCamera()
{

}

//�J�����̍X�V�����B
void CSkyCamera::Update()
{
		//�v���C���[�ǔ�
		D3DXVECTOR3 Pos = D3DXVECTOR3(g_stage->GetPlayer()->GetPos().x, vEyePt.y, vEyePt.z);
		vEyePt = g_stage->GetPlayer()->GetPos() + toPos;
		vLookatPt = g_stage->GetPlayer()->GetPos();

	RotTransversal(0.001f);
	
	cameradir = toPos;
	cameradir.y = 0.0f;
	D3DXVec3Normalize(&cameradir, &cameradir);


	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);

	D3DXMatrixInverse(&viewMatrixRotInv, NULL, &viewMatrix);
	mRot = viewMatrixRotInv;
	mRot.m[3][0] = 0.0f;
	mRot.m[3][1] = 0.0f;
	mRot.m[3][2] = 0.0f;
	mRot.m[3][3] = 1.0f;
	D3DXMatrixTranspose(&viewMatrixRotInv, &mRot);
}
//�J�����̏������B
void CSkyCamera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 5.0f, -8.5f);
	vLookatPt = D3DXVECTOR3(0.0f, 1.8f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	toPos = vEyePt - vLookatPt;						//���_ - �����_
	cameradir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Update();
}
//============================================================
//�J���������ɉ�]�B
//============================================================
void CSkyCamera::RotTransversal(float roty)
{
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

void CSkyCamera::RotLongitudinal(float rotx)
{
	D3DXVECTOR3 Cross;
	D3DXQUATERNION zAxis;
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