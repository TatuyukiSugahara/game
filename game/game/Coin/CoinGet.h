#pragma once 

class CCoinGet
{
public:
	CCoinGet();
	~CCoinGet();
	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//ポジションセット
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//回転セット
	void SetRotFlag(const bool& flag)
	{
		rot = flag;
	}
private:
	SkinModel			skinModel;				//モデル
	SkinModelData		modelData;				//モデルデータ
	Animation			animation;				//アニメーション
	CLight				light;					//ライト
	LPDIRECT3DTEXTURE9	normalMap = NULL;		//ノーマルマップ
	D3DXVECTOR3			position;				//座標
	D3DXVECTOR3			scale;					//大きさ
	D3DXQUATERNION		rotation;				//回転
	bool				rot = false;			//回転フラグ
	float				time = 0.0f;			//回転する時間
};