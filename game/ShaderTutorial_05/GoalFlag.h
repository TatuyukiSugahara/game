#pragma once
#include "Model.h"
//土管
class CGoalFlag {
public:
	//コンストラクタ
	CGoalFlag();
	//デストラクタ
	~CGoalFlag();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render();
	//開放。
	void Release();
	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
private:
	D3DXVECTOR3				position;		//座標。。
	D3DXVECTOR3				scale;			//大きさ
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
};