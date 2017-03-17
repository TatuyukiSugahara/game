#pragma once
#include "Model.h"


class CMapChip
{
public:
	CMapChip();
	~CMapChip();
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	void SetPos(const D3DXVECTOR3& pos)
	{
		position=pos;
	}
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
private:
	SkinModel skinModel;
	SkinModelData* modelData;
	Animation animation;
	CLight	light;
	D3DXVECTOR3							position;
	D3DXQUATERNION						rotation;
	int									size;
};

