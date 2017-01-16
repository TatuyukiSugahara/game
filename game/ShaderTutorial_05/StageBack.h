#pragma once
#include "Model.h"

class CStageBack {
public:
	//コンストラクタ
	CStageBack();
	//デストラクタ
	~CStageBack();
	//初期化。
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix
		);
	//開放。
	void Release();
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	D3DXVECTOR3				targetPos;		//ターゲットのポジション
};