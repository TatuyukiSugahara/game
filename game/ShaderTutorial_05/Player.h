#pragma once
#include "Model.h"
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Turn.h"

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
		int numDiffuseLight,
		bool isDrawToShadowMap
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
	D3DXVECTOR3 GetMoveSpeed()
	{
		return movespeed;
	}
	D3DXVECTOR3 GetAddPos()
	{
		return IsIntersect.GetAddPos();
	}
	D3DXVECTOR3 GetAABBMax()
	{
		return m_aabbMax;
	}
	D3DXVECTOR3 GetAABBMin()
	{
		return m_aabbMin;
	}
	D3DXMATRIX GetWMatrix()
	{
		return mWorld;
	}
	D3DXMATRIX GetRot()
	{
		return mRotation;
	}
	void Move2D();
	void Move3D();
	void Jump();
	void Died();							//死亡
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				movespeed;		//移動速度
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	D3DXMATRIX				mScale;			//スケールw a
	Model					model;			//モデル。
	CIsIntersect			IsIntersect;		//あたり判定
	CTurn					turn;			//ターンクラス
	std::vector<IPlayerCollisionCallback*>	callbackList;//
	const float				MOVE_SPEED = 5.0f;	//移動速度
	float					radius;
	PlayerState				state;				//プレイヤーの状態
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//ターン
	float					m_currentAngleY;
	float					m_targetAngleY;
};