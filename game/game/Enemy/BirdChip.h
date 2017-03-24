#pragma once
#include "Particle\ParticleEmitter.h"

class CBirdChip
{
public:
	enum class BirdState
	{
		Alive,				//敵がいる
		Dead,				//敵がいない
	};
	CBirdChip();
	~CBirdChip();
	//初期化。
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	//座標を設定。
	void SetPosition(const D3DXVECTOR3& pos)
	{
		position = pos;
	}
	//状態ゲット
	const BirdState& GetState() const
	{
		return state;
	}
	//状態セット
	void SetState(const BirdState& state)
	{
		this->state = state;
	}
	//座標ゲット
	const D3DXVECTOR3& GetPos() const 
	{
		return position;
	}
private:
	BirdState									state;					//状態
	D3DXVECTOR3									position;				//座標
	D3DXVECTOR3									scale;					//大きさ
	D3DXQUATERNION								rotation;				//回転
	SkinModel									skinModel;				//モデル
	SkinModelData								modelData;				//モデルデータ
	Animation									animation;				//アニメーション
	static SkinModelData*						orgSkinModelData;		//スキンモデルデータ。
	Animation*									orgAnimation;			//オリジナルのアニメーション
	CLight										light;					//ライト
	SParicleEmitParameter						param;					//パーティクル
	typedef std::shared_ptr<CParticleEmitter>	CParticleEmitterPtr;	//パーティクルエミッターのシェアードポインタ
	std::list<CParticleEmitterPtr>				particleEmitterList;	//パーティクルリスト
	const int									MAXPAR = 50;			//パーティクル発生時間の上限
	int											parTime;				//パーティクルの時間
	bool										parFlag;				//パーティクルが出るかのフラグ
	int											count;					//死亡した後描画する時間
	std::unique_ptr<CSoundSource>				seEnemyDeath;			//死亡したSE
};

