#pragma once
#include "Model.h"

//�m�[�}���u���b�N
class CSaboten {
public:
	//�R���X�g���N�^
	CSaboten();
	//�f�X�g���N�^
	~CSaboten();
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
	btRigidBody *Get2Dsabo()
	{
		return m_rigidBody2Dsabo;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody();					//2D�����蔻��ǉ�
private:
	D3DXVECTOR3				position;		//���W�B�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Model					model;			//���f���B
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_saboboxShape;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dsabi;	//����3D�B
	btRigidBody*		m_rigidBody2Dsabo;	//����2D�B
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
};