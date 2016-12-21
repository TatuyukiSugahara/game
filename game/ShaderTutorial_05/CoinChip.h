#pragma once

//マップチップの配置情報。
struct SCoinChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;		//回転。
};
class CCoinChip
{
public:
	CCoinChip();
	~CCoinChip();
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
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
	bool GetCoin()
	{
		return coinget;
	}
private:
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	D3DXMATRIX							mRot;
	D3DXVECTOR3							position;
	D3DXQUATERNION						rotation;
	D3DXMATRIX							mWorld;			//ワールド行列。
	int									size;
	bool								coinget;		//コインをゲットしたかフラグ。
};

