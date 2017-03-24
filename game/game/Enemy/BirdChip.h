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
	//��ԃQ�b�g
	const BirdState& GetState() const
	{
		return state;
	}
	//��ԃZ�b�g
	void SetState(const BirdState& state)
	{
		this->state = state;
	}
	//���W�Q�b�g
	const D3DXVECTOR3& GetPos() const 
	{
		return position;
	}
private:
	BirdState									state;					//���
	D3DXVECTOR3									position;				//���W
	D3DXVECTOR3									scale;					//�傫��
	D3DXQUATERNION								rotation;				//��]
	SkinModel									skinModel;				//���f��
	SkinModelData								modelData;				//���f���f�[�^
	Animation									animation;				//�A�j���[�V����
	static SkinModelData*						orgSkinModelData;		//�X�L�����f���f�[�^�B
	Animation*									orgAnimation;			//�I���W�i���̃A�j���[�V����
	CLight										light;					//���C�g
	SParicleEmitParameter						param;					//�p�[�e�B�N��
	typedef std::shared_ptr<CParticleEmitter>	CParticleEmitterPtr;	//�p�[�e�B�N���G�~�b�^�[�̃V�F�A�[�h�|�C���^
	std::list<CParticleEmitterPtr>				particleEmitterList;	//�p�[�e�B�N�����X�g
	const int									MAXPAR = 50;			//�p�[�e�B�N���������Ԃ̏��
	int											parTime;				//�p�[�e�B�N���̎���
	bool										parFlag;				//�p�[�e�B�N�����o�邩�̃t���O
	int											count;					//���S������`�悷�鎞��
	std::unique_ptr<CSoundSource>				seEnemyDeath;			//���S����SE
};

