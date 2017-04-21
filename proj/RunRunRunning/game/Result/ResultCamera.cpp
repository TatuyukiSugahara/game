#include "stdafx.h"
#include "ResultCamera.h"


//�R���X�g���N�^�B
CResultCamera::CResultCamera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//�f�X�g���N�^
CResultCamera::~CResultCamera()
{
}

//�J�����̍X�V�����B
void CResultCamera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}
//�J�����̏������B
void CResultCamera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 1.0f, -8.0);
	vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	toPos = vEyePt - vLookatPt;						//���_ - �����_
	CResultCameradir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Update();
}