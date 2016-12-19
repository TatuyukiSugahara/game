#include "../tk/tkEnginePreCompile.h"
#include "Physics.h"
#include "RigidBody.h"

	CPhysicsWorld::CPhysicsWorld()
	{
		collisionConfig = NULL;
		collisionDispatcher = NULL;
		overlappingPairCache = NULL;
		constraintSolver = NULL;
		dynamicWorld = NULL;
	}


	CPhysicsWorld::~CPhysicsWorld()
	{
		delete dynamicWorld;
		delete constraintSolver;
		delete overlappingPairCache;
		delete collisionDispatcher;
		delete collisionConfig;
	}
	void CPhysicsWorld::Init()
	{
		//•¨—ƒGƒ“ƒWƒ“‚ð‰Šú‰»B
		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		collisionConfig = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		collisionDispatcher = new	btCollisionDispatcher(collisionConfig);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		overlappingPairCache = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		constraintSolver = new btSequentialImpulseConstraintSolver;

		dynamicWorld = new btDiscreteDynamicsWorld(
			collisionDispatcher,
			overlappingPairCache,
			constraintSolver,
			collisionConfig
			);

		dynamicWorld->setGravity(btVector3(0, -10, 0));
	}
	void CPhysicsWorld::Update()
	{
		dynamicWorld->stepSimulation(1.0f/60.0f);
	}
	//void CPhysicsWorld::AddRigidBody(CRigidBody* rb)
	//{
	//	dynamicWorld->addRigidBody(rb->GetBody());
	//}
	//void CPhysicsWorld::RemoveRigidBody(CRigidBody* rb)
	//{
	//	dynamicWorld->removeRigidBody(rb->GetBody());
	//}