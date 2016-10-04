#include "IsIntersect.h"
#include "IPlayerCollisionCallback.h"
#include "..\Stage.h"

//あたり判定

struct SweepResultGround : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;
	const btCollisionObject* hitCollisionObject;
	SweepResultGround()
	{
		isHit = false;
		hitPos.x = 0.0f;
		hitPos.y = 0.0f;
		hitPos.z = 0.0f;
		hitCollisionObject = NULL;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;

		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();

		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

		float d = D3DXVec3Dot(&hitPointNormal, &Up);
		if (d < 0.0f) {
			//当たってない。
			return 0.0f;
		}
		if (acosf(d) > PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;

		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.y = convexResult.m_hitPointLocal.y();
		hitPos.z = convexResult.m_hitPointLocal.z();
		hitCollisionObject = convexResult.m_hitCollisionObject;
		return 0.0f;
	}
};
//天井
struct SweepResultCeiling : public btCollisionWorld::ConvexResultCallback
{
	bool isHit;
	D3DXVECTOR3 hitPos;
	const btCollisionObject* hitCollisionObject;
	SweepResultCeiling()
	{
		isHit = false;
		hitPos.x = 0.0f;
		hitPos.y = 0.0f;
		hitPos.z = 0.0f;
		hitCollisionObject = NULL;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;

		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();

		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

		float d = D3DXVec3Dot(&hitPointNormal, &Up);
		if (d > 0.0f) {
			//当たってない。
			return 0.0f;
		}
		if (acosf(d) < PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;

		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.y = convexResult.m_hitPointLocal.y();
		hitPos.z = convexResult.m_hitPointLocal.z();
		hitCollisionObject = convexResult.m_hitCollisionObject;
		return 0.0f;
	}
};
struct SweepResultWall : public btCollisionWorld::ConvexResultCallback
{
	D3DXVECTOR3 hitNormalXZ;
	D3DXVECTOR3 hotNormal;
	bool isHit;
	D3DXVECTOR3 hitPos;
	const btCollisionObject* hitCollisionObject;
	SweepResultWall()
	{
		isHit = false;
		hitCollisionObject = NULL;
	}

	virtual	btScalar	addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject->getUserIndex() != -1) {
			//無視。
			return 0.0f;
		}
		D3DXVECTOR3 hitPointNormal;

		hitPointNormal.x = convexResult.m_hitNormalLocal.x();
		hitPointNormal.y = convexResult.m_hitNormalLocal.y();
		hitPointNormal.z = convexResult.m_hitNormalLocal.z();

		D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);

		float d = D3DXVec3Dot(&hitPointNormal, &Up);
		if (acosf(d) < PI * 0.2) {
			//ホントは地面かどうかとかの属性を見るのがベストなんだけど、今回は角度で。
			return 0.0f;
		}
		isHit = true;
		//XZ平面での法線。
		hitNormalXZ.x = hitPointNormal.x;
		hitNormalXZ.y = 0.0f;
		hitNormalXZ.z = hitPointNormal.z;

		btTransform transform = convexResult.m_hitCollisionObject->getWorldTransform();

		hitPos.x = convexResult.m_hitPointLocal.x();
		hitPos.y = convexResult.m_hitPointLocal.y();
		hitPos.z = convexResult.m_hitPointLocal.z();
		hitCollisionObject = convexResult.m_hitCollisionObject;
		return 0.0f;
	}
};

CIsIntersect::CIsIntersect()
{

}

CIsIntersect::~CIsIntersect()
{

}

void CIsIntersect::CollisitionInitialize(D3DXVECTOR3* m_position, float radius)
{
	m_moveSpeed.x = 0.0f;				//移動速度
	m_moveSpeed.y = 0.0f;
	m_moveSpeed.z = 0.0f;				//移動速度
	
	addPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	isHit = false;//天井と当たっていない
	isWall = false;//壁と当たっていない
	isGround = false;//床と当たっていない		
	m_radius = radius;						//バウンディングスフィアの半径。
	//コリジョン初期化。
	m_collisionShape = new btSphereShape(m_radius);
	float mass = 1000.0f;
	btTransform rbTransform;
	rbTransform.setIdentity();
	rbTransform.setOrigin(btVector3(m_position->x, m_position->y, m_position->z));
	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	m_myMotionState = new btDefaultMotionState(rbTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, m_myMotionState, m_collisionShape, btVector3(0, 0, 0));
	m_rigidBody = new btRigidBody(rbInfo);
	m_rigidBody->setUserIndex(0);
	//ワールドに追加。
	g_bulletPhysics.AddRigidBody(m_rigidBody);
}

