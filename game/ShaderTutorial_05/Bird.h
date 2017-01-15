#pragma once
#include "Particle\ParticleEmitter.h"
enum BirdState
{
	BIRDON,				//�G������
	BIRDOFF,				//�G�����Ȃ�
};

class CBird
{
public:
	CBird();
	~CBird();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	BirdState GetState()
	{
		return state;
	}
	void SetState(BirdState state)
	{
		this->state = state;
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
private:
	BirdState state;

	D3DXVECTOR3				position;		//���W�B�B
	D3DXVECTOR3				scale;			//�傫��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;
	int count;
};

