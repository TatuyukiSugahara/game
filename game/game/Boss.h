#pragma once
#include "Turn.h"
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
	void Move();
	void Falter();
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
	void SetCameraFlag(const bool& flag)
	{
		cameraflag = flag;
	}
	const bool& GetCameraFlag() const 
	{
		return cameraflag;
	}
	const BossState& GetState() const
	{
		return state;
	}
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXVECTOR3				movespeed;		//�ړ����x
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	CTurn					turn;			//�^�[���N���X
	float					currentAngleY;
	float					targetAngleY;
	int life;
	bool cameraflag = false;
	BossState state;
	SParicleEmitParameter param;
	typedef std::shared_ptr<CParticleEmitter> CParticleEmitterPtr;
	std::list<CParticleEmitterPtr> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;

	CCharacterController characterController;				//�L�����N�^�[�R���g���[���[
};