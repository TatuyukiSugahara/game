#pragma once
#include "Model.h"
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"

class IPlayerCollisionCallback;

enum PlayerState{
	PlayerStay,
	PlayerWalk,
	PlayerRun,
	PlayerJump,
};

//プレイヤークラス。
class CPlayer {
public:
	//コンストラクタ
	CPlayer();
	//デストラクタ
	~CPlayer();
	//初期化。
	void Init(LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		LPDIRECT3DDEVICE9 pd3dDevice,
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		D3DXVECTOR4* diffuseLightDirection,
		D3DXVECTOR4* diffuseLightColor,
		D3DXVECTOR4	 ambientLight,
		int numDiffuseLight
		);
	//開放。
	void Release();
	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
	void Move();
	void Jump();
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				movespeed;		//移動速度
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	Model					model;			//モデル。
	CIsIntersect			IsIntersect;		//あたり判定
	std::vector<IPlayerCollisionCallback*>	callbackList;
	const float				MOVE_SPEED = 0.1f;	//移動速度
	PlayerState				state;
};