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
	const BirdState& GetState() const
	{
		return state;
	}
	void SetState(const BirdState& state)
	{
		this->state = state;
	}
	const D3DXVECTOR3& GetPos() const 
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

	std::unique_ptr<CSoundSource> SEenemyDeath;
};

