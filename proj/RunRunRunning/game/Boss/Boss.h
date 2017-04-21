#pragma once
#include "Frame\Turn.h"
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
	//移動
	void Move();
	//怯む
	void Falter();
	//死亡
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
	//ボス用カメラのフラグセット
	void SetCameraFlag(const bool& flag)
	{
		cameraFlag = flag;
	}
	//ボス用カメラのゲット
	const bool& GetCameraFlag() const 
	{
		return cameraFlag;
	}
	//状態ゲット
	const BossState& GetState() const
	{
		return state;
	}
private:
	D3DXVECTOR3									position;				//座標。
	D3DXVECTOR3									scale;					//スケール
	D3DXVECTOR3									moveSpeed;				//移動速度
	D3DXQUATERNION								rotation;				//回転
	SkinModel									skinModel;				//モデル
	SkinModelData								modelData;				//モデルデータ
	Animation									animation;				//アニメーション
	CLight										light;					//ライト
	CTurn										turn;					//ターンクラス
	CCharacterController						characterController;	//キャラクターコントローラー
	BossState									state;					//状態
	SParicleEmitParameter						param;					//パーティクル
	typedef std::shared_ptr<CParticleEmitter>	CParticleEmitterPtr;	//パーティクルエミッターのシェアードポインタ
	std::list<CParticleEmitterPtr>				particleEmitterList;	//パーティクルリスト
	const int									MAXPAR = 50;			//パーティクル発生時間の上限
	int											parTime;				//パーティクルの時間
	bool										parFlag;				//パーティクルが出るかのフラグ
	float										currentAngleY;			//現在のアングル
	float										targetAngleY;			//向きたいアングル
	int											life;					//ライフ
	bool										cameraFlag = false;		//ボス用カメラのフラグ

	
};