#pragma once
#include "Turn.h"
#include "Particle\ParticleEmitter.h"
#include "character\CharacterController.h"

class CBoss {
public:
	enum class BossState{
		Move,			//移動
		Falter,			//怯む
		Dead,			//死ぬ
	};
	//コンストラクタ
	CBoss();
	//デストラクタ
	~CBoss();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		const D3DXMATRIX viewMatrix,
		const D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void Move();
	void Falter();
	void Dead();
	//パーティクル
	void Particle();
	//ライフゲット
	const int& GetLife() const 
	{
		return life;
	}
	//行動始めるフラグ関数
	bool Start();
	//ポジションゲット
	const D3DXVECTOR3& GetPos()const 
	{
		return position;
	}
	void SetCameraFlag(const bool& flag)
	{
		cameraflag = flag;
	}
	const bool& GetCameraFlag() const 
	{
		return cameraflag;
	}
	const BossState& GetState() const
	{
		return state;
	}
private:
	D3DXVECTOR3				position;		//座標。
	D3DXVECTOR3				scale;			//スケール
	D3DXVECTOR3				movespeed;		//移動速度
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	CTurn					turn;			//ターンクラス
	float					currentAngleY;
	float					targetAngleY;
	int life;
	bool cameraflag = false;
	BossState state;
	SParicleEmitParameter param;
	typedef std::shared_ptr<CParticleEmitter> CParticleEmitterPtr;
	std::list<CParticleEmitterPtr> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;

	CCharacterController characterController;				//キャラクターコントローラー
};