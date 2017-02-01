#pragma once
#include "Model.h"
#include "IsIntersect\IsIntersect.h"

class IPlayerCollisionCallback;

enum KinokoState
{
	none,	//キノコがでてない
	Leave	//キノコが出ている
};

class CKinoko {
public:
	//コンストラクタ
	CKinoko();
	//デストラクタ
	~CKinoko();
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
	void SetKinoko(bool flag)
	{
		kinoko = flag;
	}
	bool GetKinoko()
	{
		return kinoko;
	}
	//ステートセット
	void SetState(KinokoState kinoko)
	{
		state = kinoko;
	}
	//ステートゲット
	KinokoState GetState()
	{
		return state;
	}
private:
	D3DXVECTOR3				position;		//座標。。
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	Model					model;			//モデル。
	D3DXVECTOR3				movespeed;
	float					radius;
	KinokoState				state;			//キノコの状態
	bool					kinoko;			//キノコをプレイヤーはゲットしている？
	/*AABB*/
	D3DXVECTOR3 m_aabbMin;
	D3DXVECTOR3 m_aabbMax;
};