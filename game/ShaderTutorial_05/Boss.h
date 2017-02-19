#pragma once
#include "Turn.h"
#include "Particle\ParticleEmitter.h"
#include "character\CharacterController.h"

enum BossState{
	BossMove,			//移動
	BossFalter,			//怯む
	BossDead,			//死ぬ
};

class CBoss {
public:
	//コンストラクタ
	CBoss();
	//デストラクタ
	~CBoss();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
	void Move();
	void Falter();
	void Dead();
	//パーティクル
	void Particle();
	//ライフゲット
	int GetLife()
	{
		return life;
	}
	//行動始めるフラグ関数
	bool Start();
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
	void SetCameraFlag(bool flag)
	{
		cameraflag = flag;
	}
	BossState GetState()
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
	int life = 5;
	bool cameraflag = false;
	BossState state;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;

	CCharacterController characterController;				//キャラクターコントローラー
};