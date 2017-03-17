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
	const btRigidBody *Getnoblock() const
	{
		return rigidBodynoblock;
	}
	void CreateCollision();				//2Dあたり判定
	void AddRigidBody();		//2Dあたり判定追加
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXQUATERNION			rotation;
	SkinModel				skinModel;
	SkinModelData			modelData;
	Animation				animation;
	CLight					light;
	NoblockState			state;			//見えないブロックの状態
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	noblockboxShape = NULL;	//地面のコリジョン形状。
	btRigidBody*		rigidBodynoblock = NULL;	//剛体。
	btDefaultMotionState* myMotionState = NULL;
	bool				isAddCollision;
};