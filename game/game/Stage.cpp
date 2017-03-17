#pragma once
#include "stdafx.h"
#include "Stage.h"

SCollisionInfo collisionInfoTable[] = {
#include "Collision_stage01.h"
};

SCollisionInfo collisionInfoTable2[] = {
#include "Collision_stage02.h"
};

SCollisionInfo collisionInfoTableBoss[] = {
#include "Collision_StageBos.h"
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
	//�t�B�W�b�N�X���[���h�쐬�B
	g_physicsWorld = new CPhysicsWorld;
	//�������[���h������
	g_physicsWorld->Init();		
	//NULL�Z�b�g�B
	memset(rigidBody, NULL, sizeof(rigidBody));
	memset(groundShape, NULL, sizeof(groundShape));
	//�O���[�o���̃X�e�[�W�Ɏ�����ݒ�B
	g_stage = this;
	//�X�v���C�g������
	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &sprite)))
	{
		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
	}
	//�X�e�[�W���Ƃ̃R���W�����ݒ�B
	//�X�e�[�W���Ƃɏ�����
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		collisionTable = collisionInfoTable;
		arraySize = ARRAYSIZE(collisionInfoTable);
		//�ʏ�X�e�[�W������
		StageInit();
		break;
	case CSceneManager::StageNumber::Stage2:
		collisionTable = collisionInfoTable2;
		arraySize = ARRAYSIZE(collisionInfoTable2);
		//�ʏ�X�e�[�W������
		StageInit();
		break;
	case CSceneManager::StageNumber::StageBoss:
		collisionTable = collisionInfoTableBoss;
		arraySize = ARRAYSIZE(collisionInfoTableBoss);
		//�{�X�X�e�[�W������
		StageBossInit();
		break;
	}
}

void CStage::Update()
{
	//�X�e�[�W���ƂɍX�V
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		//�ʏ�X�e�[�W�X�V
		StageUpdate();
		break;
	case CSceneManager::StageNumber::Stage2:
		//�ʏ�X�e�[�W�X�V
		StageUpdate();
		break;
	case CSceneManager::StageNumber::StageBoss:
		//�{�X�X�e�[�W�X�V
		StageBossUpdate();
		break;
	}
}

void CStage::Render()
{
	//�X�e�[�W���Ƃɕ`��
	switch (g_scenemanager->GetNumber())
	{
	case CSceneManager::StageNumber::Stage1:
		//�ʏ�X�e�[�W�`��
		StageRender();
		break;
	case CSceneManager::StageNumber::Stage2:
		//�ʏ�X�e�[�W�`��
		StageRender();
		break;
	case CSceneManager::StageNumber::StageBoss:
		//�{�X�X�e�[�W�`��
		StageBossRender();
		break;
	}
}

void CStage::Release()
{
	//�e�����[�X
	shadow.Release();
	//�v���C���[�����[�X
	player.Release();
}

void CStage::CreateCollision()
{
	if (arraySize >= MaxCollision)
	{
		std::abort();
	}
	for (int i = 0; i < arraySize; i++) {
		SCollisionInfo& collision = collisionTable[i];
		//�����ō��̂Ƃ���o�^����B
		//���̂��������B
		{
			//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
			groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
			btTransform groundTransform;
			groundTransform.setIdentity();
			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
			float mass = 0.0f;
			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
			myMotionState = new btDefaultMotionState(groundTransform);
			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape[i], btVector3(0, 0, 0));
			rigidBody[i] = new btRigidBody(rbInfo);
		}
	}
}

void CStage::AddRigidBody()
{
	// ���[���h�ɒǉ��B
	if (!isAddCollision){
		isAddCollision = true;
		for (int i = 0; i < arraySize; i++)
		{
			g_physicsWorld->AddRigidBody(rigidBody[i]);
		}
	}
}

