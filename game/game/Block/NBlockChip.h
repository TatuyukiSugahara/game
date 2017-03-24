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
	//座標セット
	void SetPos(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//回転セット
	void SetRot(const D3DXQUATERNION& rot)
	{
		rotation = rot;
	}
	//大きさセット
	void SetScale(const D3DXVECTOR3& scale)
	{
		this->scale = scale;
	}
	//ブロック壊すフラグセット
	void SetLost(const bool& flag)
	{
		blockLost = flag;
	}
	//パーティクルを出すかフラグ
	void SetParFlag(const bool& flag)
	{
		parFlag = flag;
	}
	//ブロックの剛体ゲット
	const btRigidBody *GetBlock() const
	{
		return rigidBodyBlock;
	}
	//あたり判定作成
	void CreateCollision();				
	//あたり判定追加
	void AddRigidBody();				
	//あたり判定削除
	void RemoveRigidBody();				
private:
	D3DXVECTOR3									position;				//座標。
	D3DXVECTOR3									scale;					//大きさ
	D3DXQUATERNION								rotation;				//回転
	static SkinModelData*						orgSkinModelData;		//オリジナルのスキンモデルデータ。
	SkinModel									skinModel;				//モデル
	SkinModelData								modelData;				//モデルデータ
	Animation*									orgAnimation;			//オリジナルのアニメーション
	Animation									animation;				//アニメーション
	CLight										light;					//ライト
	AnimState									animState;				//アニメーション用ステート
	SParicleEmitParameter						param;					//パーティクル
	typedef std::shared_ptr<CParticleEmitter>	CParticleEmitterPtr;	//パーティクルエミッターのシェアードポインタ
	std::list<CParticleEmitterPtr>				particleEmitterList;	//パーティクルリスト
	const int									MAXPAR = 50;			//パーティクル発生時間の上限
	int											parTime;				//パーティクルの時間
	bool										parFlag;				//パーティクルが出るかのフラグ
	bool										blockLost;				//ブロックがあるか？
	//bulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*							blockboxShape = NULL;	//地面のコリジョン形状。
	btRigidBody*								rigidBodyBlock = NULL;	//剛体
	btDefaultMotionState*						myMotionState = NULL;	//モーションステート
	bool										isAddCollision;			//コリジョン追加フラグ
};

