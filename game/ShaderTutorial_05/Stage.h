#pragma once
#include "lib\System.h"
#include "Camera.h"
#include "Light.h"
#include "LightBack.h"
#include "Player.h"
#include "Block.h"
#include "Stage.h"
#include "HatenaBox.h"
#include "Kinoko.h"
#include "NBlock.h"
#include "StageBack.h"
#include "Pipe.h"
#include "Map.h"
#include "ShadowMap.h"
#include "Goal.h"

#define MAX_COLLISION 100

//�I�u�W�F�N�g�̏ڍ�
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

//����X�e�[�W�͍��z���p������
class CStage
{
public:
	CStage(){}
	virtual ~CStage(){}
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	void UpdateLight();
	void Release();

	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody(int arraySize);		//2D�����蔻��ǉ�
	Camera* GetCamera()
	{
		return& camera;
	}
	CPlayer* GetPlayer()
	{
		return &player;
	}
	CKinoko* GetKinoko()
	{
		return &kinoko;
	}
	CHatenaBox* GetHatena()
	{
		return &hanatebox;
	}
	CMap* GetMap()
	{
		return&map;
	}
	CShadowMap* GetShadow()
	{
		return&shadow;
	}
protected:
	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3D[MAX_COLLISION];	//����3D�B
	btRigidBody*		m_rigidBody2D[MAX_COLLISION];	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;

	Camera camera;				//�J�����B
	CLight light;				//���C�g
	CLightBack lightback;		//�w�i���C�g
	CPlayer player;				//�v���C���[
	CBlock block;				//�u���b�N
	CHatenaBox	hanatebox;		//�͂Ăȃ{�b�N�X
	CKinoko	kinoko;				//�L�m�R
	CNBlock	nblock;				//�m�[�}���u���b�N
	CStageBack stageback;		//�X�e�[�W�w�i
	CPipe pipe;					//�y��
	CMap map;					//�}�b�v�쐻
	CShadowMap shadow;			//�e
	CGoal goal;					//�S�[��
};

extern CStage g_stage;