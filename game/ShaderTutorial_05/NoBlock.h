#pragma once
#include "Model.h"

enum noblockState
{
	noblockhit,			//�v���C���[�Ɠ�������				������
	noblocknohit			//�v���C���[�Ɠ������Ă��Ȃ�		�����Ȃ�
};

class CNoBlock {
public:
	//�R���X�g���N�^
	CNoBlock();
	//�f�X�g���N�^
	~CNoBlock();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render();
	//�J���B
	void Release();
	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
	noblockState GetState()
	{
		return state;
	}
	void SetState(noblockState sta)
	{
		state = sta;
	}
	btRigidBody *Get2Dnoblock()
	{
		return m_rigidBody2Dnoblock;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody();		//2D�����蔻��ǉ�
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXQUATERNION			rotation;
	SkinModel				skinmodel;
	SkinModelData			modelData;
	Animation				animation;
	CLight					light;
	noblockState			state;			//�͂ĂȂ̏��
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_noblockboxShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dnoblock;	//����3D�B
	btRigidBody*		m_rigidBody2Dnoblock;	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
};