void CStage::BossMusic()
{
	//�{�X��̉��y�𗬂�
	if (bossmusic == false)
	{
		//���݂̉��y���~�߂�
		soundsource.Stop();
		//�{�X�퉹�y���Đ�
		soundsource.InitStreaming("Asset/Sound/dotabatare-su.wav");
		soundsource.Play(true);
		bossmusic = true;
	}
}

void CStage::MusicStop()
{
	//���񂾂񉹂�������B
	soundsource.SetVolume(-0.005f);
}

//�f�o�b�O�p�̃X�e�[�W�ύX
void CStage::StageChange()
{
	//1�������ƃX�e�[�W�P��
	if (GetAsyncKeyState('1'))
	{
		g_scenemanager->SetNumber((int)CSceneManager::StageNumber::Stage1);
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
	}
	//2�������ƃX�e�[�W�Q��
	else if (GetAsyncKeyState('2'))
	{
		g_scenemanager->SetNumber((int)CSceneManager::StageNumber::Stage2);
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
	}
	//3�������ƃX�e�[�W�R��
	else if (GetAsyncKeyState('3'))
	{
		g_scenemanager->SetNumber((int)CSceneManager::StageNumber::StageBoss);
		g_scenemanager->ChangeScene((int)CSceneManager::GameScene::Game);
	}
}

//�ʏ�X�e�[�W�̏�����
void CStage::StageInit()
{
	//�R���W�����쐬
	CreateCollision();
	//���W�b�h�{�f�B�ǉ�
	AddRigidBody();
	//���C�g���������B
	light.Init();
	//�J�����̏������B
	camera.Init();
	skycamera.Init();
	//�T�E���h������
	soundsource.InitStreaming("Asset/Sound/CandyCrush.wav");
	soundsource.Play(true);
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
	goal.Init();
	//�T�{�e��������
	//sabo.Init(g_pd3dDevice);
	//�R�C����������
	coin.Init();
	//�S�[���t���O������
	goalflag.Init();
	//��������
	bird.Init();
	//�R�C���i���o�[������
	coinNumber.Init();
	//�R�C���X�v���C�g������
	coinsprite.Init();
	//�e������
	shadow.Create(512, 512);
	//���z������
	sun.Init();
	//��]����M�~�b�N������
	//otationgimmick.Init();
	//�T������
	kame.Init();
}

