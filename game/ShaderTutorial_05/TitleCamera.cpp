#include "stdafx.h"
#include "TitleCamera.h"


//�R���X�g���N�^�B
CTitleCamera::CTitleCamera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//�f�X�g���N�^
CTitleCamera::~CTitleCamera()
{
}

//�J�����̍X�V�����B
void CTitleCamera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}
//�J�����̏������B
void CTitleCamera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 1.0f, -8.0);
	vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	toPos = vEyePt - vLookatPt;						//���_ - �����_
	CTitleCameradir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Update();
}