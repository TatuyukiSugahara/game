#pragma once
#include "Frame\Turn.h"
#include "Particle\ParticleEmitter.h"
#include "character\CharacterController.h"

class CBoss {
public:
	enum class BossState{
		Move,			//�ړ�
		Falter,			//����
		Dead,			//����
	};
	//�R���X�g���N�^
	CBoss();
	//�f�X�g���N�^
	~CBoss();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//�ړ�
	void Move();
	//����
	void Falter();
	//���S
	void Dead();
	//�p�[�e�B�N��
	void Particle();
	//���C�t�Q�b�g
	const int& GetLife() const 
	{
		return life;
	}
	//�s���n�߂�t���O�֐�
	bool Start();
	//�|�W�V�����Q�b�g
	const D3DXVECTOR3& GetPos()const 
	{
		return position;
	}
	//�{�X�p�J�����̃t���O�Z�b�g
	void SetCameraFlag(const bool& flag)
	{
		cameraFlag = flag;
	}
	//�{�X�p�J�����̃Q�b�g
	const bool& GetCameraFlag() const 
	{
		return cameraFlag;
	}
	//��ԃQ�b�g
	const BossState& GetState() const
	{
		return state;
	}
private:
	D3DXVECTOR3									position;				//���W�B
	D3DXVECTOR3									scale;					//�X�P�[��
	D3DXVECTOR3									moveSpeed;				//�ړ����x
	D3DXQUATERNION								rotation;				//��]
	SkinModel									skinModel;				//���f��
	SkinModelData								modelData;				//���f���f�[�^
	Animation									animation;				//�A�j���[�V����
	CLight										light;					//���C�g
	CTurn										turn;					//�^�[���N���X
	CCharacterController						characterController;	//�L�����N�^�[�R���g���[���[
	BossState									state;					//���
	SParicleEmitParameter						param;					//�p�[�e�B�N��
	typedef std::shared_ptr<CParticleEmitter>	CParticleEmitterPtr;	//�p�[�e�B�N���G�~�b�^�[�̃V�F�A�[�h�|�C���^
	std::list<CParticleEmitterPtr>				particleEmitterList;	//�p�[�e�B�N�����X�g
	const int									MAXPAR = 50;			//�p�[�e�B�N���������Ԃ̏��
	int											parTime;				//�p�[�e�B�N���̎���
	bool										parFlag;				//�p�[�e�B�N�����o�邩�̃t���O
	float										currentAngleY;			//���݂̃A���O��
	float										targetAngleY;			//���������A���O��
	int											life;					//���C�t
	bool										cameraFlag = false;		//�{�X�p�J�����̃t���O

	
};