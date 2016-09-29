#pragma once
#include "lib\System.h"
#include "Camera.h"
#include "Light.h"
#include "LightBack.h"
#include "Player.h"
#include "Block.h"
#include "Stage.h"
#include "HatenaBox.h"
#include "Kinoko.h"
#include "NBlock.h"
#include "StageBack.h"
#include "Pipe.h"
#include "Map.h"
#include "ShadowMap.h"
#include "Goal.h"

#define MAX_COLLISION 100

//オブジェクトの詳細
struct SCollisionInfo {
	D3DXVECTOR3 pos;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 scale;
};

//今後ステージは此奴を継承する
class CStage
{
public:
	CStage(){}
	virtual ~CStage(){}
	virtual void Initialize();
	virtual void Update();
	virtual void Render();
	void UpdateLight();
	void Release();

	void CreateCollision2D();				//2Dあたり判定
	void Add2DRigidBody(int arraySize);		//2Dあたり判定追加
	Camera* GetCamera()
	{
		return& camera;
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
protected:
	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3D[MAX_COLLISION];	//剛体3D。
	btRigidBody*		m_rigidBody2D[MAX_COLLISION];	//剛体2D。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;

	Camera camera;				//カメラ。
	CLight light;				//ライト
	CLightBack lightback;		//背景ライト
	CPlayer player;				//プレイヤー
	CBlock block;				//ブロック
	CHatenaBox	hanatebox;		//はてなボックス
	CKinoko	kinoko;				//キノコ
	CNBlock	nblock;				//ノーマルブロック
	CStageBack stageback;		//ステージ背景
	CPipe pipe;					//土管
	CMap map;					//マップ作製
	CShadowMap shadow;			//影
	CGoal goal;					//ゴール
};

extern CStage g_stage;