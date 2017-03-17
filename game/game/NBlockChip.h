#pragma once
#include "Particle\ParticleEmitter.h"

//������u���b�N

class CNBlockChip
{
public:
	enum class AnimState
	{
		On,				//�A�j���[�V��������
		Off,			//�A�j���[�V�������Ȃ�
	};
	CNBlockChip();
	~CNBlockChip();
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
	void SetScale(const D3DXVECTOR3& scale)
	{
		this->scale = scale;
	}
	void SetLost(const bool& flag)
	{
		blockLost = flag;
	}
	void SetParFlag(const bool& flag)
	{
		parflag = flag;
	}
	void CreateCollision2D();				//2D�����蔻��
	void Add2DRigidBody();					//2D�����蔻��ǉ�
	void Remove2DRigidBody();				//2D�����蔻��폜
	const btRigidBody *Get2DBlock() const
	{
		return m_rigidBody2Dblock;
	}
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXQUATERNION			rotation;
	static SkinModelData*	orgSkinModelData;		//�X�L�����f���f�[�^�B
	SkinModel skinModel;
	SkinModelData modelData;
	Animation* orgAnimation;
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

