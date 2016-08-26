#pragma once
#include "Model.h"
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"

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
		int numDiffuseLight
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
	void Move();
	void Jump();
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				movespeed;		//�ړ����x
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Model					model;			//���f���B
	CIsIntersect			IsIntersect;		//�����蔻��
	std::vector<IPlayerCollisionCallback*>	callbackList;
	const float				MOVE_SPEED = 0.1f;	//�ړ����x
	PlayerState				state;
};