void CIsIntersect::Intersect(
	D3DXVECTOR3* m_position, 
	D3DXVECTOR3* m_moveSpeed,
	std::vector<IPlayerCollisionCallback*>& callbackList)
{
	static float deltaTime = 1.0f / 60.0f;
	static D3DXVECTOR3 gravity(0.0f, -30.0f, 0.0f);
	D3DXVECTOR3 addGravity = gravity;
	addGravity *= (deltaTime);
	*m_moveSpeed += (addGravity);
	addPos = *m_moveSpeed;
	addPos *= (deltaTime);
	D3DXVECTOR3 Up(0.0f, 1.0f, 0.0f);
	//XZ平面を調べる。
	{
		int loopCount = 0;
		while (true) {
			btTransform start, end;
			start.setIdentity();
			end.setIdentity();
			start.setOrigin(btVector3(m_position->x, m_position->y, m_position->z));
			D3DXVECTOR3 newPos;
			SweepResultWall callback;
			D3DXVECTOR3 addPosXZ = addPos;
			addPosXZ.y = 0.0f;
			if (D3DXVec3Length(&addPosXZ) > 0.0001f) {
				newPos = (*m_position + addPosXZ);
				end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));
				g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
			}
			if (callback.isHit) {
				//当たった。
				//壁。
				isWall = true;
				addPos.x = callback.hitPos.x - m_position->x;
				addPos.z = callback.hitPos.z - m_position->z;

				D3DXVECTOR3 t;
				t.x = -addPos.x;
				t.y = 0.0f;
				t.z = -addPos.z;
				D3DXVec3Normalize(&t, &t);
				//半径分押し戻す。
				t *= m_radius;
				addPos += t;
				//続いて壁に沿って滑らせる。
				//滑らせる方向を計算。
				D3DXVec3Cross(&t, &callback.hitNormalXZ, &Up);
				D3DXVec3Normalize(&t, &t);
				t *= D3DXVec3Dot(&t, &addPosXZ);
				addPos += t;	//滑らせるベクトルを加算。
				for (auto p : callbackList){
					p->OnHitWall(callback.hitCollisionObject);
				}
			}
			else {
				//どことも当たらないので終わり。
				break;
			}
			loopCount++;
			if (loopCount == 5) {
				break;
			}
		}
		/*if (loopCount != 0)
		{
			m_moveSpeed->x = m_moveSpeed->x * -1.0f;
		}*/
	}
	//下方向を調べる。
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		start.setOrigin(btVector3(m_position->x, m_position->y, m_position->z));
		D3DXVECTOR3 newPos;
		SweepResultGround callback;
		if (fabsf(addPos.y) > 0.0001f) {
			newPos = *m_position;
			newPos.y += addPos.y;


			end.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));

			g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
		}
		if (callback.isHit) {
			//当たった。
			//地面。
			isGround = true;//床と当たった
			m_moveSpeed->y = 0.0f;
			D3DXVECTOR3 Circle;
			float x = 0.0f;
			float offset = 0.0f;	//押し戻す量。
			Circle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Circle = *m_position;
			Circle.y = callback.hitPos.y;//円の中心
			D3DXVECTOR3 v = Circle - callback.hitPos;
			x = D3DXVec3Length(&v);//物体の角とプレイヤーの間の横幅の距離が求まる。

			offset = sqrt(m_radius*m_radius - x*x);//yの平方根を求める。
			addPos.y = callback.hitPos.y - m_position->y;
			addPos.y += offset;
			for (auto p : callbackList){
				p->OnHitGround(callback.hitCollisionObject);
				if (!p->IsHitGround()){
					//初めてあたった
					if (p->OnHitGroundTrigger(callback.hitCollisionObject)){
						p->SetHitGround(true);
					}
				}
			}
		}
		else{
			
			for (auto p : callbackList){
				if (p->IsHitGround()){
					//あたってたので離れた
					p->OnHitGroundLeave(callback.hitCollisionObject);
					p->SetHitGround(false);
					
				}
			}
			isGround = false;//床と離れた
		}
	}
	//上方向を調べる。
	{
		btTransform start, end;
		start.setIdentity();
		end.setIdentity();
		btVector3 btStart = btVector3(m_position->x, m_position->y + 1.0f, m_position->z);
		start.setOrigin(btStart);
		
		SweepResultCeiling callback;
		if (fabsf(addPos.y) > 0.0001f) {
			end.setOrigin(btVector3(btStart.x(), btStart.y() + addPos.y, btStart.z()));

			g_bulletPhysics.ConvexSweepTest(m_collisionShape, start, end, callback);
		}
		if (callback.isHit) {
			//当たった。
			//天井。
			isHit = true;
			hitCollisionObject = callback.hitCollisionObject;
			m_moveSpeed->y =0.0f;
			D3DXVECTOR3 Circle;
			float x = 0.0f;
			float offset = 0.0f;	//押し戻す量。
			Circle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			Circle = D3DXVECTOR3(btStart.x(), btStart.y(), btStart.z());
			Circle.y = callback.hitPos.y;//円の中心
			D3DXVECTOR3 v = callback.hitPos - Circle;
			x = D3DXVec3Length(&v);//物体の角とプレイヤーの間の横幅の距離が求まる。

			offset = sqrt(m_radius*m_radius - x*x);//yの平方根を求める。
			addPos.y = callback.hitPos.y - btStart.y();
			addPos.y -= offset;

			for (auto p : callbackList){
				p->OnHitCeiling(callback.hitCollisionObject);
				if (!p->IsHitCeiling()){
					//初めてあたった
					if (p->OnHitCeilingTrigger(callback.hitCollisionObject)){
						p->SetHitCeiling(true);
					}
				}
			}
		}
		else{

			for (auto p : callbackList){
				if (p->IsHitCeiling()){
					//あたってたので離れた
					p->OnHitCeilingLeave(callback.hitCollisionObject);
					p->SetHitCeiling(false);
					
				}
			}
			isHit = false;
		}
	}

	*m_position += addPos;

	const btVector3& rPos = m_rigidBody->getWorldTransform().getOrigin();

	m_rigidBody->getWorldTransform().setOrigin(btVector3(m_position->x, m_position->y, m_position->z));
}