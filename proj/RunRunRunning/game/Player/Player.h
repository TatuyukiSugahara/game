#pragma once
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Frame\Turn.h"
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
		return moveSpeed;
	}
	//�v���C���[��AABB��MAX���Q�b�g
	const D3DXVECTOR3& GetAABBMax() const
	{
		return aabbMaxGet;
	}
	//�v���C���[��AABB��MIN���Q�b�g
	const D3DXVECTOR3& GetAABBMin() const
	{
		return aabbMinGet;
	}
	//�v���C���[�̃L�����N�^�[�R���g���[���[�Q�b�g
	CCharacterController& GetcharacterController()
	{
		return characterController;
	}
	//effect�Z�b�g�B
	void SetEffect(ID3DXEffect* effect)
	{
		skinModel.SetEffect(effect);
	}
	//�G�t�F�N�g�Q�b�g
	const ID3DXEffect* GetEffect() const
	{
		return skinModel.GetEffect();
	}
	//�ړ����x�Z�b�g
	void SetMoveSpeed(const D3DXVECTOR3& speed)
	{
		moveSpeed = speed;
	}
	//�v���C���[���C�t�X�e�[�g�Q�b�g
	const Life& GetLifeState() const
	{
		return lifeState;
	}
	//���C�t�X�e�[�g�Z�b�g
	void SetLifeState(const Life& life)
	{
		lifeState = life;
	}
	//�X�P�[���Z�b�g
	void SetScale(const D3DXVECTOR3& scal)
	{
		scale = scal;
	}
	//�X�P�[���Q�b�g
	const D3DXVECTOR3& GetScale() const
	{
		return scale;
	}
	//�X�P�[�������Z
	void SubScale(const D3DXVECTOR3& sub)
	{
		scale -= sub;
	}
	//�X�P�[�������Z
	void AddScale(const D3DXVECTOR3& add)
	{
		scale += add;
	}
	//�v���C���[�X�e�[�g�Z�b�g
	void SetState(const PlayerState& state)
	{
		this->state = state;
	}
	//�v���C���[��Î~������t���O�Z�b�g
	void SetPlyaerStop(const bool& stop)
	{
		playerStop = stop;
	}
	//�v���C���[�Î~������t���O�Q�b�g
	const bool& GetPlayerStop() const
	{
		return playerStop;
	}
	//���S���ԃZ�b�g
	void SetDiedTime(const float& time)
	{
		diedTime = time;
	}
	//�v���C���[�ړ��֐�
	void Move(float maxmove);
	//�v���C���[�W�����v�֐�
	void Jump();
	//�v���C���[�̃X�e�[�g�֐�
	void State();
	//���S�֐�
	void Died();
	//�N���A���֐�		
	void Clear();		
private:
	D3DXVECTOR3						position;						//���W�B
	D3DXVECTOR3						moveSpeed;						//�ړ����x
	D3DXVECTOR3						scale;							//�X�P�[��w
	SkinModel						skinModel;						//�I���W�i��
	SkinModel						skinModelMorpA;						//���[�t�B���O�pA
	SkinModel						skinModelMorpB;						//���[�t�B���O�pB
	SkinModelData					modelData;						//�I���W�i��
	SkinModelData					modelDataMorpA;						//���[�t�B���O�pA
	SkinModelData					modelDataMorpB;						//���[�t�B���O�pB
	Animation 						animation;						//�A�j���[�V����
	CLight							light;							//���C�g
	LPDIRECT3DTEXTURE9				normalMap = NULL;				//�m�[�}���}�b�v
	LPDIRECT3DTEXTURE9				specularMap = NULL;				//�X�y�L�����}�b�v�B
	CTurn							turn;							//�^�[���N���X
	CCharacterController			characterController;			//�L�����N�^�[�R���g���[���[
	PlayerState						state;							//�v���C���[�̏��
	Life							lifeState;						//�v���C���[����
	D3DXQUATERNION					rotation;						//��]�N�H�[�^�j�I��
	D3DXVECTOR3						addMove;						//�ړ����x���Z�̂���
	D3DXVECTOR3						aabbMin;						//AABB�̏����l
	D3DXVECTOR3						aabbMax;						//AABB�̏����l
	D3DXVECTOR3						aabbMinGet;						//AABB�Ƀv���C���[�̍��̏ꏊ�𑫂����Ƃ���
	D3DXVECTOR3						aabbMaxGet;						//AABB�Ƀv���C���[�̍��̏ꏊ�𑫂����Ƃ���
	std::unique_ptr<CSoundSource>	seJump;							//�W�����vSE
	float							radius;							//���a
	float							friction;						//���C
	float							deathCount;						//���S�܂ł̃J�E���g
	bool							playerStop = false;				//�����Ȃ����
	float							diedTime = 0.0f;				//���S���鎞��
	float							rate;							//���[�t�B���O�p����
	float							currentAngleY;					//���݂̃A���O��
	float							targetAngleY;					//�^�[�Q�b�g�̃A���O��
};