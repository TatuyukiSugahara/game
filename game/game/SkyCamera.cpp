#include "stdafx.h"
#include "SkyCamera.h"
#include "Player.h"
#include "pad\Pad.h"
#include "Stage.h"

//コンストラクタ。
CSkyCamera::CSkyCamera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//デストラクタ
CSkyCamera::~CSkyCamera()
{

}

//カメラの更新処理。
void CSkyCamera::Update()
{
	//プレイヤー追尾
	D3DXVECTOR3 Pos = D3DXVECTOR3(g_stage->GetPlayer()->GetPos().x, vEyePt.y, vEyePt.z);
	vEyePt = g_stage->GetPlayer()->GetPos() + toPos;
	vLookatPt = g_stage->GetPlayer()->GetPos();

	//背景を回転させる
	RotTransversal(0.001f);

	cameradir = toPos;
	cameradir.y = 0.0f;
	D3DXVec3Normalize(&cameradir, &cameradir);


	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, aspect, Near, Far);

	D3DXMatrixInverse(&viewMatrixRotInv, NULL, &viewMatrix);
	rot = viewMatrixRotInv;
	rot.m[3][0] = 0.0f;
	rot.m[3][1] = 0.0f;
	rot.m[3][2] = 0.0f;
	rot.m[3][3] = 1.0f;
	D3DXMatrixTranspose(&viewMatrixRotInv, &rot);
}
//カメラの初期化。
void CSkyCamera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 5.0f, -8.5f);
	vLookatPt = D3DXVECTOR3(0.0f, 1.8f, 0.0f);
	vUpVec = CConst::Vec3Up;
	toPos = vEyePt - vLookatPt;						//視点 - 注視点
	cameradir = CConst::Vec3Zero;
	Update();
}
//============================================================
//カメラが横に回転。
//============================================================
void CSkyCamera::RotTransversal(float roty)
{
	D3DXQUATERNION mAxisY;
	D3DXVECTOR4 v;
	D3DXQuaternionRotationAxis(&mAxisY, &vUpVec, roty);
	D3DXMatrixRotationQuaternion(&rot, &mAxisY);
	D3DXVec3Transform(&v, &toPos, &rot);
	toPos.x = v.x;
	toPos.y = v.y;
	toPos.z = v.z;
}

void CSkyCamera::RotLongitudinal(float rotx)
{
	D3DXVECTOR3 Cross;
	D3DXQUATERNION zAxis;
	D3DXVECTOR4 v;
	D3DXVec3Cross(&Cross, &vUpVec, &toPos);
	D3DXQuaternionRotationAxis(&zAxis, &Cross, rotx);
	D3DXMatrixRotationQuaternion(&rot, &zAxis);
	D3DXVec3Transform(&v, &toPos, &rot);
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