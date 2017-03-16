#pragma once
#include "Model.h"

class CHatenaBox {
public:
	enum class HatenaState
	{
		hit,			//�v���C���[�Ɠ�������
		nohit			//�v���C���[�Ɠ������Ă��Ȃ�
	};
	//�R���X�g���N�^
	CHatenaBox();
	//�f�X�g���N�^
	~CHatenaBox();
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
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
	const HatenaState& GetState() const
	{
		return state;
	}
	void SetState(const HatenaState& sta)
	{
		state = sta;
	}
	const btRigidBody *Get2DHatena() const
	{
		return m_rigidBody2Dhatena;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody();		//2D�����蔻��ǉ�
private:
	D3DXVECTOR3				position;		//���W�B�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Model					model;			//���f���B
	HatenaState				state;			//�͂ĂȂ̏��
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_hatenaboxShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dhatena = NULL;	//����3D�B
	btRigidBody*		m_rigidBody2Dhatena = NULL;	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
};