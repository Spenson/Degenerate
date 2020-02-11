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

namespace DegenMyPhysicsWrapper
{
	cPhysicsWorld::~cPhysicsWorld()
	{
		delete mWorld;
	}

	cPhysicsWorld::cPhysicsWorld()
	{
		mWorld = new MyPhysics::cWorld();
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
		mWorld->Update(dt);
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
		switch (component->GetComponentType())
		{
			case DegenPhysics::eComponentType::plane:
				mWorld->AddRigidBody(dynamic_cast<cPlane*>(component)->mBody);
				break;
			case DegenPhysics::eComponentType::sphere:
				mWorld->AddRigidBody(dynamic_cast<cSphere*>(component)->mBody);
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
		switch (component->GetComponentType())
		{
			case DegenPhysics::eComponentType::plane:
				mWorld->RemoveRigidBody(dynamic_cast<cPlane*>(component)->mBody);
				break;
			case DegenPhysics::eComponentType::sphere:
				mWorld->RemoveRigidBody(dynamic_cast<cSphere*>(component)->mBody);
				break;
		}
	}

}
