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
	//���W�Z�b�g
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//��]�Z�b�g
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
	//�傫���Z�b�g
	void SetScale(const D3DXVECTOR3& scale)
	{
		this->scale = scale;
	}
	//�u���b�N�󂷃t���O�Z�b�g
	void SetLost(const bool& flag)
	{
		blockLost = flag;
	}
	//�p�[�e�B�N�����o�����t���O
	void SetParFlag(const bool& flag)
	{
		parFlag = flag;
	}
	//�u���b�N�̍��̃Q�b�g
	const btRigidBody *GetBlock() const
	{
		return rigidBodyBlock;
	}
	//�����蔻��쐬
	void CreateCollision();				
	//�����蔻��ǉ�
	void AddRigidBody();				
	//�����蔻��폜
	void RemoveRigidBody();				
private:
	D3DXVECTOR3									position;				//���W�B
	D3DXVECTOR3									scale;					//�傫��
	D3DXQUATERNION								rotation;				//��]
	static SkinModelData*						orgSkinModelData;		//�I���W�i���̃X�L�����f���f�[�^�B
	SkinModel									skinModel;				//���f��
	SkinModelData								modelData;				//���f���f�[�^
	Animation*									orgAnimation;			//�I���W�i���̃A�j���[�V����
	Animation									animation;				//�A�j���[�V����
	CLight										light;					//���C�g
	AnimState									animState;				//�A�j���[�V�����p�X�e�[�g
	SParicleEmitParameter						param;					//�p�[�e�B�N��
	typedef std::shared_ptr<CParticleEmitter>	CParticleEmitterPtr;	//�p�[�e�B�N���G�~�b�^�[�̃V�F�A�[�h�|�C���^
	std::list<CParticleEmitterPtr>				particleEmitterList;	//�p�[�e�B�N�����X�g
	const int									MAXPAR = 50;			//�p�[�e�B�N���������Ԃ̏��
	int											parTime;				//�p�[�e�B�N���̎���
	bool										parFlag;				//�p�[�e�B�N�����o�邩�̃t���O
	bool										blockLost;				//�u���b�N�����邩�H
	//bulletPhysics�̍��̂��g�p���邽�߂ɕK�v�ȕϐ��B
	btCollisionShape*							blockboxShape = NULL;	//�n�ʂ̃R���W�����`��B
	btRigidBody*								rigidBodyBlock = NULL;	//����
	btDefaultMotionState*						myMotionState = NULL;	//���[�V�����X�e�[�g
	bool										isAddCollision;			//�R���W�����ǉ��t���O
};

