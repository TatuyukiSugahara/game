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
	const btRigidBody *Getnoblock() const
	{
		return rigidBodynoblock;
	}
	void CreateCollision();				//2D�����蔻��
	void AddRigidBody();		//2D�����蔻��ǉ�
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXQUATERNION			rotation;
	SkinModel				skinModel;
	SkinModelData			modelData;
	Animation				animation;
	CLight					light;
	NoblockState			state;			//�����Ȃ��u���b�N�̏��
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	noblockboxShape = NULL;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		rigidBodynoblock = NULL;	//���́B
	btDefaultMotionState* myMotionState = NULL;
	bool				isAddCollision;
};