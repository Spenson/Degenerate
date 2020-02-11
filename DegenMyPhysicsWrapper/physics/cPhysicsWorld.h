#pragma once

/**
 * \file	cPhysicsWorld.h
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class header file
 *
 * \desc	Contains the cPhysicsWorld class definition
 */

#include <physics/interfaces/iPhysicsWorld.h>
#include <physics/my_physics.h>

namespace DegenMyPhysicsWrapper
{
	/**
	 * \class	cPhysicsWorld
	 * \brief	Wrapper class
	 *
	 * \desc	A wrapper for a cWorld object. Maintaining a pointer to the world to access
	 */
	class cPhysicsWorld : public DegenPhysics::iPhysicsWorld
	{
	public:
		MyPhysics::cWorld* mWorld;	// \desc pointer to custom physics world object

		/**
		 * \method		~cPhysicsWorld
		 * \fullname	DegenMyPhysicsWrapper::cPhysicsWorld::~cPhysicsWorld
		 * \brief		dtor
		 *
		 * \access		virtual public 
		 *
		 * \desc		cleans up mWorld
		 */
		virtual ~cPhysicsWorld();

		/**
		 * \method		cPhysicsWorld
		 * \fullname	DegenMyPhysicsWrapper::cPhysicsWorld::cPhysicsWorld
		 * \brief		ctor
		 *
		 * \access		public
		 * 
		 * \desc		initialize mWorld
		 */
		cPhysicsWorld();

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
		void Update(float dt) override;
		
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
		void AddObject(DegenPhysics::iPhysicsComponent* component) override;
		
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
		void RemoveObject(DegenPhysics::iPhysicsComponent* component) override;
	};
}
