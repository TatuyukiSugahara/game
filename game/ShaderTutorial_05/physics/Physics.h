#pragma once
#include "..\..\bulletPhysics\src\btBulletDynamicsCommon.h"
#include"..\BulletCollision\CollisionDispatch\btGhostObject.h"

	class CRigidBody;

	class CPhysicsWorld
	{
		btDefaultCollisionConfiguration*		collisionConfig;
		btCollisionDispatcher*					collisionDispatcher;	//!<�Փˉ��������B
		btBroadphaseInterface*					overlappingPairCache;	//!<�u���[�h�t�F�[�Y�B�Փ˔���̎}�؂�B
		btSequentialImpulseConstraintSolver*	constraintSolver;		//!<�R���X�g���C���g�\���o�[�B�S�������̉��������B
		btDiscreteDynamicsWorld*				dynamicWorld;			//!<���[���h�B
	public:
		CPhysicsWorld();
		~CPhysicsWorld();
		void Init();
		void Update() ;
		/*!
		* @brief	�_�C�i�~�b�N���[���h���擾�B
		*/
		btDiscreteDynamicsWorld* GetDynamicWorld()
		{
			return dynamicWorld;
		}
		/*void AddRigidBody(CRigidBody* rb);
		void RemoveRigidBody(CRigidBody* rb);*/
		/*!
		* @brief	���̂𕨗����[���h�ɒǉ��B
		*@param[in]	body		����
		*/
		void AddRigidBody(btRigidBody* body)
		{
			dynamicWorld->addRigidBody(body);
		}
		/*!
		* @brief	���̂𕨗����[���h����폜�B
		*@param[in]	body		����
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