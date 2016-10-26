#pragma once
#include "Model.h"
#include "lib\System.h"
#include "IsIntersect\IsIntersect.h"
#include "Turn.h"

class IPlayerCollisionCallback;

enum PlayerState{
	PlayerStay,			//ステイ
	PlayerWalk,			//歩く
	PlayerRun,			//走る
	PlayerJump,			//ジャンプ
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
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
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
	CIsIntersect GetIsIntersect()
	{
		return IsIntersect;
	}
	void SetEffect(ID3DXEffect* effect)
	{
		skinmodel.SetEffect(effect);
	}
	ID3DXEffect* GetEffect()
	{
		return skinmodel.GetEffect();
	}
	void Move2D();
	void Move3D();
	void Jump();
	void Died();//死亡
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				movespeed;		//移動速度
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	D3DXMATRIX				mScale;			//スケールw
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	CIsIntersect			IsIntersect;		//あたり判定
	CTurn					turn;			//ターンクラス
	std::vector<IPlayerCollisionCallback*>	callbackList;//
	const float				MOVE_SPEED = 5.0f;	//移動速度
	float					radius;
	PlayerState				state;				//プレイヤーの状態
	D3DXQUATERNION			rotation;		//回転クォータニオン
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
	//ターン
	float					m_currentAngleY;
	float					m_targetAngleY;
	bool					AnimationRun;
};