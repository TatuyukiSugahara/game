#pragma once
#include "stdafx.h"
#include "Stage.h"

SCollisionInfo collisionInfoTable2D[] = {
#include "Collision2D_stage01.h"
};

CStage* g_stage;

/*!-----------------------------------------------------------------------------
*@brief	���C�g���X�V�B
-----------------------------------------------------------------------------*/
void CStage::UpdateLight()
{
	light.Update();
	lightback.Update();
}

void CStage::Init()
{
	g_physicsWorld = new CPhysicsWorld;
	g_physicsWorld->Init();			//�������[���h������
	memset(m_rigidBody2D, NULL, sizeof(m_rigidBody2D));
	memset(m_groundShape, NULL, sizeof(m_groundShape));
	g_stage = this;
	CreateCollision2D();
	Add2DRigidBody(ARRAYSIZE(collisionInfoTable2D));
	//���C�g���������B
	light.Init();
	//�J�����̏������B
	camera.Init();

	//�T�E���h�\�[�X���������B
	soundsource.InitStreaming("Asset/Sound/mario.wav");
	soundsource.Play(true);
	soundsource.SetVolume(0.5f);

	//�X�v���C�g������
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
	}

	//�w�i���C�g��������
	lightback.Init();
	//�X�e�[�W�w�i������
	stageback.Init(g_pd3dDevice);
	//�}�b�v������
	map.Init(g_pd3dDevice);
	//�v���C���[������
	player.Init(g_pd3dDevice);
	//���t�����G�l�~�[������
	mohurun.Init();
	//n�u���b�N������
	nblock.Init(g_pd3dDevice);
	//�����Ȃ��u���b�N������
	//noblock.Init();
	//�͂Ăȃ{�b�N�X������
	//hanatebox.Init(g_pd3dDevice);
	//�L�m�R������
	//kinoko.Init(g_pd3dDevice);
	//�y�Ǐ�����
	pipe.Init();
	//�S�[��������
	goal.Init(g_pd3dDevice);
	//�e������
	shadow.Create(512, 512);
	//�T�{�e��������
	//sabo.Init(g_pd3dDevice);
	//�R�C����������
	coin.Init();
	//�R�C���i���o�[������
	coinNumber.Init();	
	//�S�[���t���O������
	goalflag.Init();
	//�R�C���X�v���C�g������
	coinsprite.Init();
	//��������
	bird.Init();
	//���z������
	sun.Init();
	//��]����M�~�b�N������
	//otationgimmick.Init();
}

void CStage::Update()
{
	//���C�g�̍X�V�B
	UpdateLight();
	//�X�e�[�W�w�i�X�V
	stageback.Update();
	//�}�b�v�X�V
	map.Update();
	//�v���C���[���X�V�B
	player.Update();
	//���t�����G�l�~�[�X�V
	mohurun.Update();
	//�e�X�V
	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	shadow.SetLightDirection(lightDir);
	//N�u���b�N���X�V
	nblock.Update();
	//�����Ȃ��u���b�N�X�V
	//noblock.Update();
	//�͂Ăȃ{�b�N�X�X�V
	//hanatebox.Update();
	//�L�m�R�X�V
	/*if (kinoko.GetState() == Leave && kinoko.GetKinoko() == false)
	{
		kinoko.Update();
	}*/
	//�y�ǍX�V
	pipe.Update();
	//�S�[���X�V
	goal.Update();
	//�T�{�e���X�V
	//sabo.Update();
	//�R�C���X�V
	coin.Update();
	//�S�[���t���O�X�V
	goalflag.Update();
	//�R�C���X�V
	coinNumber.Update();
	//���X�V
	bird.Update();
	//��]����M�~�b�N�X�V
	//rotationgimmick.Update();
	//�T�E���h�\�[�X�X�V
	soundsource.Update();
	//�R�C���X�v���C�g�X�V
	coinsprite.Update();
	//���z�X�V
	sun.Update();
	//�J�����̍X�V
	camera.Update();
}

void CStage::Render()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	//�e�`��
	shadow.Draw(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
		);
	shadow.RenderUnity(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
		);

	//�n���Y�I�� 1-1 �����_�����O�^�[�Q�b�g�̐؂�ւ��B
	LPDIRECT3DSURFACE9 frameBufferRT;
	LPDIRECT3DSURFACE9 frameBufferDS;
	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);		//���݂̃����_�����O�^�[�Q�b�g
	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);	//���݂̃f�v�X�X�e���V���T�[�t�F�X���Q�b�g�B
	//���C�������_�[�^�[�Q�b�g�ɍ����ւ���B
	g_pd3dDevice->SetRenderTarget(
		0,									//���Ԗڂ̃����_�����O�^�[�Q�b�g��ݒ肷�邩�̈����B
		mainRenderTarget->GetRenderTarget()	//�ύX���郌���_�����O�^�[�Q�b�g�B
		);
	// �f�v�X�X�e���V���o�b�t�@���ύX����B
	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());

	// �����_�����O�^�[�Q�b�g���N���A�B
	//g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//�X�e�[�W�w�i�`��
	stageback.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
		);
	//�}�b�v�`��
	map.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix());
	//�v���C���[��`��
	player.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false
		);
	//���t�����G�l�~�[�`��
	mohurun.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//N�u���b�N��`��
	nblock.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//�����Ȃ��u���b�N�`��
	noblock.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix());
	//�͂Ăȃ{�b�N�X�`��
	/*hanatebox.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);*/
	//�L�m�R
	/*if (kinoko.GetState() == Leave && kinoko.GetKinoko() == false)
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
	}*/
	//�y�Ǖ`��
	pipe.Render();
	//�S�[���`��
	goal.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
	);
	//�T�{�e���`��
	/*sabo.Render(
		g_pd3dDevice,
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		light.GetLightDirection(),
		light.GetLightColor(),
		light.GetambientLight(),
		light.GetLightNum()
		);*/
	//�R�C���`��
	coin.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//�S�[�����`��
	goalflag.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix());
	//���`��
	bird.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//��]����M�~�b�N�`��
	/*rotationgimmick.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
		);*/
	//���z�`��
	sun.Render();

	bloom->Render();

	//// �n���Y�I�� 1-2 �����_�����O�^�[�Q�b�g��߂��B
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
	//�Q�ƃJ�E���^�������Ă���̂ŊJ���B
	frameBufferRT->Release();
	frameBufferDS->Release();

	//// 18-3 �I�t�X�N���[�������_�����O�����G���t���[���o�b�t�@�ɓ\��t����B
	CopyMainRTToCurrentRT();

	//�R�C���`��
	coinNumber.Render(m_pSprite);
	//�R�C���X�v���C�g�`��
	coinsprite.Render(m_pSprite);

	

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CStage::Release()
{
	//�e�����[�X
	shadow.Release();
	//�X�e�[�W�w�i�����[�X
	//stageback.Release();
	//�͂Ăȃ{�b�N�X�����[�X
	//hanatebox.Release();
	//�L�m�R�����[�X
	//kinoko.Release();
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
			g_physicsWorld->AddRigidBody(m_rigidBody2D[i]);
		}
	}
}
