#pragma once
#include "Particle\ParticleEmitter.h"
#include "character\CharacterController.h"

//マップチップの配置情報。
struct SMohurunChipLocInfo {
	const char* modelName;		//モデル。
	D3DXVECTOR3	pos;			//座標。
	D3DXQUATERNION	rotation;		//回転。
};

enum State
{
	on,				//敵がいる
	off				//敵がいない
};

class CMohurunChip
{
public:
	CMohurunChip();
	~CMohurunChip();
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

	D3DXVECTOR3				gravity = D3DXVECTOR3(0.0f, -0.98f, 0.0f);
	D3DXVECTOR3				position;		//座標。。
	D3DXVECTOR3				scale;			//大きさ
	D3DXVECTOR3				movespeed;		//移動速度
	D3DXMATRIX				mWorld;			//ワールド行列。
	D3DXQUATERNION			rotation;
	SkinModel skinmodel;
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
	bool parflag;
	int count;

	CSoundSource* SEenemyDeath;
};

