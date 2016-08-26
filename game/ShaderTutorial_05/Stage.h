#pragma once
#include "lib\System.h"

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
	virtual void Draw();

	void CreateCollision2D();
	void Add2DRigidBody(int arraySize);

protected:


	bool				isButtomTriger;
	bool				isDied;

	//��������bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3D[MAX_COLLISION];	//����3D�B
	btRigidBody*		m_rigidBody2D[MAX_COLLISION];	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;

};
