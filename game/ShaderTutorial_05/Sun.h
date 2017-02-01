#pragma once

class CSun {
public:
	//コンストラクタ
	CSun();
	//デストラクタ
	~CSun();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render();
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
};