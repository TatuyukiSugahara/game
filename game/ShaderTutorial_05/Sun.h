#pragma once

class CSun {
public:
	//�R���X�g���N�^
	CSun();
	//�f�X�g���N�^
	~CSun();
	//�������B
	void Init();
	//�X�V�B
	void Update();
	//�`��B
	void Render();
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXMATRIX				mWorld;			//���[���h�s��B
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
};