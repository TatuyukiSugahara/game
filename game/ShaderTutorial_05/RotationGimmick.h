#pragma once

class CRotationGimmick
{
public:
	CRotationGimmick();
	~CRotationGimmick();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos)
	{
		*position = pos;
	}
	D3DXVECTOR3 GetPos()
	{
		return *position;
	}
private:
	D3DXVECTOR3				originPos;		//原点の座標
	D3DXVECTOR3				position[3];	//座標。。
	D3DXVECTOR3				vector;			//向き
	D3DXVECTOR3				scale;			//大きさ
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	SkinModel skinmodel[3];
	SkinModelData modelData[3];
	Animation animation;
	CLight	light;
};

