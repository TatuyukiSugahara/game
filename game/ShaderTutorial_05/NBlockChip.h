#pragma once
#include "Particle\ParticleEmitter.h"
enum AnimState
{
	BlockOn,				//�A�j���[�V��������
	BlockOff,			//�A�j���[�V�������Ȃ�
};

//�}�b�v�`�b�v�̔z�u���B
struct SBlockChipLocInfo {
	const char* modelName;		//���f���B
	D3DXVECTOR3	pos;			//���W�B
	D3DXQUATERNION	rotation;	//��]�B
	D3DXVECTOR3 scale;			//�傫��	
};

//������u���b�N

class CNBlockChip
{
public:
	CNBlockChip();
	~CNBlockChip();
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void SetPos(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	void SetRot(D3DXQUATERNION rot)
	{
		rotation = rot;
	}
	void SetScale(D3DXVECTOR3 scale)
	{
		this->scale = scale;
	}
	void SetLost(bool flag)
	{
		blockLost = flag;
	}
	void SetParFlag(bool flag)
	{
		parflag = flag;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody();					//2D�����蔻��ǉ�
	void Remove2DRigidBody();				//2D�����蔻��폜
	btRigidBody *Get2DBlock()
	{
		return m_rigidBody2Dblock;
	}
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXQUATERNION			rotation;
	LPDIRECT3DTEXTURE9		normalMap = NULL;	//�m�[�}���}�b�v
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	AnimState animState;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 50;
	int parTime;
	bool parflag;
	bool blockLost;						//�u���b�N�����邩�H
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*	m_blockboxShape = NULL;	//�n�ʂ̃R���W�����`��B
	btRigidBody*		m_rigidBody3Dblock = NULL;	//����3D�B
	btRigidBody*		m_rigidBody2Dblock = NULL;	//����2D�B
	btDefaultMotionState* m_myMotionState = NULL;
	bool				m_isAdd2DCollision;
};

