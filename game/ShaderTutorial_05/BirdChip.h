#pragma once
#include "Particle\ParticleEmitter.h"



enum BirdState
{
	BIRDON,				//敵がいる
	BIRDOFF,				//敵がいない
};

class CBirdChip
{
public:
	CBirdChip();
	~CBirdChip();
	//初期化。
	void Init(const char* name, LPDIRECT3DDEVICE9 pd3dDevice);
	//更新。
	void Update();
	//描画。
	void Render(
		D3DXMATRIX viewMatrix,
		D3DXMATRIX projMatrix,
		bool isDrawToShadowMap);
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
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
	SkinModelData modelData;
	Animation animation;
	static SkinModelData*	orgSkinModelData;		//スキンモデルデータ。
	Animation* orgAnimation;
	CLight	light;
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parflag;
	int count;

	CSoundSource* SEenemyDeath;
};

