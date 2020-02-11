#pragma once
/**
 *	\file	cPhysicsFactory.h
 *	\brief	Class header file
 *
 *	\desc	Contains the cPhysicsFactory class definition
 */

#include <physics/interfaces/iPhysicsFactory.h>

namespace DegenMyPhysicsWrapper
{
	/**
	 *	\class	cPhysicsFactory
	 *	\brief	Factory class
	 *
	 *	\desc	A factory class for creating physics objects
	 */
	class cPhysicsFactory: public DegenPhysics::iPhysicsFactory
	{
	public:
		
		/**
		 * \method    ~cPhysicsFactory
		 * \fullname  DegenMyPhysicsWrapper::cPhysicsFactory::~cPhysicsFactory
		 * \brief     dtor
		 *
		 * \access    virtual public 
		 *
		 * \desc      default dtor
		 */
		virtual ~cPhysicsFactory() = default;
		
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
		DegenPhysics::iPhysicsWorld* CreateWorld() override;
		
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
		DegenPhysics::iSphereComponent* CreateSphere(const DegenPhysics::sSphereDef& def) override;

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
		DegenPhysics::iPlaneComponent* CreatePlane(const DegenPhysics::sPlaneDef& def) override;
	};
}
