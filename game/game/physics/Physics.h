#pragma once
#include "..\..\bulletPhysics\src\btBulletDynamicsCommon.h"
#include"..\BulletCollision\CollisionDispatch\btGhostObject.h"

	class CRigidBody;

	class CPhysicsWorld
	{
		btDefaultCollisionConfiguration*		collisionConfig;
		btCollisionDispatcher*					collisionDispatcher;	//!<衝突解決処理。
		btBroadphaseInterface*					overlappingPairCache;	//!<ブロードフェーズ。衝突判定の枝切り。
		btSequentialImpulseConstraintSolver*	constraintSolver;		//!<コンストレイントソルバー。拘束条件の解決処理。
		btDiscreteDynamicsWorld*				dynamicWorld;			//!<ワールド。
	public:
		CPhysicsWorld();
		~CPhysicsWorld();
		void Init();
		void Update() ;
		/*!
		* @brief	ダイナミックワールドを取得。
		*/
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return dynamicWorld;
		}
		/*void AddRigidBody(CRigidBody* rb);
		void RemoveRigidBody(CRigidBody* rb);*/
		/*!
		* @brief	剛体を物理ワールドに追加。
		*@param[in]	body		剛体
		*/
		void AddRigidBody(btRigidBody* body)
		{
			dynamicWorld->addRigidBody(body);
		}
		/*!
		* @brief	剛体を物理ワールドから削除。
		*@param[in]	body		剛体
		*/
		void RemoveRigidBody(btRigidBody* body)
		{
			if (body){
				dynamicWorld->removeRigidBody(body);
			}
		}
		void ConvexSweepTest(
			const btConvexShape* castShape,
			const btTransform& convexFromWorld,
			const btTransform& convexToWorld,
			btCollisionWorld::ConvexResultCallback& resultCallback,
			btScalar allowedCcdPenetration = 0.0f
			)
		{
			dynamicWorld->convexSweepTest(castShape, convexFromWorld, convexToWorld, resultCallback, allowedCcdPenetration);
		}
	};