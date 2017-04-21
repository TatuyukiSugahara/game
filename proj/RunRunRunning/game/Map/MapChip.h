#pragma once

class CMapChip
{
public:
	CMapChip();
	~CMapChip();
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	//座標をセット
	void SetPos(const D3DXVECTOR3& pos)
	{
		position=pos;
	}
	//回転をセット
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
private:
	SkinModel			skinModel;	//モデル
	SkinModelData*		modelData;	//モデルデータ
	Animation			animation;	//アニメーション
	CLight				light;		//ライト
	D3DXVECTOR3			position;	//座標
	D3DXQUATERNION		rotation;	//回転
};

