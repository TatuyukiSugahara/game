#pragma once
#include "Particle\ParticleEmitter.h"
enum State
{
	on,				//敵がいる
	off				//敵がいない
};

class CMohurun
{
public:
	CMohurun();
	~CMohurun();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render();
	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	State GetState()
	{
		return state;
	}
	void SetState(State state)
	{
		this->state = state;
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
private:
	State state;

	D3DXVECTOR3				position;		//座標。。
	D3DXVECTOR3				scale;			//大きさ
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	CParticleEmitter particleEmitter;		//パーティクルエミッター
	SParicleEmitParameter param;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;		
	int count;
};

