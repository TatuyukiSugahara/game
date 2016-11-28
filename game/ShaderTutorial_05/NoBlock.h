#pragma once
#include "Model.h"

enum noblockState
{
	noblockhit,			//プレイヤーと当たった				見える
	noblocknohit			//プレイヤーと当たっていない		見えない
};

class CNoBlock {
public:
	//コンストラクタ
	CNoBlock();
	//デストラクタ
	~CNoBlock();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render();
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
	noblockState GetState()
	{
		return state;
	}
	void SetState(noblockState sta)
	{
		state = sta;
	}
	btRigidBody *Get2Dnoblock()
	{
		return m_rigidBody2Dnoblock;
	}
	void CreateCollision2D();				//2Dあたり判定
	void Add2DRigidBody();		//2Dあたり判定追加
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXQUATERNION			rotation;
	SkinModel				skinmodel;
	SkinModelData			modelData;
	Animation				animation;
	CLight					light;
	noblockState			state;			//はてなの状態
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_noblockboxShape;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3Dnoblock;	//剛体3D。
	btRigidBody*		m_rigidBody2Dnoblock;	//剛体2D。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
};