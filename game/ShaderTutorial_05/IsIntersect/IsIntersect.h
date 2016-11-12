#pragma once
#include"..\BulletPhysics\BulletPhysics.h"
#include <vector>
class IPlayerCollisionCallback;
//あたり判定

#define PI 3.14159265358979323846f

class CIsIntersect
{
public:
	CIsIntersect();
	~CIsIntersect();
	void CollisitionInitialize(D3DXVECTOR3* m_position,float radius);
	void Intersect(
		D3DXVECTOR3* m_position, 
		D3DXVECTOR3* m_moveSpeed, 
		std::vector<IPlayerCollisionCallback*>& callbackList
	);
	D3DXVECTOR3 GetAddPos()
	{
		return addPos;
	}
	bool gethit()
	{
		return isHit;
	}
	bool GetWall()
	{
		return isWall;
	}
	bool GetGround()
	{
		return isGround;
	}
	const btCollisionObject* getCollisionObj()
	{
		return hitCollisionObject;
	}
private:
	float	m_radius;		//ラジアンの角度
	//D3DXVECTOR3 m_position;	//ポジション
	D3DXVECTOR3 m_moveSpeed;		//移動速度
	D3DXVECTOR3 addPos;				//移動した分
	D3DXVECTOR3 gravity;
	//ここからBulletPhysicsで衝突判定を行うためのメンバ変数。
	btGhostObject*		m_ghostObject;		//!<ゴースト。剛体の変わりになるもの。完全に物理挙動に任せたいものは剛体を使う。
	btSphereShape*		m_collisionShape;	//!<コリジョン形状。
	btRigidBody*			m_rigidBody;
	btDefaultMotionState*	m_myMotionState;
	bool isHit;					//天井と当たった？
	bool isWall;				//壁と当たった？
	bool isGround;				//床と当たっている？
	const btCollisionObject* hitCollisionObject;//どのコリジョンと当たった？

};