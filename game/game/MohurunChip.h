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
	//���t�����̃X�e�[�g�Q�b�g
	const MohurunState& GetState() const
	{
		return state;
	}
	//�X�e�[�g�Z�b�g
	void SetState(const MohurunState& state)
	{
		this->state = state;
	}
	//���W�Q�b�g
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
private:
	MohurunState 					state;					//�X�e�[�g
	D3DXVECTOR3						position;				//���W
	D3DXVECTOR3						scale;					//�傫��
	D3DXVECTOR3						moveSpeed;				//�ړ����x
	D3DXQUATERNION					rotation;				//��]
	SkinModel						skinModel;				//���f��
	static SkinModelData*			orgSkinModelData;		//�X�L�����f���f�[�^�B
	SkinModelData					modelData;				//���f���f�[�^
	Animation						animation;				//�A�j���[�V����
	Animation*						orgAnimation;			//�I���W�i���̃A�j���[�V����
	CLight							light;					//���C�g
	CCharacterController			characterController;	//�L�����N�^�[�R���g���[���[
	SParicleEmitParameter			param;					//�p�[�e�B�N��
	std::list<CParticleEmitter*>	particleEmitterList;	//�p�[�e�B�N�����X�g
	const int						MAXPAR = 50;			//�p�[�e�B�N���������Ԃ̏��
	int								parTime;				//�p�[�e�B�N���̎���
	bool							parFlag;				//�p�[�e�B�N�����o�邩�̃t���O
	int								count;					//�|�����㐔�b�\�������邽�߂̎���
	std::unique_ptr<CSoundSource>	seEnemyDeath;			//���S��������SE
};

