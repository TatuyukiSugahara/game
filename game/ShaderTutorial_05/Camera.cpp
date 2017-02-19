#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
#include "pad\Pad.h"
#include "Stage.h"

//コンストラクタ。
Camera::Camera()
{
	Near = 0.1f;
	Far = 1000.0f;
	aspect = 960.0f / 580.0f;
}
//デストラクタ
Camera::~Camera()
{
}

//カメラの更新処理。
void Camera::Update()
{
	if (g_scenemanager->GetNomber() == StageBoss)
	{

		BossCamera();
	}
	else{
		//プレイヤー追尾
		D3DXVECTOR3 Pos = D3DXVECTOR3(g_stage->GetPlayer()->GetPos().x, vEyePt.y, vEyePt.z);
		vEyePt = g_stage->GetPlayer()->GetPos() + toPos;
		vLookatPt = g_stage->GetPlayer()->GetPos();
	}
	
	
	/*if (fabs(g_pad.GetRStickXF()) > 0.0f)
	{
		RotTransversal(g_pad.GetRStickXF() * 0.1f);
	}
	if (fabs(g_pad.GetRStickYF()) > 0.0f)
	{
		RotLongitudinal(g_pad.GetRStickYF() * 0.1f);
	}
	*/
	cameradir = toPos;
	cameradir.y = 0.0f;
	D3DXVec3Normalize(&cameradir, &cameradir);


	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, /*D3DX_PI / 4*/ D3DXToRadian(Angle), aspect, Near, Far);
	
	D3DXMatrixInverse(&viewMatrixRotInv, NULL, &viewMatrix);
	mRot = viewMatrixRotInv;
	mRot.m[3][0] = 0.0f;
	mRot.m[3][1] = 0.0f;
	mRot.m[3][2] = 0.0f;
	mRot.m[3][3] = 1.0f;
	D3DXMatrixTranspose(&viewMatrixRotInv, &mRot);

	//3Dサウンドのリスナーはカメラ。
	g_soundengine->SetListenerPosition(g_stage->GetPlayer()->GetPos());
	const D3DXMATRIX& m = mRot;
	g_soundengine->SetListenerFront({ m.m[2][0], m.m[2][1], m.m[2][2] });
	g_soundengine->SetListenerUp({ m.m[1][0], m.m[1][1], m.m[1][2] });

}
//カメラの初期化。
void Camera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 5.0f, -8.5f);
	vLookatPt = D3DXVECTOR3(0.0f, 1.8f, 0.0f);
	vUpVec = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	toPos = vEyePt - vLookatPt;						//視点 - 注視点
	cameradir = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Angle = 45.0f;									//画角
	bosstime = 0.0f;
	Update();
}
//============================================================
//カメラが横に回転。
//============================================================
void Camera::RotTransversal(float roty)
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

void Camera::RotLongitudinal(float rotx)
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

void Camera::BossCamera()
{
	if (g_stage->GetBoss()->Start() == true)
	{
		if (bosstime < 1.0f)
		{
			g_stage->BossMusic();
			g_stage->GetBossKatto()->SetKatto(true);
			D3DXVECTOR3 to = D3DXVECTOR3(g_stage->GetBoss()->GetPos().x, g_stage->GetBoss()->GetPos().y,0.0f) - vEyePt;
			if (to.x >= 3.0f)
			{
				D3DXVec3Normalize(&to, &to);
				vEyePt += D3DXVECTOR3(to.x, 0.0f, 0.0f);
				vLookatPt += D3DXVECTOR3(to.x, 0.0f, 0.0f);
			}
			bosstime += 1.0f / 60.0f;
		}
		else if (bosstime >= 1.0f && bosstime <= 2.0f)
		{
			g_stage->GetBossKatto()->SetKatto(false);
			D3DXVECTOR3 to = D3DXVECTOR3(g_stage->GetPlayer()->GetPos().x, 5.0f, 0.0f) - vEyePt;
			if (to.x <= 0.1f && to.y <= 0.1f)
			{
				D3DXVec3Normalize(&to, &to);
				vEyePt += D3DXVECTOR3(to.x, to.y, 0.0f);
				vLookatPt += D3DXVECTOR3(to.x, to.y, 0.0f);
			}
			if (Angle < 90.0f)
			{
				Angle++; //ボス戦時のみ画角ひろげる。
			}
			bosstime += 1.0f / 60.0f;
		}
		else if (bosstime >= 2.0f)
		{
			g_stage->GetBoss()->SetCameraFlag(true);
			//プレイヤー追尾
			D3DXVECTOR3 Pos = D3DXVECTOR3(g_stage->GetPlayer()->GetPos().x, vEyePt.y, vEyePt.z);
			vEyePt = g_stage->GetPlayer()->GetPos() + toPos;
			vLookatPt = g_stage->GetPlayer()->GetPos();
		}
		if (g_stage->GetBoss()->GetState() == BossDead)
		{
			if (Angle > 45.0f)
			{
				Angle--; //ボス撃破時画角狭める。
			}
		}
	}
	else
	{
		//プレイヤー追尾
		D3DXVECTOR3 Pos = D3DXVECTOR3(g_stage->GetPlayer()->GetPos().x, vEyePt.y, vEyePt.z);
		vEyePt = g_stage->GetPlayer()->GetPos() + toPos;
		vLookatPt = g_stage->GetPlayer()->GetPos();
	}
}