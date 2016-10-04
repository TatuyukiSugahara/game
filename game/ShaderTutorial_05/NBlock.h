#pragma once
#include "Model.h"

enum BlockState
{
	yes,		//ブロックある
	no			//ブロックない
};

//ノーマルブロック
class CNBlock {
public:
	//コンストラクタ
	CNBlock();
	//デストラクタ
	~CNBlock();
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
	void CreateCollision2D();				//2Dあたり判定
	void Add2DRigidBody();					//2Dあたり判定追加
	void Remove2DRigidBody();				//2Dあたり判定削除
	btRigidBody *Get2DBlock()
	{
		return m_rigidBody2Dblock;
	}
	void SetState(BlockState sta)
	{
		state = sta;
	}
private:
	D3DXVECTOR3				position;		//座標。。
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	Model					model;			//モデル。
	BlockState				state;
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_blockboxShape;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3Dblock;	//剛体3D。
	btRigidBody*		m_rigidBody2Dblock;	//剛体2D。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
};