#pragma once
#include "stdafx.h"
#include "Stage.h"

SCollisionInfo collisionInfoTable[] = {
#include "Collision2D_stage01.h"
};

SCollisionInfo collisionInfoTable2[] = {
#include "Collision_stage02.h"
};

SCollisionInfo collisionInfoTableBoss[] = {
#include "CollisionStageBos.h"
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
	memset(m_rigidBody, NULL, sizeof(m_rigidBody));
	memset(m_groundShape, NULL, sizeof(m_groundShape));
	g_stage = this;

	switch (g_scenemanager->GetNomber())
	{
	case Stage1:
		collisionTable = collisionInfoTable;
		arraySize = ARRAYSIZE(collisionInfoTable);
		break;
	case Stage2:
		collisionTable = collisionInfoTable2;
		arraySize = ARRAYSIZE(collisionInfoTable2);
		break;
	case StageBoss:
		collisionTable = collisionInfoTableBoss;
		arraySize = ARRAYSIZE(collisionInfoTableBoss);
		break;
	}

	CreateCollision();
	Add2DRigidBody(/*ARRAYSIZE(collisionTable)*/);
	//���C�g���������B
	light.Init();
	//�J�����̏������B
	camera.Init();
	skycamera.Init();

	soundsource.InitStreaming("Asset/Sound/mario.wav");
	soundsource.Play(true);

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
	if (g_scenemanager->GetNomber() != StageBoss)
	{
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

		//�T�{�e��������
		//sabo.Init(g_pd3dDevice);
		//�R�C����������
		coin.Init();

		//�S�[���t���O������
		goalflag.Init();

		//��������
		bird.Init();
	}
	//�R�C���i���o�[������
	coinNumber.Init();
	//�R�C���X�v���C�g������
	coinsprite.Init();
	//�e������
	shadow.Create(512, 512);
	//���z������
	sun.Init();
	if (g_scenemanager->GetNomber() == StageBoss)
	{
		//�{�X���y�t���O�������B
		bossmusic = false;
		//�{�X������
		boss.Init();
		//�{�X���C�t������
		bossLife.Init();
		//�{�X���O������
		bossName.Init();
		//�{�X�J�b�g�C��������
		bossKatto.Init();
		//�{�X���j�N���A������
		bossClear.Init();
	}

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
	if (g_scenemanager->GetNomber() != StageBoss)
	{
		//���t�����G�l�~�[�X�V
		mohurun.Update();
		//N�u���b�N���X�V
		nblock.Update();
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
		//���X�V
		bird.Update();
		//��]����M�~�b�N�X�V
		//rotationgimmick.Update();
		
	}
	//�R�C���X�V
		coinNumber.Update();
	//�R�C���X�v���C�g�X�V
		coinsprite.Update();
	//�e�X�V
	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	shadow.SetLightDirection(lightDir);
	
	//�����Ȃ��u���b�N�X�V
	//noblock.Update();
	//�͂Ăȃ{�b�N�X�X�V
	//hanatebox.Update();
	//�L�m�R�X�V
	/*if (kinoko.GetState() == Leave && kinoko.GetKinoko() == false)
	{
		kinoko.Update();
	}*/
	
	//�T�E���h�\�[�X�X�V
	soundsource.Update();
	
	//���z�X�V
	sun.Update();
	if (g_scenemanager->GetNomber() == StageBoss)
	{
		//�{�X�X�V
		boss.Update();
		//�{�X���C�t�X�V
		bossLife.Update();
		//�{�X���O�X�V
		bossName.Update();
		//�{�X�J�b�g�C���X�V
		bossKatto.Update();
		//�{�X�N���A�X�V
		bossClear.Update();
	}
	//�J�����̍X�V
	camera.Update();
	skycamera.Update();
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
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//�X�e�[�W�w�i�`��
	stageback.Render(
		g_pd3dDevice,
		skycamera.GetViewMatrix(),
		skycamera.GetProjectionMatrix()
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
	if (g_scenemanager->GetNomber() != StageBoss)
	{
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
		pipe.Render(camera.GetViewMatrix(),
			camera.GetProjectionMatrix(), 
			false);
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
	}
	
	//���z�`��
	sun.Render();
	if (g_scenemanager->GetNomber() == StageBoss)
	{
		//�{�X�`��
		boss.Render(camera.GetViewMatrix(),
			camera.GetProjectionMatrix(),
			false);
	}

	//�R�C���擾�\���p(��ԑO�ɕ`�悷�邽��Z�o�b�t�@�N���A)
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	if (g_scenemanager->GetNomber() != StageBoss)
	{
		//�R�C���X�v���C�g�`��
		coinsprite.Render();
	}

	bloom->Render();

	//// �n���Y�I�� 1-2 �����_�����O�^�[�Q�b�g��߂��B
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
	//�Q�ƃJ�E���^�������Ă���̂ŊJ���B
	frameBufferRT->Release();
	frameBufferDS->Release();

	//// 18-3 �I�t�X�N���[�������_�����O�����G���t���[���o�b�t�@�ɓ\��t����B
	CopyMainRTToCurrentRT();
	
	//�u���[��������QD�\��
	if (g_scenemanager->GetNomber() == StageBoss)
	{
		//�{�X���C�t�`��
		bossLife.Render(m_pSprite);
		//�{�X�J�b�g�C���`��
		bossKatto.Render(m_pSprite);
		//�{�X�N���A�`��
		bossClear.Render(m_pSprite);
		if (boss.Start() == true && boss.GetLife() > 0)
		{
			//�{�X���O�`��
			bossName.Render(m_pSprite);
		}
	}
	else
	{
		//�R�C���`��
		coinNumber.Render(m_pSprite);
	}


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

void CStage::CreateCollision()
{
	if (arraySize >= MAX_COLLISION)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionTable[i];
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
			m_rigidBody[i] = new btRigidBody(rbInfo);

			//���[���h�ɒǉ��B
			//g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);

		}
	}
}

void CStage::Add2DRigidBody(/*int arraySize*/)//���[���h�ɒǉ��B
{
	if (!m_isAdd2DCollision){
		m_isAdd2DCollision = true;
		for (int i = 0; i < arraySize; i++)
		{
			g_physicsWorld->AddRigidBody(m_rigidBody[i]);
		}
	}
}

void CStage::BossMusic()
{
	if (bossmusic == false)
	{
		soundsource.Stop();
		soundsource.InitStreaming("Asset/Sound/battle.wav");
		soundsource.Play(true);
		bossmusic = true;
	}
}

void CStage::MusicStop()
{
	//���񂾂񉹂�������B
	soundsource.SetVolume(-0.05);
}