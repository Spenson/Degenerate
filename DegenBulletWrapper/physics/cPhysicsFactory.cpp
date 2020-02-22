/**
 * \file	cPhysicsFactory.cpp
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class Implementation File
 *
 * \desc	contains the implementation of the cPhysicsFactory class
 */

#include "cPhysicsFactory.h"
#include "cPhysicsWorld.h"
#include "cSphere.h"
#include "cPlane.h"

namespace DegenBulletPhysicsWrapper
{
	/**
	 * \method    CreateWorld
	 * \fullname  DegenMyPhysicsWrapper::cPhysicsFactory::CreateWorld
	 * \brief     Factory create method
	 *
	 * \access    public
	 * \returns   DegenPhysics::iPhysicsWorld*
	 *
	 * \desc      Override iPhysicsFactory method. Creates physics world and returns ptr
	 */
	DegenPhysics::iPhysicsWorld* cPhysicsFactory::CreateWorld()
	{
		return new cPhysicsWorld();
	}

	/**
	 * \method    CreateSphere
	 * \fullname  DegenMyPhysicsWrapper::cPhysicsFactory::CreateSphere
	 * \brief     Factory create method
	 *
	 * \access    public
	 * \returns   DegenPhysics::iSphereComponent*
	 * \param     const DegenPhysics::sSphereDef & def
	 *
	 * \desc      Override iPhysicsFactory method. Creates sphere based off def and returns ptr
	 */
	DegenPhysics::iSphereComponent* cPhysicsFactory::CreateSphere(const DegenPhysics::sSphereDef& def)
	{
		return new cSphere(def);
	}

	/**
	 * \method    CreatePlane
	 * \fullname  DegenMyPhysicsWrapper::cPhysicsFactory::CreatePlane
	 * \brief     Factory create method
	 *
	 * \access    public
	 * \returns   DegenPhysics::iPlaneComponent*
	 * \param     const DegenPhysics::sPlaneDef & def
	 *
	 * \desc      Override iPhysicsFactory method. Creates plane based off def and returns ptr
	 */
	DegenPhysics::iPlaneComponent* cPhysicsFactory::CreatePlane(const DegenPhysics::sPlaneDef& def)
	{
		return new cPlane(def);
	}

}
