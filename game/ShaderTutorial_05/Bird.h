#pragma once
#include "Particle\ParticleEmitter.h"
enum BirdState
{
	BIRDON,				//敵がいる
	BIRDOFF,				//敵がいない
};

class CBird
{
public:
	CBird();
	~CBird();
	//初期化。
	void Init();
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix);
	//座標を設定。
	void SetPosition(D3DXVECTOR3 pos)
	{
		position = pos;
	}
	BirdState GetState()
	{
		return state;
	}
	void SetState(BirdState state)
	{
		this->state = state;
	}
	D3DXVECTOR3 GetPos()
	{
		return position;
	}
private:
	BirdState state;

	D3DXVECTOR3				position;		//座標。。
	D3DXVECTOR3				scale;			//大きさ
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXMATRIX				mRotation;		//回転行列。
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	CLight	light;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;
	int count;
};

