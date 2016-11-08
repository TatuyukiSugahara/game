#pragma once
#include "Particle\ParticleEmitter.h"
enum State
{
	on,				//�G������
	off				//�G�����Ȃ�
};

class CMohurun
{
public:
	CMohurun();
	~CMohurun();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render();
	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	State GetState()
	{
		return state;
	}
	void SetState(State state)
	{
		this->state = state;
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
private:
	State state;

	D3DXVECTOR3				position;		//���W�B�B
	D3DXVECTOR3				scale;			//�傫��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	CParticleEmitter particleEmitter;		//�p�[�e�B�N���G�~�b�^�[
	SParicleEmitParameter param;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;		
	int count;
};

