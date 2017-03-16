#pragma once
#include "Particle\ParticleEmitter.h"
#include "character\CharacterController.h"

class CMohurunChip
{
public:
	enum class MohurunState
	{
		Alive,				//�G������
		Dead				//�G�����Ȃ�
	};

	CMohurunChip();
	~CMohurunChip();
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
	const MohurunState& GetState() const
	{
		return state;
	}
	void SetState(const MohurunState& state)
	{
		this->state = state;
	}
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
private:
	MohurunState state;

	D3DXVECTOR3				gravity = D3DXVECTOR3(0.0f, -0.98f, 0.0f);
	D3DXVECTOR3				position;		//���W�B�B
	D3DXVECTOR3				scale;			//�傫��
	D3DXVECTOR3				movespeed;		//�ړ����x
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	static SkinModelData*	orgSkinModelData;		//�X�L�����f���f�[�^�B
	SkinModelData modelData;
	Animation animation;
	Animation* orgAnimation;
	CLight	light;
	CCharacterController characterController;				//�L�����N�^�[�R���g���[���[
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;
	int count;
	std::unique_ptr<CSoundSource> SEenemyDeath;
};

