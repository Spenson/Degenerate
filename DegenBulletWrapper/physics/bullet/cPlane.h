#pragma once
/**
 * \file	cPlane.h
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class header file
 *
 * \desc	contains the cPlane wrapper class definition
 */
#include <physics/interfaces/iPlaneComponent.h>
#include "btBulletDynamicsCommon.h"

namespace DegenBulletPhysicsWrapper
{


	/**
	 * \class	cPlane
	 * \brief	Wrapper class
	 *
	 * \desc	A wrapper for a cRigidBody object containing a cPlane: iShape. Maintaining a pointer to the body to access and the shape for cleanup.
	 */
	class cPlane : public DegenPhysics::iPlaneComponent
	{
	public:
		btRigidBody* mBody;	// \desc	pointer to wrapped object to allow access
		
		/**
		 * \method		~cPlane
		 * \fullname	DegenMyPhysicsWrapper::cPlane::~cPlane
		 * \brief		dtor
		 *
		 * \access		virtual public 
		 *
		 * \desc		cleans up mBody and mShape
		 */
		virtual ~cPlane();
		
		/**
		 * \method		cPlane
		 * \fullname	DegenMyPhysicsWrapper::cPlane::cPlane
		 * \brief		ctor
		 *
		 * \access		public 
		 * \param		DegenPhysics::sPlaneDef def
		 *
		 * \desc		creates Rigid body and plane shape based off values in def
		 */
		cPlane(DegenPhysics::sPlaneDef def);

		/**
		 * \method		GetTransform
		 * \fullname	DegenMyPhysicsWrapper::cPlane::GetTransform
		 * \brief		mBody GetTransform wrapper
		 *
		 * \access		public 
		 * \return		glm::mat4 & transformOut
		 *
		 * \desc		Get the transform calculation for rendering the object
		 */
		void GetTransform(glm::mat4& transformOut) override;
		
		/**
		 * \method		ApplyForce
		 * \fullname	DegenMyPhysicsWrapper::cPlane::ApplyForce
		 * \brief		mBody ApplyForce Wrapper
		 *
		 * \access		virtual public 
		 * \returns		void
		 * \param		const glm::vec3 & force
		 *
		 * \desc		add force to the acceleration of the object
		 */
		virtual void ApplyForce(const glm::vec3& force) override;
	};
}
