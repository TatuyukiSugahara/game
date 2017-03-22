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
	//座標ゲット
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
	//ステートゲット
	const NoblockState& GetState() const
	{
		return state;
	}
	//ステートセット
	void SetState(const NoblockState& sta)
	{
		state = sta;
	}
	//見えないブロックの剛体ゲット
	const btRigidBody *Getnoblock() const
	{
		return rigidBodynoblock;
	}
	//あたり判定作成
	void CreateCollision();					
	//あたり判定追加
	void AddRigidBody();						
private:
	D3DXVECTOR3				position;				//座標。
	D3DXVECTOR3				scale;					//スケール
	D3DXQUATERNION			rotation;				//回転
	SkinModel				skinModel;				//モデル
	SkinModelData			modelData;				//モデルデータ
	Animation				animation;				//アニメーション
	CLight					light;					//ライト
	NoblockState			state;					//見えないブロックの状態
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	noblockboxShape = NULL;		//地面のコリジョン形状。
	btRigidBody*		rigidBodynoblock = NULL;	//剛体。
	btDefaultMotionState* myMotionState = NULL;		//モーションステート
	bool				isAddCollision;				//コリジョン追加フラグ
};