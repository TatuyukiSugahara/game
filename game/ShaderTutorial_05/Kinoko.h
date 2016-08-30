#pragma once
#include "Model.h"
#include "IsIntersect\IsIntersect.h"

class IPlayerCollisionCallback;

class CKinoko {
public:
	//�R���X�g���N�^
	CKinoko();
	//�f�X�g���N�^
	~CKinoko();
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
private:
	D3DXVECTOR3				position;		//���W�B�B
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	Model					model;			//���f���B
	CIsIntersect			IsIntersect;		//�����蔻��
	std::vector<IPlayerCollisionCallback*>	callbackList;//
	D3DXVECTOR3				movespeed;
};