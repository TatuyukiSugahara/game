//#pragma once
//#include "lib\System.h"
//#include "Scene\Scene.h"
//#include "Stage.h"
//#include "Camera.h"
//#include "Light.h"
//#include "Player.h"
//#include "StageBack.h"
//#include "Map.h"
//#include "ShadowMap.h"
//#include "Sound\SoundSource.h"
//#include "Sun.h"
//#include "Boss.h"
//#include "BossLife.h"
//
//#define MAX_COLLISION 100
//
////����X�e�[�W�͍��z���p������
//class CStageBoss : public CScene
//{
//public:
//	CStageBoss(){}
//	~CStageBoss()
//	{
//		for (auto& shape : m_groundShape){
//			delete shape;
//		}
//		for (auto& rb : m_rigidBody){
//			delete rb;
//		}
//		delete m_myMotionState;
//
//	}
//	void Init();
//	void Update();
//	void Render();
//	void UpdateLight();
//	void Release();
//
//	void CreateCollision();				//2D�����蔻��
//	void Add2DRigidBody(/*int arraySize*/);		//2D�����蔻��ǉ�
//	Camera* GetCamera()
//	{
//		return&camera;
//	}
//	CLight* GetLight()
//	{
//		return &light;
//	}
//	CPlayer* GetPlayer()
//	{
//		return &player;
//	}
//	CMap* GetMap()
//	{
//		return&map;
//	}
//	CShadowMap* GetShadow()
//	{
//		return&shadow;
//	}
//	CSoundSource* GetSoundSorce()
//	{
//		return&soundsource;
//	}
//	CBoss* GetBoss()
//	{
//		return &boss;
//	}
//protected:
//	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
//	btCollisionShape*	m_groundShape[MAX_COLLISION];	//�n�ʂ̃R���W�����`��B
//	btRigidBody*		m_rigidBody[MAX_COLLISION];	//���́B
//	btDefaultMotionState* m_myMotionState;
//	bool				m_isAdd2DCollision;
//	SCollisionInfo* collisionTable;					//�R���W�����e�[�u��
//	int arraySize;									//�T�C�Y
//	LPD3DXSPRITE m_pSprite;			//�X�v���C�g
//	Camera camera;				//�J�����B
//	CLight light;				//���C�g
//	CPlayer player;				//�v���C���[
//	CStageBack stageback;		//�X�e�[�W�w�i
//	CMap map;					//�}�b�v�쐻
//	CShadowMap shadow;			//�e
//	CSoundSource			soundsource;
//	CSun sun;					//���z
//	CBoss boss;					//�{�X
//	CBossLife bossLife;			//�{�X���C�t
//};
//
//extern CStageBoss* g_stageBoss;