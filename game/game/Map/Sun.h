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
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXQUATERNION			rotation;		//回転	
	SkinModel				skinModel;		//モデル
	SkinModelData			modelData;		//モデルデータ
	Animation				animation;		//アニメーション
	CLight					light;			//ライト
};