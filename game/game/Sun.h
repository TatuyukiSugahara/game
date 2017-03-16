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
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXQUATERNION			rotation;		//��]	
	SkinModel				skinModel;		//���f��
	SkinModelData			modelData;		//���f���f�[�^
	Animation				animation;		//�A�j���[�V����
	CLight					light;			//���C�g
};