#pragma once
#include "lib\System.h"
#include "Scene\Scene.h"
#include "Camera.h"
#include "Light.h"
#include "LightBack.h"
#include "Player.h"
#include "Stage.h"
#include "HatenaBox.h"
#include "Kinoko.h"
#include "NBlock.h"
#include "StageBack.h"
#include "Pipe.h"
#include "Map.h"
#include "ShadowMap.h"
#include "Goal.h"
#include "Saboten.h"
#include "Mohurun.h"
#include "Sound\SoundSource.h"
#include "NoBlock.h"
#include "Coin.h"
#include "GoalFlag.h"
#include "CoinNomber.h"
#include "Bird.h"
#include "RotationGimmick.h"
#include "CoinSprite.h"
#include "Sun.h"
#include "Boss.h"
#include "BossLife.h"
#include "BossName.h"
#include "BossKatto.h"
#include "BossClear.h"
#include "SkyCamera.h"
#include "Kame.h"

//オブジェクトの詳細
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

//今後ステージは此奴を継承する
class CStage : public CScene
{
public:
	CStage(){}
	~CStage()
	{
		for (auto& shape : groundShape){
			delete shape;
		}
		for (auto& rb : rigidBody){
			delete rb;
		}
		delete myMotionState;
		
	}
	void Init();								//初期化
	void Update();								//更新
	void Render();								//描画
	void UpdateLight();							//ライト更新
	void Release();								//リリース
	void CreateCollision();						//あたり判定
	void AddRigidBody();						//あたり判定追加
	void BossMusic();							//ボス戦時の音楽再生。
	void MusicStop();							//音楽ストップ。
	void StageChange();							//デバッグ用ステージ変更。
	void StageInit();							//通常ステージの初期化
	void StageBossInit();						//ボスステージの初期化
	void StageUpdate();							//通常ステージのアップデート
	void StageBossUpdate();						//ボスステージのアップデート
	void StageRender();							//通常ステージの描画
	void StageBossRender();						//ボスステージの描画
	//カメラをゲット。
	Camera* GetCamera()
	{
		return&camera;
	}
	//ライトをゲット。
	CLight* GetLight()
	{
		return &light;
	}
	//背景用のライトをゲット。
	CLightBack* GetLightBack()
	{
		return &lightback;
	}
	//プレイヤーをゲット。
	CPlayer* GetPlayer()
	{
		return &player;
	}
	//キノコをゲット。
	CKinoko* GetKinoko()
	{
		return &kinoko;
	}
	//はてなボックスをゲット。
	CHatenaBox* GetHatena()
	{
		return &hanatebox;
	}
	//マップをゲット
	CMap* GetMap()
	{
		return&map;
	}
	//影をゲット。
	CShadowMap* GetShadow()
	{
		return&shadow;
	}
	//サボテンをゲット。
	CSaboten* GetSabo()
	{
		return &sabo;
	}
	//ノーマルブロックをゲット。
	CNBlock* GetNBlock()
	{
		return &nblock;
	}
	//土管をゲット。
	CPipe* GetPipe()
	{
		return &pipe;
	}
	//敵(もふるん)をげっと。
	CMohurun* GetMohu()
	{
		return &mohurun;
	}
	//見えないブロックをゲット。
	CNoBlock* GetNoBlock()
	{
		return&noblock;
	}
	//コインのナンバーをゲット。
	CCoinNomber* GetCoinNum()
	{
		return &coinNumber;
	}
	//サウンドソースをゲット。
	CSoundSource* GetSoundSorce()
	{
		return&soundsource;
	}
	//敵(とり)をゲット。
	CBird* GetBird()
	{
		return &bird;
	}
	//コインをゲット。
	CCoin* GetCoin()
	{
		return &coin;
	}
	//取得したコイン用のコインをゲット。
	CCoinSprite* GetCoinSprite()
	{
		return &coinsprite;
	}
	//ボスをゲット。
	CBoss* GetBoss()
	{
		return &boss;
	}
	//ボスの名前をゲット。
	CBossName* GetBossName()
	{
		return &bossName;
	}
	//ボス戦時のカットインをゲット。
	CBossKatto* GetBossKatto()
	{
		return &bossKatto;
	}
	//ボスを撃破した時のカットインをゲット。
	CBossClear* GetBossClear()
	{
		return &bossClear;
	}
	//コンストがいる場合の亀をゲット
	const CKame* GetKame() const
	{
		return &kame;
	}
	//亀をゲット
	CKame* GetKame()
	{
		return &kame;
	}
protected:
	//bulletPhysicsの剛体を使用するために必要な変数。
	static const int MaxCollision = 100;										//コリジョンの最大数
	btCollisionShape*				groundShape[MaxCollision];	//地面のコリジョン形状。
	btRigidBody*					rigidBody[MaxCollision];	//剛体。
	btDefaultMotionState*			myMotionState;				//モーションステート
	bool							isAddCollision;				//コリジョン追加フラグ
	SCollisionInfo*					collisionTable;				//コリジョンテーブル
	int								arraySize;					//サイズ
	bool							bossmusic;					//ボス戦時の音楽フラグ。
	LPD3DXSPRITE					sprite;						//スプライト
	Camera							camera;						//カメラ。
	CSkyCamera						skycamera;					//空用カメラ
	CLight							light;						//ライト
	CLightBack						lightback;					//背景ライト
	CPlayer							player;						//プレイヤー
	CHatenaBox						hanatebox;					//はてなボックス
	CKinoko							kinoko;						//キノコ
	CNBlock							nblock;						//ノーマルブロック
	CStageBack						stageback;					//ステージ背景
	CPipe							pipe;						//土管
	CMap							map;						//マップ作製
	CShadowMap						shadow;						//影
	CGoal							goal;						//ゴール
	CSaboten						sabo;						//サボテン
	CMohurun						mohurun;					//モフルンエネミー
	CNoBlock						noblock;					//見えないブロック
	CCoin							coin;						//コイン
	CGoalFlag						goalflag;					//ゴールフラグ
	CCoinNomber						coinNumber;					//コインナンバー
	CBird							bird;						//鳥エネミー
	CRotationGimmick				rotationgimmick;			//回転するギミック
	CSoundSource					soundsource;				//サウンドソース
	CCoinSprite						coinsprite;					//コインを取得した用のコイン
	CSun							sun;						//太陽
	CBoss							boss;						//ボス
	CBossLife						bossLife;					//ボスライフ
	CBossName						bossName;					//ボス名前
	CBossKatto						bossKatto;					//ボス登場時のカットイン。
	CBossClear						bossClear;					//ボス撃破時のカットイン。
	CKame							kame;						//亀
};

extern CStage* g_stage;