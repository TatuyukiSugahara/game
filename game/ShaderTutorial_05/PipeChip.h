#pragma once
#include "Model.h"

//マップチップの配置情報。
struct SPipeChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//大きさ	
};
class CPipeChip
{
public:
	CPipeChip();
	~CPipeChip();
	void Init();
	//更新。
	void Update();
	//描画。
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
	D3DXVECTOR3							Scale;			//大きさ
	D3DXMATRIX							mScale;			//matrixスケール
	D3DXMATRIX							mWorld;			//ワールド行列。
};

