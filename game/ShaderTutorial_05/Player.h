#pragma once
#include "Model.h"
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Turn.h"

class IPlayerCollisionCallback;

enum PlayerState{
	PlayerStay,
	PlayerWalk,
	PlayerRun,
	PlayerJump,
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
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight,
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
	D3DXVECTOR3 GetAddPos()
	{
		return IsIntersect.GetAddPos();
	}
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
	void Move2D();
	void Move3D();
	void Jump();
	void Died();							//���S
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				movespeed;		//�ړ����x
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	D3DXMATRIX				mScale;			//�X�P�[��w a
	Model					model;			//���f���B
	CIsIntersect			IsIntersect;		//�����蔻��
	CTurn					turn;			//�^�[���N���X
	std::vector<IPlayerCollisionCallback*>	callbackList;//
	const float				MOVE_SPEED = 5.0f;	//�ړ����x
	float					radius;
	PlayerState				state;				//�v���C���[�̏��
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//�^�[��
	float					m_currentAngleY;
	float					m_targetAngleY;
};