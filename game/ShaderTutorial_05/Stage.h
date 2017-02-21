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

#define MAX_COLLISION 100

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
		for (auto& shape : m_groundShape){
			delete shape;
		}
		for (auto& rb : m_rigidBody){
			delete rb;
		}
		delete m_myMotionState;
		
	}
	void Init();
	void Update();
	void Render();
	void UpdateLight();
	void Release();
	void CreateCollision();				//2Dあたり判定
	void Add2DRigidBody(/*int arraySize*/);		//2Dあたり判定追加
	void BossMusic();							//ボス戦時の音楽再生。
	void MusicStop();							//音楽ストップ。
	Camera* GetCamera()
	{
		return&camera;
	}
	CLight* GetLight()
	{
		return &light;
	}
	CLightBack* GetLightBack()
	{
		return &lightback;
	}
	CPlayer* GetPlayer()
	{
		return &player;
	}
	CKinoko* GetKinoko()
	{
		return &kinoko;
	}
	CHatenaBox* GetHatena()
	{
		return &hanatebox;
	}
	CMap* GetMap()
	{
		return&map;
	}
	CShadowMap* GetShadow()
	{
		return&shadow;
	}
	CSaboten* GetSabo()
	{
		return &sabo;
	}
	CNBlock* GetNBlock()
	{
		return &nblock;
	}
	CPipe* GetPipe()
	{
		return &pipe;
	}
	CMohurun* GetMohu()
	{
		return &mohurun;
	}
	CNoBlock* GetNoBlock()
	{
		return&noblock;
	}
	CCoinNomber* GetCoinNum()
	{
		return &coinNumber;
	}
	CSoundSource* GetSoundSorce()
	{
		return&soundsource;
	}
	CBird* GetBird()
	{
		return &bird;
	}
	CCoin* GetCoin()
	{
		return &coin;
	}
	CCoinSprite* GetCoinSprite()
	{
		return &coinsprite;
	}
	CBoss* GetBoss()
	{
		return &boss;
	}
	CBossName* GetBossName()
	{
		return &bossName;
	}
	CBossKatto* GetBossKatto()
	{
		return &bossKatto;
	}
	CBossClear* GetBossClear()
	{
		return &bossClear;
	}
protected:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody[MAX_COLLISION];	//剛体。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;
	SCollisionInfo* collisionTable;					//コリジョンテーブル
	int arraySize;									//サイズ
	bool bossmusic;					//ボス戦時の音楽フラグ。
	LPD3DXSPRITE m_pSprite;			//スプライト
	Camera camera;				//カメラ。
	CLight light;				//ライト
	CLightBack lightback;		//背景ライト
	CPlayer player;				//プレイヤー
	CHatenaBox	hanatebox;		//はてなボックス
	CKinoko	kinoko;				//キノコ
	CNBlock	nblock;				//ノーマルブロック
	CStageBack stageback;		//ステージ背景
	CPipe pipe;					//土管
	CMap map;					//マップ作製
	CShadowMap shadow;			//影
	CGoal goal;					//ゴール
	CSaboten sabo;				//サボテン
	CMohurun mohurun;			//モフルンエネミー
	CNoBlock	noblock;		//見えないブロック
	CCoin coin;					//コイン
	CGoalFlag goalflag;			//ゴールフラグ
	CCoinNomber coinNumber;		//コインナンバー
	CBird bird;					//鳥エネミー
	CRotationGimmick rotationgimmick;//回転するギミック
	CSoundSource			soundsource;
	CCoinSprite	coinsprite;
	CSun sun;					//太陽
	CBoss boss;					//ボス
	CBossLife bossLife;			//ボスライフ
	CBossName bossName;			//ボス名前
	CBossKatto bossKatto;		//ボス登場時のカットイン。
	CBossClear bossClear;		//ボス撃破時のカットイン。
};

extern CStage* g_stage;