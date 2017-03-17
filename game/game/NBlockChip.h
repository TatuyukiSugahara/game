#pragma once
#include "Particle\ParticleEmitter.h"

//見えるブロック

class CNBlockChip
{
public:
	enum class AnimState
	{
		On,				//アニメーションする
		Off,			//アニメーションしない
	};
	CNBlockChip();
	~CNBlockChip();
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
	void SetScale(const D3DXVECTOR3& scale)
	{
		this->scale = scale;
	}
	void SetLost(const bool& flag)
	{
		blockLost = flag;
	}
	void SetParFlag(const bool& flag)
	{
		parflag = flag;
	}
	void CreateCollision2D();				//2Dあたり判定
	void Add2DRigidBody();					//2Dあたり判定追加
	void Remove2DRigidBody();				//2Dあたり判定削除
	const btRigidBody *Get2DBlock() const
	{
		return m_rigidBody2Dblock;
	}
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXQUATERNION			rotation;
	static SkinModelData*	orgSkinModelData;		//スキンモデルデータ。
	SkinModel skinModel;
	SkinModelData modelData;
	Animation* orgAnimation;
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
	btCollisionShape*	m_blockboxShape = NULL;	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3Dblock = NULL;	//剛体3D。
	btRigidBody*		m_rigidBody2Dblock = NULL;	//剛体2D。
	btDefaultMotionState* m_myMotionState = NULL;
	bool				m_isAdd2DCollision;
};

