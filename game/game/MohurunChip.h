#pragma once
#include "Particle\ParticleEmitter.h"
#include "character\CharacterController.h"

class CMohurunChip
{
public:
	enum class MohurunState
	{
		Alive,				//敵がいる
		Dead				//敵がいない
	};

	CMohurunChip();
	~CMohurunChip();
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
	const MohurunState& GetState() const
	{
		return state;
	}
	void SetState(const MohurunState& state)
	{
		this->state = state;
	}
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
private:
	MohurunState state;
	D3DXVECTOR3				gravity = D3DXVECTOR3(0.0f, -0.98f, 0.0f);
	D3DXVECTOR3				position;		//座標
	D3DXVECTOR3				scale;			//大きさ
	D3DXVECTOR3				movespeed;		//移動速度
	D3DXQUATERNION			rotation;
	SkinModel skinModel;
	static SkinModelData*	orgSkinModelData;		//スキンモデルデータ。
	SkinModelData modelData;
	Animation animation;
	Animation* orgAnimation;
	CLight	light;
	CCharacterController characterController;				//キャラクターコントローラー
	SParicleEmitParameter param;
	std::list<CParticleEmitter*> particleEmitterList;
	const int MAXPAR = 100;
	int parTime;
	bool parFlag;
	int count;
	std::unique_ptr<CSoundSource> seEnemyDeath;
};

