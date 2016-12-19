#pragma once
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Turn.h"
#include "character\CharacterController.h"

class IPlayerCollisionCallback;

enum PlayerState{
	PlayerStay,			//�X�e�C
	PlayerWalk,			//����
	PlayerRun,			//����
	PlayerJump,			//�W�����v
	PlayerIsJump,		//�W�����v������Ƃ�
	PlayerJumpNow,		//�W�����v��
	PlayerJumpWas,		//���n��
};

//�v���C���[�N���X�B
class CPlayer {
public:
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
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap
		);
	//�J���B
	void Release();
	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
	D3DXVECTOR3 GetMoveSpeed()
	{
		return movespeed;
	}
	/*D3DXVECTOR3 GetAddPos()
	{
		return IsIntersect.GetAddPos();
	}*/
	D3DXVECTOR3 GetAABBMax()
	{
		return m_aabbMax;
	}
	D3DXVECTOR3 GetAABBMin()
	{
		return m_aabbMin;
	}
	D3DXMATRIX GetWMatrix()
	{
		return mWorld;
	}
	D3DXMATRIX GetRot()
	{
		return mRotation;
	}
	/*CIsIntersect GetIsIntersect()
	{
		return IsIntersect;
	}*/
	CCharacterController& GetcharacterController()
	{
		return characterController;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		skinmodel.SetEffect(effect);
	}
	ID3DXEffect* GetEffect()
	{
		return skinmodel.GetEffect();
	}
	void SetMoveSpeed(D3DXVECTOR3 speed)
	{
		movespeed = speed;
	}
	void Move(float maxmove);
	void Jump();
	void State();
	void Died();//���S
private:
	D3DXVECTOR3				position;						//���W�B
	D3DXVECTOR3				movespeed;						//�ړ����x
	D3DXVECTOR3				Scale;							//�X�P�[��w
	D3DXMATRIX				mWorld;							//���[���h�s��B
	D3DXMATRIX				mRotation;						//��]�s��B
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	LPDIRECT3DTEXTURE9 normalMap = NULL;					//�m�[�}���}�b�v
	LPDIRECT3DTEXTURE9 specularMap = NULL;					//�X�y�L�����}�b�v�B
	CTurn					turn;							//�^�[���N���X
	CCharacterController characterController;				//�L�����N�^�[�R���g���[���[
	std::vector<IPlayerCollisionCallback*>	callbackList;	//
	const float				MOVE_SPEED = 5.0f;				//�ړ����x
	float					radius;
	float					friction;						//���C
	PlayerState				state;							//�v���C���[�̏��
	D3DXQUATERNION			rotation;						//��]�N�H�[�^�j�I��
	float					deathCount;						//���S�܂ł̃J�E���g
	D3DXVECTOR3				addmove;							//���̈ړ�
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//�^�[��
	float					m_currentAngleY;
	float					m_targetAngleY;
};