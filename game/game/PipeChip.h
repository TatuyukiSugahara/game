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
		Scale = scale;
	}
private:
	SkinModel skinmodel;
	SkinModelData* modelData;
	Animation animation;
	CLight	light;
	D3DXVECTOR3							position;
	D3DXQUATERNION						rotation;
	D3DXVECTOR3							Scale;			//�傫��
};

