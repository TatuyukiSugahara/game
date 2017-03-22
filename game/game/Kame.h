#pragma once
#include "character\CharacterController.h"

class CKame {
public:
	//コンストラクタ
	CKame();
	//デストラクタ
	~CKame();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool shadow
		);
	//AABBの範囲に入っているか。
	void AabbUpdate();
	//座標を設定。
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//キャラクターコントローラー初期化
	void CharConInit();
	//キャラクターコントローラー更新
	void CharConUpdate();
	//あたり判定。
	void Hit();
	//高さをゲット
	const float& GetHeight() const
	{
		return HEIGHT;
	}
	//半径をゲット
	const float& GetRadius() const
	{
		return RADIUS;
	}
private:
	D3DXVECTOR3				position;		//座標
	D3DXVECTOR3				scale;			//大きさ
	D3DXQUATERNION			rotation;		//回転
	D3DXVECTOR3				moveSpeed;		//移動速度
	SkinModel				skinModel;
	SkinModelData			modelData;
	Animation				animation;
	CLight					light;
	CCharacterController	characterController;	//キャラクターコントローラー
	const float				SPEED = 10.0f;			//速度を設定。
	const float				HEIGHT = 0.5f;			//高さ
	const float				RADIUS = 0.5f;			//半径
};