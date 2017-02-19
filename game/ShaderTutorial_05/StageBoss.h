//#pragma once
//#include "lib\System.h"
//#include "Scene\Scene.h"
//#include "Stage.h"
//#include "Camera.h"
//#include "Light.h"
//#include "Player.h"
//#include "StageBack.h"
//#include "Map.h"
//#include "ShadowMap.h"
//#include "Sound\SoundSource.h"
//#include "Sun.h"
//#include "Boss.h"
//#include "BossLife.h"
//
//#define MAX_COLLISION 100
//
////今後ステージは此奴を継承する
//class CStageBoss : public CScene
//{
//public:
//	CStageBoss(){}
//	~CStageBoss()
//	{
//		for (auto& shape : m_groundShape){
//			delete shape;
//		}
//		for (auto& rb : m_rigidBody){
//			delete rb;
//		}
//		delete m_myMotionState;
//
//	}
//	void Init();
//	void Update();
//	void Render();
//	void UpdateLight();
//	void Release();
//
//	void CreateCollision();				//2Dあたり判定
//	void Add2DRigidBody(/*int arraySize*/);		//2Dあたり判定追加
//	Camera* GetCamera()
//	{
//		return&camera;
//	}
//	CLight* GetLight()
//	{
//		return &light;
//	}
//	CPlayer* GetPlayer()
//	{
//		return &player;
//	}
//	CMap* GetMap()
//	{
//		return&map;
//	}
//	CShadowMap* GetShadow()
//	{
//		return&shadow;
//	}
//	CSoundSource* GetSoundSorce()
//	{
//		return&soundsource;
//	}
//	CBoss* GetBoss()
//	{
//		return &boss;
//	}
//protected:
//	//ここからbulletPhysicsの剛体を使用するために必要な変数。
//	btCollisionShape*	m_groundShape[MAX_COLLISION];	//地面のコリジョン形状。
//	btRigidBody*		m_rigidBody[MAX_COLLISION];	//剛体。
//	btDefaultMotionState* m_myMotionState;
//	bool				m_isAdd2DCollision;
//	SCollisionInfo* collisionTable;					//コリジョンテーブル
//	int arraySize;									//サイズ
//	LPD3DXSPRITE m_pSprite;			//スプライト
//	Camera camera;				//カメラ。
//	CLight light;				//ライト
//	CPlayer player;				//プレイヤー
//	CStageBack stageback;		//ステージ背景
//	CMap map;					//マップ作製
//	CShadowMap shadow;			//影
//	CSoundSource			soundsource;
//	CSun sun;					//太陽
//	CBoss boss;					//ボス
//	CBossLife bossLife;			//ボスライフ
//};
//
//extern CStageBoss* g_stageBoss;