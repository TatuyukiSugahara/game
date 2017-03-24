#pragma once
#include "Frame\Model.h"

class CHatenaBox {
public:
	enum class HatenaState
	{
		hit,			//プレイヤーと当たった
		nohit			//プレイヤーと当たっていない
	};
	//コンストラクタ
	CHatenaBox();
	//デストラクタ
	~CHatenaBox();
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
	const HatenaState& GetState() const
	{
		return state;
	}
	//ステートセット
	void SetState(const HatenaState& sta)
	{
		state = sta;
	}
	//剛体ゲット
	const btRigidBody *GetHatena() const
	{
		return rigidBodyHatena;
	}
	//あたり判定作成
	void CreateCollision();
	//あたり判定追加
	void AddRigidBody();		
private:
	D3DXVECTOR3				position;				//座標。
	D3DXMATRIX				mWorld;					//ワールド行列。
	D3DXMATRIX				mRotation;				//回転行列。
	Model					model;					//モデル。
	HatenaState				state;					//はてなの状態
	btCollisionShape*		hatenaboxShape;			//地面のコリジョン形状。
	btRigidBody*			rigidBodyHatena = NULL;	//剛体
	btDefaultMotionState*	myMotionState;			//モーションステート
	bool					isAddCollision;			//コリジョン追加フラグ
};