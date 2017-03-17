#pragma once
#include "Model.h"


class CPipeChip
{
public:
	CPipeChip();
	~CPipeChip();
	void Init();
	//更新。
	void Update();
	//描画。
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
	SkinModel							skinmodel;		//モデル
	SkinModelData*						modelData;		//モデルデータ
	Animation							animation;		//アニメーション
	CLight								light;			//ライト
	D3DXVECTOR3							position;		//座標
	D3DXQUATERNION						rotation;		//回転
	D3DXVECTOR3							scale;			//大きさ
};

