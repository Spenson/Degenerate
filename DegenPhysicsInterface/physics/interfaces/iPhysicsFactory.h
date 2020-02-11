#pragma once
/**
 * \file	iPhysicsFactory.h
 * \path	D:\GDP\Degenerate\DegenPhysicsInterface\physics\interfaces
 * \brief	Interface File
 *
 * \desc	contains the iPhysicsFactory interface
 */
#include "iSphereComponent.h"
#include "iPlaneComponent.h"
#include "iPhysicsWorld.h"

namespace DegenPhysics
{
	/**
	 * \class	iPhysicsFactory
	 * \brief	factory interface
	 *
	 * \desc	creates objects
	 */
	class iPhysicsFactory
	{
	public:
		/**
		 * \method		~iPhysicsFactory
		 * \fullname	DegenPhysics::iPhysicsFactory::~iPhysicsFactory
		 * \brief		dtor
		 *
		 * \access		virtual public
		 *
		 * \desc		default
		 */
		virtual ~iPhysicsFactory() {}
		/**
		 * \method		CreateWorld
		 * \fullname	DegenPhysics::iPhysicsFactory::CreateWorld
		 * \brief		Creator
		 *
		 * \access		virtual public
		 * \return		DegenPhysics::iPhysicsWorld*
		 *
		 * \desc		creates and returns a physics world
		 */
		virtual iPhysicsWorld* CreateWorld() = 0;
		// components
		/**
		 * \method		CreateSphere
		 * \fullname	DegenPhysics::iPhysicsFactory::CreateSphere
		 * \brief		Creator
		 *
		 * \access		virtual public
		 * \return		DegenPhysics::iSphereComponent*
		 * \param		const sSphereDef & def
		 *
		 * \desc		creates and returns a physics sphere
		 */
		virtual iSphereComponent* CreateSphere(const sSphereDef& def) = 0;
		/**
		 * \method		CreatePlane
		 * \fullname	DegenPhysics::iPhysicsFactory::CreatePlane
		 * \brief		Creator
		 *
		 * \access		virtual public
		 * \return		DegenPhysics::iPlaneComponent*
		 * \param		const sPlaneDef & def
		 *
		 * \desc		creates and returns a physics plane
		 */
		virtual iPlaneComponent* CreatePlane(const sPlaneDef& def) = 0;
	};
}