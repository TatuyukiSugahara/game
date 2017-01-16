#pragma once
#include "Model.h"

class CStageBack {
public:
	//�R���X�g���N�^
	CStageBack();
	//�f�X�g���N�^
	~CStageBack();
	//�������B
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//�X�V�B
	void Update();
	//�`��B
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix
		);
	//�J���B
	void Release();
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	D3DXVECTOR3				targetPos;		//�^�[�Q�b�g�̃|�W�V����
};