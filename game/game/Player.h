#pragma once
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Turn.h"
#include "character\CharacterController.h"

//�v���C���[�N���X�B
class CPlayer {
public:
	enum class PlayerState {
		Stay,			//�X�e�C
		Walk,			//����
		Run,			//����
		Jump,			//�W�����v
		IsJump,			//�W�����v������Ƃ�
		JumpNow,		//�W�����v��
		JumpWas,		//���n��
		HipDrop,		//�q�b�v�h���b�v
		Happy,			//���
	};
	enum class Life{
		Alive,				//�����Ă���
		Died,				//����
	};
	//�R���X�g���N�^
	CPlayer();
	//�f�X�g���N�^
	~CPlayer();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap
		);
	//�J���B
	void Release();
	//���W��ݒ�B
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
		characterController.SetPosition(pos);
	}
	//�|�W�V�����Q�b�g
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	} 
	//�ړ����x�Q�b�g
	const D3DXVECTOR3& GetMoveSpeed() const
	{
		return movespeed;
	}
	//�v���C���[��AABB��MAX���Q�b�g
	const D3DXVECTOR3& GetAABBMax() const
	{
		return aabbMaxget;
	}
	//�v���C���[��AABB��MIN���Q�b�g
	const D3DXVECTOR3& GetAABBMin() const
	{
		return aabbMinget;
	}
	const D3DXMATRIX& GetRot() const
	{
		return mRotation;
	}
	CCharacterController& GetcharacterController()
	{
		return characterController;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		skinmodel.SetEffect(effect);
	}
	const ID3DXEffect* GetEffect() const
	{
		return skinmodel.GetEffect();
	}
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		movespeed = speed;
	}
	const Life& GetLifeState() const
	{
		return lifestate;
	}
	void SetLifeState(const Life& life)
	{
		lifestate = life;
	}
	void SetScale(const D3DXVECTOR3& scal)
	{
		scale = scal;
	}
	const D3DXVECTOR3& GetScale() const
	{
		return scale;
	}
	void SubScale(const D3DXVECTOR3& sub)
	{
		scale -= sub;
	}
	void AddScale(const D3DXVECTOR3& add)
	{
		scale += add;
	}
	void SetState(const PlayerState& state)
	{
		this->state = state;
	}
	void SetPlyaerStop(const bool& stop)
	{
		playerstop = stop;
	}
	const bool& GetPlayerStop() const
	{
		return playerstop;
	}
	void SetDiedTime(const float& time)
	{
		diedTime = time;
	}
	void Move(float maxmove);
	void Jump();
	void State();
	void Died();		//���S
	void Clear();		//�N���A��
private:
	D3DXVECTOR3						position;						//���W�B
	D3DXVECTOR3						movespeed;						//�ړ����x
	D3DXVECTOR3						scale;							//�X�P�[��w
	D3DXMATRIX						mRotation;						//��]�s��B
	SkinModel						skinmodel;						//�I���W�i��
	SkinModel						skinmodelA;						//���[�t�B���O�pA
	SkinModel						skinmodelB;						//���[�t�B���O�pB
	SkinModelData					modelData;						//�I���W�i��
	SkinModelData					modelDataA;						//���[�t�B���O�pA
	SkinModelData					modelDataB;						//���[�t�B���O�pB
	Animation 						animation;						//�A�j���[�V����
	CLight							light;							//���C�g
	LPDIRECT3DTEXTURE9				normalMap = NULL;				//�m�[�}���}�b�v
	LPDIRECT3DTEXTURE9				specularMap = NULL;				//�X�y�L�����}�b�v�B
	CTurn							turn;							//�^�[���N���X
	CCharacterController			characterController;			//�L�����N�^�[�R���g���[���[
	PlayerState						state;							//�v���C���[�̏��
	Life							lifestate;						//�v���C���[����
	D3DXQUATERNION					rotation;						//��]�N�H�[�^�j�I��
	D3DXVECTOR3						addmove;						//���̈ړ�
	D3DXVECTOR3						aabbMin;						//AABB�̏����l
	D3DXVECTOR3						aabbMax;						//AABB�̏����l
	D3DXVECTOR3						aabbMinget;						//AABB�Ƀv���C���[�̍��̏ꏊ�𑫂����Ƃ���
	D3DXVECTOR3						aabbMaxget;						//AABB�Ƀv���C���[�̍��̏ꏊ�𑫂����Ƃ���
	std::unique_ptr<CSoundSource>	SEjump;							//�W�����vSE
	float							radius;							//���a
	float							friction;						//���C
	float							deathCount;						//���S�܂ł̃J�E���g
	bool							playerstop = false;				//�����Ȃ����
	float							diedTime = 0.0f;				//���S���鎞��
	float							rate;							//���[�t�B���O�p����
	float							currentAngleY;					//���݂̃A���O��
	float							targetAngleY;					//�^�[�Q�b�g�̃A���O��

	

};