#include "stdafx.h"
#include "ResultCamera.h"


//コンストラクタ。
CResultCamera::CResultCamera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//デストラクタ
CResultCamera::~CResultCamera()
{
}

//カメラの更新処理。
void CResultCamera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}
//カメラの初期化。
void CResultCamera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 1.0f, -8.0);
	vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	toPos = vEyePt - vLookatPt;						//視点 - 注視点
	CResultCameradir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Update();
}