#pragma once
#include "lib\System.h"
#include "Camera.h"
#include "Light.h"
#include "Player.h"
#include "Block.h"
#include "Stage.h"
#include "HatenaBox.h"
#include "Kinoko.h"

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

	CPlayer* GetPlayer()
	{
		return &player;
	}
	CKinoko* GetKinoko()
	{
		return &kinoko;
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
	CPlayer player;				//�v���C���[
	CBlock block;				//�u���b�N
	CHatenaBox	hanatebox;		//�͂Ăȃ{�b�N�X
	CKinoko	kinoko;				//�L�m�R
};

extern CStage g_stage;