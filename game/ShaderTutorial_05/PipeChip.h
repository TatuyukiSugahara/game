#pragma once
#include "Model.h"


class CPipeChip
{
public:
	CPipeChip();
	~CPipeChip();
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render();
	void SetPos(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	void SetRot(D3DXQUATERNION rot)
	{
		rotation = rot;
	}
	void SetScale(D3DXVECTOR3 scale)
	{
		Scale = scale;
	}
private:
	SkinModel skinmodel;
	SkinModelData* modelData;
	Animation animation;
	CLight	light;
	D3DXMATRIX							mRot;
	D3DXVECTOR3							position;
	D3DXQUATERNION						rotation;
	D3DXVECTOR3							Scale;			//�傫��
	D3DXMATRIX							mScale;			//matrix�X�P�[��
	D3DXMATRIX							mWorld;			//���[���h�s��B
};

