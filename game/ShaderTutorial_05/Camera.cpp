#include "stdafx.h"
#include "Camera.h"
#include "Player.h"

//コンストラクタ。
Camera::Camera()
{
	Near = 0.1f;
	Far = 100.0f;
	aspect = 1.0f;
}
//デストラクタ
Camera::~Camera()
{
}

//カメラの更新処理。
void Camera::Update()
{
	//プレイヤー追尾
	D3DXVECTOR3 Pos = D3DXVECTOR3(player->GetPos().x, player->GetPos().y, GetEyePt().z);
	vEyePt = Pos;
	vLookatPt = player->GetPos();

	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);
}
//カメラの初期化。
void Camera::Init(CPlayer* player)
{
	vEyePt = D3DXVECTOR3(0.0f, 1.0f, -15.0f);
	vLookatPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	this->player = player;

	Update();
}