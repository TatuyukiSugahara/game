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
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
	void SetScale(const D3DXVECTOR3& scale)
	{
		this->scale = scale;
	}
private:
	SkinModel							skinmodel;		//���f��
	SkinModelData*						modelData;		//���f���f�[�^
	Animation							animation;		//�A�j���[�V����
	CLight								light;			//���C�g
	D3DXVECTOR3							position;		//���W
	D3DXQUATERNION						rotation;		//��]
	D3DXVECTOR3							scale;			//�傫��
};

