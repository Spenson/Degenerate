/**
 * \file	cPhysicsWorld.cpp
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class Implementation File
 *
 * \desc	contains the implementation of the cPhysicsWorld class
 */

#include "cPhysicsWorld.h"
#include "cPlane.h"
#include "cSphere.h"

namespace DegenBulletPhysicsWrapper
{
	cPhysicsWorld::~cPhysicsWorld()
	{
		//This is a toggle comment add/remove first forward slash to comment/uncomment block
		//* James Order
		delete mCollisionConfiguration;
		delete mDispatcher;
		delete mOverlappingPairCache;
		delete mSolver;
		delete mWorld;
		//*/

		/*	to add later
			if(mCollisionListener)
			{
				delete mCollisionListener;
				mCollisionListener = nullptr;
			}
		*/


		/* Bullet Order			
		//delete dynamics world
		delete mWorld;

		//delete solver
		delete mSolver;

		//delete broadphase
		delete mOverlappingPairCache;

		//delete dispatcher
		delete mDispatcher;

		delete mCollisionConfiguration;
		*/
	}

	cPhysicsWorld::cPhysicsWorld()
	{
		///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
		mCollisionConfiguration = new btDefaultCollisionConfiguration();

		///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
		mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

		///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
		mOverlappingPairCache = new btDbvtBroadphase();

		///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
		mSolver = new btSequentialImpulseConstraintSolver;

		mWorld = new btDiscreteDynamicsWorld(mDispatcher, mOverlappingPairCache, mSolver, mCollisionConfiguration);

		mWorld->setGravity(btVector3(0, -5, 0));
	}

	/**
	 * \method		Update
	 * \fullname	DegenMyPhysicsWrapper::cPhysicsWorld::Update
	 * \brief		cWorld Update wrapper
	 *
	 * \access		public
	 * \returns		void
	 * \param		float dt : delta-time/timestep between updates
	 *
	 * \desc		calls mWorld's Update method passing dt
	 */
	void cPhysicsWorld::Update(float dt)
	{
		mWorld->stepSimulation(dt, 10);
		/*// todo collision stuff
		if (mCollisionListener)
		{
			
		}
		//*/
	}

	/**
	 * \method		AddObject
	 * \fullname	DegenMyPhysicsWrapper::cPhysicsWorld::AddObject
	 * \brief		cWorld AddRigidBody wrapper
	 *
	 * \access		public
	 * \returns		void
	 * \param		DegenPhysics::iPhysicsComponent * component : physics object to add to mWorld
	 *
	 * \desc		Adds object to the physics world
	 */
	void cPhysicsWorld::AddObject(DegenPhysics::iPhysicsComponent* component)
	{
		if (!component)
		{
			return;
		}


		switch (component->GetComponentType())
		{
			case DegenPhysics::eComponentType::plane:
				mWorld->addRigidBody(dynamic_cast<cPlane*>(component)->mBody);
				break;
			case DegenPhysics::eComponentType::sphere:
				mWorld->addRigidBody(dynamic_cast<cSphere*>(component)->mBody);
				break;
		}

	}

	/**
	 * \method		RemoveObject
	 * \fullname	DegenMyPhysicsWrapper::cPhysicsWorld::RemoveObject
	 * \brief		cWorld RemoveRigidBody wrapper
	 *
	 * \access		public
	 * \returns		void
	 * \param		DegenPhysics::iPhysicsComponent * component
	 *
	 * \desc		removes object from the physics world
	 */
	void cPhysicsWorld::RemoveObject(DegenPhysics::iPhysicsComponent* component)
	{
		if (!component)
		{
			return;
		}


		switch (component->GetComponentType())
		{
			case DegenPhysics::eComponentType::plane:
				mWorld->removeRigidBody(dynamic_cast<cPlane*>(component)->mBody);
				break;
			case DegenPhysics::eComponentType::sphere:
				mWorld->removeRigidBody(dynamic_cast<cSphere*>(component)->mBody);
				break;
		}
	}

}
