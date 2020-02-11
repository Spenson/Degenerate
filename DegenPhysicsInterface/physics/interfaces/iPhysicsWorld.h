#pragma once
/**
 * \file	iPhysicsWorld.h
 * \path	D:\GDP\Degenerate\DegenPhysicsInterface\physics\interfaces
 * \brief	Interface File
 *
 * \desc	contains the iPhysicsWorld interface
 */
#include "iPhysicsComponent.h"

namespace DegenPhysics
{
		/**
		 * \class	iPhysicsWorld
		 * \brief	interface
		 *
		 * \member	iPhysicsWorld
		 *
		 * \desc	interface for physics world
		 */
	class iPhysicsWorld
	{
	public:
		/**
		 * \method		~iPhysicsWorld
		 * \fullname	DegenPhysics::iPhysicsWorld::~iPhysicsWorld
		 * \brief		dtor
		 *
		 * \access		virtual public
		 * 
		 * \desc		default
		 */
		virtual ~iPhysicsWorld() = default;

		/**
		 * \method		Update
		 * \fullname	DegenPhysics::iPhysicsWorld::Update
		 * \brief		simulate passage of time
		 *
		 * \access		virtual public 
		 * \return		void
		 * \param		float dt
		 */
		virtual void Update(float dt) = 0;
		/**
		 * \method		AddObject
		 * \fullname	DegenPhysics::iPhysicsWorld::AddObject
		 * \brief		add a component to the world
		 *
		 * \access		virtual public 
		 * \return		void
		 * \param		iPhysicsComponent * component	
		 */
		virtual void AddObject(iPhysicsComponent* component) = 0;
		/**
		 * \method		RemoveObject
		 * \fullname	DegenPhysics::iPhysicsWorld::RemoveObject
		 * \brief		remove a component from the world
		 *
		 * \access		virtual public 
		 * \return		void
		 * \param		iPhysicsComponent * component
		 */
		virtual void RemoveObject(iPhysicsComponent* component) = 0;
	};
}