//�{�X�X�e�[�W������
void CStage::StageBossInit()
{
	//�R���W�����쐬
	CreateCollision();
	//���W�b�h�{�f�B�ǉ�
	AddRigidBody();
	//���C�g���������B
	light.Init();
	//�J�����̏������B
	camera.Init();
	skycamera.Init();
	//�T�E���h������
	soundsource.InitStreaming("Asset/Sound/CandyCrush.wav");
	soundsource.Play(true);
	//�w�i���C�g��������
	lightback.Init();
	//�X�e�[�W�w�i������
	stageback.Init(g_pd3dDevice);
	//�}�b�v������
	map.Init(g_pd3dDevice);
	//�v���C���[������
	player.Init(g_pd3dDevice);
	//�e������
	shadow.Create(512, 512);
	//���z������
	sun.Init();
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

//�ʏ�X�e�[�W�X�V
void CStage::StageUpdate()
{
	//���C�g�̍X�V�B
	UpdateLight();
	//�X�e�[�W�w�i�X�V
	stageback.Update();
	//�}�b�v�X�V
	map.Update();
	//�v���C���[���X�V�B
	player.Update();
	//�R�C���X�V
	coinNumber.Update();
	//�R�C���X�v���C�g�X�V
	coinsprite.Update();
	//�e�X�V
	//���C�g�̃|�W�V�������v���C���[��10m��ɐݒ�
	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	shadow.SetLightDirection(lightDir);
	//�T�E���h�\�[�X�X�V
	soundsource.Update();
	//���z�X�V
	sun.Update();
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
	//�����Ȃ��u���b�N�X�V
	//noblock.Update();
	//�͂Ăȃ{�b�N�X�X�V
	//hanatebox.Update();
	//�L�m�R�X�V
	/*if (kinoko.GetState() == Leave && kinoko.GetKinoko() == false)
	{
	kinoko.Update();
	}*/
	//�T�X�V
	kame.Update();
	//�J�����̍X�V
	camera.Update();
	skycamera.Update();

#ifdef _DEBUG
	StageChange();
#endif
}

//�{�X�X�e�[�W�X�V
void CStage::StageBossUpdate()
{
	//���C�g�̍X�V�B
	UpdateLight();
	//�X�e�[�W�w�i�X�V
	stageback.Update();
	//�}�b�v�X�V
	map.Update();
	//�v���C���[���X�V�B
	player.Update();
	//�R�C���X�V
	coinNumber.Update();
	//�R�C���X�v���C�g�X�V
	coinsprite.Update();
	//�e�X�V
	//���C�g�̃|�W�V�������v���C���[��10m��ɐݒ�
	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	shadow.SetLightPosition(lightPos);
	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
	D3DXVec3Normalize(&lightDir, &lightDir);
	shadow.SetLightDirection(lightDir);
	//�T�E���h�\�[�X�X�V
	soundsource.Update();
	//���z�X�V
	sun.Update();
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
	//�J�����̍X�V
	camera.Update();
	skycamera.Update();

#ifdef _DEBUG
	StageChange();
#endif
}

//�ʏ�X�e�[�W�`��
void  CStage::StageRender()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	//�e�`��
	shadow.Render(camera.GetViewMatrix());
	//�v���C���[�p�̉e�`��
	shadow.RenderUnity(camera.GetViewMatrix());
	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
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
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix()
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
	sun.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//�T�X�V
	kame.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//�R�C���擾�\���p(��ԑO�ɕ`�悷�邽��Z�o�b�t�@�N���A)
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	coinsprite.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//�u���[���`��
	bloom->Render();
	//�����_�����O�^�[�Q�b�g��߂��B
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
	//�Q�ƃJ�E���^�������Ă���̂ŊJ���B
	frameBufferRT->Release();
	frameBufferDS->Release();

	//�I�t�X�N���[�������_�����O�����G���t���[���o�b�t�@�ɓ\��t����B
	CopyMainRTToCurrentRT();

	//�u���[��������QD�\��
	//�R�C���`��
	coinNumber.Render(sprite);

	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

//�{�X�X�e�[�W�`��
void CStage::StageBossRender()
{
	// ��ʂ��N���A�B
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
	//�V�[���̕`��J�n�B
	g_pd3dDevice->BeginScene();

	//�e�`��
	shadow.Render(camera.GetViewMatrix());
	//�v���C���[�p�̉e�`��
	shadow.RenderUnity(camera.GetViewMatrix());

	//�����_�����O�^�[�Q�b�g�̐؂�ւ��B
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
	//���z�`��
	sun.Render(
		camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//�{�X�`��
	boss.Render(camera.GetViewMatrix(),
		camera.GetProjectionMatrix(),
		false);
	//�R�C���擾�\���p(��ԑO�ɕ`�悷�邽��Z�o�b�t�@�N���A)
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
	//�u���[���`��
	bloom->Render();
	//�����_�����O�^�[�Q�b�g��߂��B
	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
	//�Q�ƃJ�E���^�������Ă���̂ŊJ���B
	frameBufferRT->Release();
	frameBufferDS->Release();
	//�I�t�X�N���[�������_�����O�����G���t���[���o�b�t�@�ɓ\��t����B
	CopyMainRTToCurrentRT();
	//�u���[��������QD�\��
	//�{�X���C�t�`��
	bossLife.Render(sprite);
	//�{�X�J�b�g�C���`��
	bossKatto.Render(sprite);
	//�{�X�N���A�`��
	bossClear.Render(sprite);
	if (boss.Start() == true && boss.GetLife() > 0)
	{
		//�{�X���O�`��
		bossName.Render(sprite);
	}
	// �V�[���̕`��I���B
	g_pd3dDevice->EndScene();
	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}