#include "stdafx.h"
#include "TitleCamera.h"


//コンストラクタ。
CTitleCamera::CTitleCamera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//デストラクタ
CTitleCamera::~CTitleCamera()
{
}

//カメラの更新処理。
void CTitleCamera::Update()
{
	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}
//カメラの初期化。
void CTitleCamera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 1.0f, -8.0);
	vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	toPos = vEyePt - vLookatPt;						//視点 - 注視点
	CTitleCameradir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Update();
}