#pragma once
#include "Model.h"


class CNoBlock {
public:
	enum class NoblockState
	{
		hit,			//�v���C���[�Ɠ�������				������
		nohit			//�v���C���[�Ɠ������Ă��Ȃ�		�����Ȃ�
	};
	//�R���X�g���N�^
	CNoBlock();
	//�f�X�g���N�^
	~CNoBlock();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
	//�J���B
	void Release();
	//���W��ݒ�B
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
	const NoblockState& GetState() const
	{
		return state;
	}
	void SetState(const NoblockState& sta)
	{
		state = sta;
	}
	const btRigidBody *Get2Dnoblock() const
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
	NoblockState			state;			//�͂ĂȂ̏��
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_noblockboxShape = NULL;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dnoblock = NULL;	//����3D�B
	btRigidBody*		m_rigidBody2Dnoblock = NULL;	//����2D�B
	btDefaultMotionState* m_myMotionState = NULL;
	bool				m_isAdd2DCollision;
};