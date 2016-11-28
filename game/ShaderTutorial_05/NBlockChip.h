#pragma once
#include "Particle\ParticleEmitter.h"
enum AnimState
{
	BlockOn,				//アニメーションする
	BlockOff,			//アニメーションしない
};

//マップチップの配置情報。
struct SBlockChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;	//回転。
	D3DXVECTOR3 scale;			//大きさ	
};

//見えるブロック

class CNBlockChip
{
public:
	CNBlockChip();
	~CNBlockChip();
	void Init();
	//更新。
	void Update();
	//描画。
	void Render();
	void SetPos(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	void SetRot(D3DXQUATERNION rot)
	{
		rotation = rot;
	}
	void SetScale(D3DXVECTOR3 scale)
	{
		this->scale = scale;
	}
	void SetLost(bool flag)
	{
		blockLost = flag;
	}
	void SetParFlag(bool flag)
	{
		parflag = flag;
	}
	void CreateCollision2D();				//2Dあたり判定
	void Add2DRigidBody();					//2Dあたり判定追加
	void Remove2DRigidBody();				//2Dあたり判定削除
	btRigidBody *Get2DBlock()
	{
		return m_rigidBody2Dblock;
	}
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	AnimState animState;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 50;
	int parTime;
	bool parflag;
	bool blockLost;						//ブロックがあるか？
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_blockboxShape;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3Dblock;	//剛体3D。
	btRigidBody*		m_rigidBody2Dblock;	//剛体2D。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
};

