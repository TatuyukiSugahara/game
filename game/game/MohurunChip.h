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
	//モフルンのステートゲット
	const MohurunState& GetState() const
	{
		return state;
	}
	//ステートセット
	void SetState(const MohurunState& state)
	{
		this->state = state;
	}
	//座標ゲット
	const D3DXVECTOR3& GetPos() const
	{
		return position;
	}
private:
	MohurunState 					state;					//ステート
	D3DXVECTOR3						position;				//座標
	D3DXVECTOR3						scale;					//大きさ
	D3DXVECTOR3						moveSpeed;				//移動速度
	D3DXQUATERNION					rotation;				//回転
	SkinModel						skinModel;				//モデル
	static SkinModelData*			orgSkinModelData;		//スキンモデルデータ。
	SkinModelData					modelData;				//モデルデータ
	Animation						animation;				//アニメーション
	Animation*						orgAnimation;			//オリジナルのアニメーション
	CLight							light;					//ライト
	CCharacterController			characterController;	//キャラクターコントローラー
	SParicleEmitParameter			param;					//パーティクル
	std::list<CParticleEmitter*>	particleEmitterList;	//パーティクルリスト
	const int						MAXPAR = 50;			//パーティクル発生時間の上限
	int								parTime;				//パーティクルの時間
	bool							parFlag;				//パーティクルが出るかのフラグ
	int								count;					//倒した後数秒表示させるための時間
	std::unique_ptr<CSoundSource>	seEnemyDeath;			//死亡した時のSE
};

