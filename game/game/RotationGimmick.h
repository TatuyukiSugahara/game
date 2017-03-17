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
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
	//座標を設定。
	void SetPosition(const D3DXVECTOR3& pos)
	{
		*position = pos;
	} 
	//ポジションゲット
	const D3DXVECTOR3& GetPos() const
	{
		return *position;
	}
private:
	D3DXVECTOR3				originPos;		//原点の座標
	D3DXVECTOR3				position[3];	//座標。
	D3DXVECTOR3				vector;			//向き
	D3DXVECTOR3				scale;			//大きさ
	D3DXMATRIX				rotation;		//回転行列。
	SkinModel				skinModel[3];	//スキンモデル
	SkinModelData			modelData[3];	//モデルデータ
	Animation				animation;		//アニメーション
	CLight					light;			//ライト
};

