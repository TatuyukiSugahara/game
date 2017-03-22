#include "stdafx.h"
#include "Camera.h"
#include "Player.h"
#include "pad\Pad.h"
#include "Stage.h"

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
	//�{�X�펞�̃J����
	if (g_scenemanager->GetNumber() == CSceneManager::StageNumber::StageBoss)
	{

		BossCamera();
	}
	//�ʏ�X�e�[�W�ł̃J����
	else
	{
		//�v���C���[�ǔ�
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
	cameraDir = toPos;
	cameraDir.y = 0.0f;
	D3DXVec3Normalize(&cameraDir, &cameraDir);


	D3DXMatrixLookAtLH(&viewMatrix, &vEyePt, &vLookatPt, &vUpVec);
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, /*D3DX_PI / 4*/ D3DXToRadian(angle), aspect, Near, Far);
	
	D3DXMatrixInverse(&viewMatrixRotInv, NULL, &viewMatrix);
	rot = viewMatrixRotInv;
	rot.m[3][0] = 0.0f;
	rot.m[3][1] = 0.0f;
	rot.m[3][2] = 0.0f;
	rot.m[3][3] = 1.0f;
	D3DXMatrixTranspose(&viewMatrixRotInv, &rot);

	//3D�T�E���h�̃��X�i�[�̓J�����B
	g_soundengine->SetListenerPosition(g_stage->GetPlayer()->GetPos());
	const D3DXMATRIX& m = rot;
	g_soundengine->SetListenerFront({ m.m[2][0], m.m[2][1], m.m[2][2] });
	g_soundengine->SetListenerUp({ m.m[1][0], m.m[1][1], m.m[1][2] });

}
//�J�����̏������B
void Camera::Init()
{
	vEyePt = D3DXVECTOR3(0.0f, 5.0f, -8.5f);
	vLookatPt = D3DXVECTOR3(0.0f, 1.8f, 0.0f);
	vUpVec = CConst::Vec3Up;
	toPos = vEyePt - vLookatPt;						//���_ - �����_
	cameraDir = CConst::Vec3Zero;
	angle = 45.0f;									//��p
	bossTime = 0.0f;
	Update();
}
//============================================================
//�J���������ɉ�]�B
//============================================================
void Camera::RotTransversal(float roty)
{
	D3DXQUATERNION mAxisY;
	D3DXVECTOR4 v;
	D3DXQuaternionRotationAxis(&mAxisY, &vUpVec, roty);
	D3DXMatrixRotationQuaternion(&rot, &mAxisY);
	D3DXVec3Transform(&v, &toPos, &rot);
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

void Camera::BossCamera()
{
	if (g_stage->GetBoss()->Start() == true)
	{
		if (bossTime < 2.0f)
		{
			D3DXVECTOR3 targetCEye(g_stage->GetBoss()->GetPos() + toPos);			//�{�X�J�������_�B
			D3DXVECTOR3 currentCEye(g_stage->GetPlayer()->GetPos() + toPos);		//�v���C���[�J�������_�B
			D3DXVECTOR3 targetCLook(g_stage->GetBoss()->GetPos());					//�{�X�J���������_�B
			D3DXVECTOR3 currentCLook(g_stage->GetPlayer()->GetPos());				//�v���C���[�J���������_�B
			g_stage->GetPlayer()->SetPlyaerStop(true);
			g_stage->BossMusic();
			g_stage->GetBossKatto()->SetKatto(true);
			vEyePt = (targetCEye * (1.0f - cameraHokan) + currentCEye * cameraHokan);
			vLookatPt = (targetCLook * (1.0f - cameraHokan) + currentCLook * cameraHokan);
			toPos = vEyePt - vLookatPt;
			if (cameraHokan > 0.0f)
			{
				cameraHokan -= 0.01f;
			}
			bossTime += CConst::DeltaTime;
		}
		else if (bossTime >= 2.0f && bossTime < 4.0f)
		{
			D3DXVECTOR3 targetCEye(g_stage->GetBoss()->GetPos() + toPos);			//�{�X�J�������_�B
			D3DXVECTOR3 currentCEye(g_stage->GetPlayer()->GetPos() + D3DXVECTOR3(toPos.x, toPos.y, -17.0f));		//�v���C���[�J�������_�B
			D3DXVECTOR3 targetCLook(g_stage->GetBoss()->GetPos());					//�{�X�J���������_�B
			D3DXVECTOR3 currentCLook(g_stage->GetPlayer()->GetPos());				//�v���C���[�J���������_�B
			g_stage->GetBossKatto()->SetKatto(false);
			vEyePt = (targetCEye * (1.0f - cameraHokan) + currentCEye * cameraHokan);
			vLookatPt = (targetCLook * (1.0f - cameraHokan) + currentCLook * cameraHokan);
			if (cameraHokan < 1.0f)
			{
				cameraHokan += 0.01f;
			}
			if (cameraHokan == 1.0f)
			{
				toPos = vEyePt - vLookatPt;
			}
			bossTime += CConst::DeltaTime;
		}
		else if (bossTime >= 4.0f)
		{
			if (g_stage->GetPlayer()->GetPlayerStop() == true)
			{
				g_stage->GetPlayer()->SetPlyaerStop(false);
			}
			g_stage->GetBoss()->SetCameraFlag(true);
			//�v���C���[�ǔ�
			vEyePt = g_stage->GetPlayer()->GetPos() + toPos;
			vLookatPt = g_stage->GetPlayer()->GetPos();
		}
		if (g_stage->GetBoss()->GetState() == CBoss::BossState::Dead)
		{
			if (angle > 15.0f)
			{
				angle -= 0.2f; //�{�X���j����p���߂�B
			}
		}
	}
	else
	{
		//�v���C���[�ǔ�
		vEyePt = g_stage->GetPlayer()->GetPos() + toPos;
		vLookatPt = g_stage->GetPlayer()->GetPos();
	}
}