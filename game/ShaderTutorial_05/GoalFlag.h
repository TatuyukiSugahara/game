#pragma once
#include "Model.h"
//�y��
class CGoalFlag {
public:
	//�R���X�g���N�^
	CGoalFlag();
	//�f�X�g���N�^
	~CGoalFlag();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render();
	//�J���B
	void Release();
	//���W��ݒ�B
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
private:
	D3DXVECTOR3				position;		//���W�B�B
	D3DXVECTOR3				scale;			//�傫��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXMATRIX				mRotation;		//��]�s��B
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
};