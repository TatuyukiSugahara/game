#pragma once
#include "Turn.h"
#include "Particle\ParticleEmitter.h"
#include "character\CharacterController.h"

enum BossState{
	BossMove,			//�ړ�
	BossFalter,			//����
	BossDead,			//����
};

class CBoss {
public:
	//�R���X�g���N�^
	CBoss();
	//�f�X�g���N�^
	~CBoss();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void Move();
	void Falter();
	void Dead();
	//�p�[�e�B�N��
	void Particle();
	//���C�t�Q�b�g
	int GetLife()
	{
		return life;
	}
	//�s���n�߂�t���O�֐�
	bool Start();
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
	void SetCameraFlag(bool flag)
	{
		cameraflag = flag;
	}
	BossState GetState()
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
	int life = 5;
	bool cameraflag = false;
	BossState state;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;

	CCharacterController characterController;				//�L�����N�^�[�R���g���[���[
};