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
	//���W�Q�b�g
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
	//�X�e�[�g�Q�b�g
	const NoblockState& GetState() const
	{
		return state;
	}
	//�X�e�[�g�Z�b�g
	void SetState(const NoblockState& sta)
	{
		state = sta;
	}
	//�����Ȃ��u���b�N�̍��̃Q�b�g
	const btRigidBody *Getnoblock() const
	{
		return rigidBodynoblock;
	}
	//�����蔻��쐬
	void CreateCollision();					
	//�����蔻��ǉ�
	void AddRigidBody();						
private:
	D3DXVECTOR3				position;				//���W�B
	D3DXVECTOR3				scale;					//�X�P�[��
	D3DXQUATERNION			rotation;				//��]
	SkinModel				skinModel;				//���f��
	SkinModelData			modelData;				//���f���f�[�^
	Animation				animation;				//�A�j���[�V����
	CLight					light;					//���C�g
	NoblockState			state;					//�����Ȃ��u���b�N�̏��
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	noblockboxShape = NULL;		//�n�ʂ̃R���W�����`��B
	btRigidBody*		rigidBodynoblock = NULL;	//���́B
	btDefaultMotionState* myMotionState = NULL;		//���[�V�����X�e�[�g
	bool				isAddCollision;				//�R���W�����ǉ��t���O
};