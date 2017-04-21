#pragma once
#include "Frame\Model.h"
#include "Frame\Texture.h"

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
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix
		);
	//開放。
	void Release();
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXQUATERNION			rotation;		//回転	
	SkinModel				skinModel;		//モデル
	SkinModelData			modelData;		//モデルデータ
	Animation				animation;		//アニメーション
	CLight					light;			//ライト
	CTexture				texture;		//テクスチャ
};