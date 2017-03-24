#pragma once
class CGoal {
public:
	//コンストラクタ
	CGoal();
	//デストラクタ
	~CGoal();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
	//AABBの範囲に入っているか。
	void AabbUpdate();
	//座標を設定。
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
private:
	D3DXVECTOR3		position;		//座標
	D3DXVECTOR3		scale;			//大きさ
	SkinModel		skinModel;		//モデル	
	SkinModelData	modelData;		//モデルデータ
	Animation		animation;		//アニメーション
	CLight			light;			//ライト
	D3DXVECTOR3		aabbMin;		//AABBの最小
	D3DXVECTOR3		aabbMax;		//AABBの最大
};