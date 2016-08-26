#pragma once
#include "lib\System.h"

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
	virtual void Draw();

	void CreateCollision2D();
	void Add2DRigidBody(int arraySize);

protected:


	bool				isButtomTriger;
	bool				isDied;

	//ここからbulletPhysicsの剛体を使用するために必要な変数。
	btCollisionShape*	m_groundShape[MAX_COLLISION];	//地面のコリジョン形状。
	btRigidBody*		m_rigidBody3D[MAX_COLLISION];	//剛体3D。
	btRigidBody*		m_rigidBody2D[MAX_COLLISION];	//剛体2D。
	btDefaultMotionState* m_myMotionState;
	bool				m_isAdd2DCollision;

};
