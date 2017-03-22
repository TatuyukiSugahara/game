#pragma once


class CCoinChip
{
public:
	CCoinChip();
	~CCoinChip();
	//初期化
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//座標セット
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//加点セット
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
	//コインゲットしたかフラグゲット
	const bool& GetCoin() const
	{
		return coinGet;
	}
private:
	SkinModel						skinModel;		//モデル
	SkinModelData*					modelData;		//モデルデータ
	Animation						animation;		//アニメーション
	CLight							light;			//ライト
	D3DXVECTOR3						position;		//座標
	D3DXVECTOR3						scale;			//大きさ
	D3DXVECTOR3						scaleShadow;	//大きさ影用
	D3DXQUATERNION					rotation;		//回転
	bool							coinGet;		//コインをゲットしたかフラグ。
	std::unique_ptr<CSoundSource>	soundSource;	//コインゲットSE
};

