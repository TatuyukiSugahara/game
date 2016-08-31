#pragma once
#include "stdafx.h"
#include "Stage.h"

SCollisionInfo collisionInfoTable2D[] = {
#include "Collision2D_stage01.h"
};

CStage g_stage;

/*!-----------------------------------------------------------------------------
*@brief	���C�g���X�V�B
-----------------------------------------------------------------------------*/
void CStage::UpdateLight()
{
	light.Update();
}

void CStage::Initialize()
{
	CreateCollision2D();
	Add2DRigidBody(ARRAYSIZE(collisionInfoTable2D));
	//���C�g���������B
	light.Init();
	//�u���b�N������
	block.Init(g_pd3dDevice);
	//�͂Ăȃ{�b�N�X������
	hanatebox.Init(g_pd3dDevice);
	//�L�m�R������
	kinoko.Init(g_pd3dDevice);
	//�v���C���[������
	player.Init(g_pd3dDevice);
	//�J�����̏������B
	camera.Init(&player);
	
}

void CStage::Update()
{
	//���C�g�̍X�V�B
	UpdateLight();
	//�u���b�N���X�V
	block.Update();
	//�͂Ăȃ{�b�N�X�X�V
	hanatebox.Update();
	//�L�m�R�X�V
	if (hanatebox.GetItem() == true && kinoko.GetKinoko() == false)
	{
		kinoko.Update();
	}
	//�v���C���[���X�V�B
	player.Update();
	//�J�����̍X�V
	camera.Update();
}

void CStage::Render()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();
	//�u���b�N��`��
	block.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//�͂Ăȃ{�b�N�X�`��
	hanatebox.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	//�L�m�R
	if (hanatebox.GetItem() == true && kinoko.GetKinoko() == false)
	{
		kinoko.Render(
			g_pd3dDevice,
			camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			light.GetLightDirection(),
			light.GetLightColor(),
			light.GetambientLight(),
			light.GetLightNum()
			);
	}
	//�v���C���[��`��
	player.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);
	// �V�[���̕`��I���B

	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CStage::Release()
{
	//�u���b�N�����[�X
	block.Release();
	//�͂Ăȃ{�b�N�X�����[�X
	hanatebox.Release();
	//�L�m�R�����[�X
	kinoko.Release();
	//�v���C���[�����[�X
	player.Release();
}

void CStage::CreateCollision2D()
{
	int arraySize = ARRAYSIZE(collisionInfoTable2D);
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionInfoTable2D[i];
		//�����ō��̂Ƃ���o�^����B
		//���̂��������B
		{
			//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;

			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			m_myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
			m_rigidBody2D[i] = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			//g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);

		}
	}
}

void CStage::Add2DRigidBody(int arraySize)//���[���h�ɒǉ��B
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		arraySize;
		for (int i = 0; i < arraySize; i++)
		{
			g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
		}
	}
}