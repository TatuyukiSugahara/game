#pragma once
#include "Frame\Model.h"
#include "Frame\Texture.h"

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
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix
		);
	//�J���B
	void Release();
private:
	D3DXVECTOR3				position;		//���W�B
	D3DXVECTOR3				scale;			//�X�P�[��
	D3DXQUATERNION			rotation;		//��]	
	SkinModel				skinModel;		//���f��
	SkinModelData			modelData;		//���f���f�[�^
	Animation				animation;		//�A�j���[�V����
	CLight					light;			//���C�g
	CTexture				texture;		//�e�N�X�`��
};