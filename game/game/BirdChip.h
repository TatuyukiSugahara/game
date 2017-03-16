#pragma once
#include "Particle\ParticleEmitter.h"

class CBirdChip
{
public:
	enum class BirdState
	{
		Alive,				//�G������
		Dead,				//�G�����Ȃ�
	};
	CBirdChip();
	~CBirdChip();
	//�������B
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//���W��ݒ�B
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	const BirdState& GetState() const
	{
		return state;
	}
	void SetState(const BirdState& state)
	{
		this->state = state;
	}
	const D3DXVECTOR3& GetPos() const 
	{
		return position;
	}
private:
	BirdState state;
	D3DXVECTOR3				position;		//���W�B�B
	D3DXVECTOR3				scale;			//�傫��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	static SkinModelData*	orgSkinModelData;		//�X�L�����f���f�[�^�B
	Animation* orgAnimation;
	CLight	light;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;
	int count;

	std::unique_ptr<CSoundSource> SEenemyDeath;
};

