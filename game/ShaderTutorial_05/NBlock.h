#pragma once
#include "Model.h"

enum BlockState
{
	yes,		//�u���b�N����
	no			//�u���b�N�Ȃ�
};

//�m�[�}���u���b�N
class CNBlock {
public:
	//�R���X�g���N�^
	CNBlock();
	//�f�X�g���N�^
	~CNBlock();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	//�J���B
	void Release();
	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody();					//2D�����蔻��ǉ�
	void Remove2DRigidBody();				//2D�����蔻��폜
	btRigidBody *Get2DBlock()
	{
		return m_rigidBody2Dblock;
	}
	void SetState(BlockState sta)
	{
		state = sta;
	}
private:
	D3DXVECTOR3				position;		//���W�B�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Model					model;			//���f���B
	BlockState				state;
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_blockboxShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dblock;	//����3D�B
	btRigidBody*		m_rigidBody2Dblock;	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
};