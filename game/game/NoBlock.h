#pragma once
#include "Model.h"


class CNoBlock {
public:
	enum class NoblockState
	{
		hit,			//プレイヤーと当たった				見える
		nohit			//プレイヤーと当たっていない		見えない
	};
	//コンストラクタ
	CNoBlock();
	//デストラクタ
	~CNoBlock();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix);
	//開放。
	void Release();
	//座標を設定。
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
	const NoblockState& GetState() const
	{
		return state;
	}
	void SetState(const NoblockState& sta)
	{
		state = sta;
	}
	const btRigidBody *Get2Dnoblock() const
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
	NoblockState			state;			//はてなの状態
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_noblockboxShape = NULL;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3Dnoblock = NULL;	//剛体3D。
	btRigidBody*		m_rigidBody2Dnoblock = NULL;	//剛体2D。
	btDefaultMotionState* m_myMotionState = NULL;
	bool				m_isAdd2DCollision;
};