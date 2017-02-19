//#pragma once
//#include "stdafx.h"
//#include "StageBoss.h"
//
//SCollisionInfo collisionInfoTableBoss[] = {
//#include "CollisionStageBos.h"
//};
//
//CStageBoss* g_stageBoss;
//
///*!-----------------------------------------------------------------------------
//*@brief	���C�g���X�V�B
//-----------------------------------------------------------------------------*/
//void CStageBoss::UpdateLight()
//{
//	light.Update();
//}
//
//void CStageBoss::Init()
//{
//	g_physicsWorld = new CPhysicsWorld;
//	g_physicsWorld->Init();			//�������[���h������
//	memset(m_rigidBody, NULL, sizeof(m_rigidBody));
//	memset(m_groundShape, NULL, sizeof(m_groundShape));
//	g_stageBoss = this;
//
//	collisionTable = collisionInfoTableBoss;
//	arraySize = ARRAYSIZE(collisionInfoTableBoss);
//
//	CreateCollision();
//	Add2DRigidBody();
//	//���C�g���������B
//	light.Init();
//	//�J�����̏������B
//	camera.Init();
//
//	//�T�E���h�\�[�X���������B
//	soundsource.InitStreaming("Asset/Sound/mario.wav");
//	soundsource.Play(true);
//	soundsource.SetVolume(0.5f);
//
//	//�X�v���C�g������
//	if (FAILED(D3DXCreateSprite(g_pd3dDevice, &m_pSprite)))
//	{
//		MessageBox(0, TEXT("�X�v���C�g�쐬���s"), NULL, MB_OK);
//	}
//
//	//�X�e�[�W�w�i������
//	stageback.Init(g_pd3dDevice);
//	//�}�b�v������
//	map.Init(g_pd3dDevice);
//	//�v���C���[������
//	player.Init(g_pd3dDevice);
//	//�e������
//	shadow.Create(512, 512);
//	//���z������
//	sun.Init();
//	//�{�X������
//	boss.Init();
//	//�{�X���C�t������
//	bossLife.Init();
//}
//
//void CStageBoss::Update()
//{
//	//���C�g�̍X�V�B
//	UpdateLight();
//	//�X�e�[�W�w�i�X�V
//	stageback.Update();
//	//�}�b�v�X�V
//	map.Update();
//	//�v���C���[���X�V�B
//	player.Update();
//	//�e�X�V
//	D3DXVECTOR3 lightPos = player.GetPos() + D3DXVECTOR3(0.0f, 10.0f, 0.0f);
//	shadow.SetLightPosition(lightPos);
//	D3DXVECTOR3 lightDir = player.GetPos() - lightPos;
//	D3DXVec3Normalize(&lightDir, &lightDir);
//	shadow.SetLightDirection(lightDir);
//	//�T�E���h�\�[�X�X�V
//	soundsource.Update();
//	//���z�X�V
//	sun.Update();
//	//�{�X�X�V
//	boss.Update();
//	//�{�X���C�t�X�V
//	bossLife.Update();
//	//�J�����̍X�V
//	camera.Update();
//}
//
//void CStageBoss::Render()
//{
//	// ��ʂ��N���A�B
//	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
//	//�V�[���̕`��J�n�B
//	g_pd3dDevice->BeginScene();
//
//	//�e�`��
//	shadow.Draw(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix()
//		);
//	shadow.RenderUnity(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix()
//		);
//
//	//�n���Y�I�� 1-1 �����_�����O�^�[�Q�b�g�̐؂�ւ��B
//	LPDIRECT3DSURFACE9 frameBufferRT;
//	LPDIRECT3DSURFACE9 frameBufferDS;
//	g_pd3dDevice->GetRenderTarget(0, &frameBufferRT);		//���݂̃����_�����O�^�[�Q�b�g
//	g_pd3dDevice->GetDepthStencilSurface(&frameBufferDS);	//���݂̃f�v�X�X�e���V���T�[�t�F�X���Q�b�g�B
//	//���C�������_�[�^�[�Q�b�g�ɍ����ւ���B
//	g_pd3dDevice->SetRenderTarget(
//		0,									//���Ԗڂ̃����_�����O�^�[�Q�b�g��ݒ肷�邩�̈����B
//		mainRenderTarget->GetRenderTarget()	//�ύX���郌���_�����O�^�[�Q�b�g�B
//		);
//	// �f�v�X�X�e���V���o�b�t�@���ύX����B
//	g_pd3dDevice->SetDepthStencilSurface(mainRenderTarget->GetDepthStencilBuffer());
//
//	// �����_�����O�^�[�Q�b�g���N���A�B
//	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);
//
//	//�X�e�[�W�w�i�`��
//	stageback.Render(
//		g_pd3dDevice,
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix()
//		);
//	//�}�b�v�`��
//	map.Render(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix());
//	//�v���C���[��`��
//	player.Render(
//		camera.GetViewMatrix(),
//		camera.GetProjectionMatrix(),
//		false
//		);
//	//���z�`��
//	sun.Render();
//	if (g_scenemanager->GetNomber() == StageBoss)
//	{
//		//�{�X�`��
//		boss.Render();
//	}
//
//	//�R�C���擾�\���p(��ԑO�ɕ`�悷�邽��Z�o�b�t�@�N���A)
//	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER,
//		D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0);
//	bloom->Render();									//�u���[�������_�[
//	//// �n���Y�I�� 1-2 �����_�����O�^�[�Q�b�g��߂��B
//	g_pd3dDevice->SetRenderTarget(0, frameBufferRT);
//	g_pd3dDevice->SetDepthStencilSurface(frameBufferDS);
//	//�Q�ƃJ�E���^�������Ă���̂ŊJ���B
//	frameBufferRT->Release();
//	frameBufferDS->Release();
//
//	//// 18-3 �I�t�X�N���[�������_�����O�����G���t���[���o�b�t�@�ɓ\��t����B
//	CopyMainRTToCurrentRT();
//
//	//�u���[��������QD�\��
//	//�{�X���C�t�`��
//	bossLife.Render(m_pSprite);
//	// �V�[���̕`��I���B
//	g_pd3dDevice->EndScene();
//	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�����ւ���B
//	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
//}
//
//void CStageBoss::Release()
//{
//	//�e�����[�X
//	shadow.Release();
//	//�v���C���[�����[�X
//	player.Release();
//}
//
//void CStageBoss::CreateCollision()
//{
//	if (arraySize >= MAX_COLLISION)
//	{
//		std::abort();
//	}
//	for (int i = 0; i < arraySize; i++) {
//		SCollisionInfo& collision = collisionTable[i];
//		//�����ō��̂Ƃ���o�^����B
//		//���̂��������B
//		{
//			//���̈����ɓn���̂̓{�b�N�X��halfsize�Ȃ̂ŁA0.5�{����B
//			m_groundShape[i] = new btBoxShape(btVector3(collision.scale.x*0.5f, collision.scale.y*0.5f, collision.scale.z*0.5f));
//			btTransform groundTransform;
//			groundTransform.setIdentity();
//			groundTransform.setOrigin(btVector3(collision.pos.x, collision.pos.y, collision.pos.z));
//			float mass = 0.0f;
//
//			//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
//			m_myMotionState = new btDefaultMotionState(groundTransform);
//			btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_groundShape[i], btVector3(0, 0, 0));
//			m_rigidBody[i] = new btRigidBody(rbInfo);
//
//			//���[���h�ɒǉ��B
//			//g_bulletPhysics.AddRigidBody(m_rigidBody2D[i]);
//
//		}
//	}
//}
//
//void CStageBoss::Add2DRigidBody(/*int arraySize*/)//���[���h�ɒǉ��B
//{
//	if (!m_isAdd2DCollision){
//		m_isAdd2DCollision = true;
//		for (int i = 0; i < arraySize; i++)
//		{
//			g_physicsWorld->AddRigidBody(m_rigidBody[i]);
//		}
//	}
//}
