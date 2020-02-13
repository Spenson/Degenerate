/**
 * \file	cSphere.cpp
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class Implementation File
 *
 * \desc	contains the implementation of cSphere class
 */

#include "cSphere.h"

namespace DegenMyPhysicsWrapper
{
	/**
	 * \method		~cSphere
	 * \fullname	DegenMyPhysicsWrapper::cSphere::~cSphere
	 * \brief		dtor
	 *
	 * \access		virtual public
	 *
	 * \desc		cleans up mBody and mShape
	 */
	cSphere::~cSphere()
	{
		delete mBody;
		delete mShape;
	}

	/**
	 * \method		cSphere
	 * \fullname	DegenMyPhysicsWrapper::cSphere::cSphere
	 * \brief		ctor
	 *
	 * \access		public
	 * \param		DegenPhysics::sSphereDef def
	 *
	 * \desc		creates Rigid body and sphere shape based off values in def
	 */
	cSphere::cSphere(DegenPhysics::sSphereDef def)
	{
		MyPhysics::sRigidBodyDef rigiddef;
		rigiddef.Position = def.Position;
		rigiddef.Acceleration = def.Acceleration;
		rigiddef.Mass = def.Radius;
		rigiddef.Velocity = def.Velocity;

		mShape = new MyPhysics::cSphere(def.Radius);
		mBody = new MyPhysics::cRigidBody(rigiddef, mShape);
	}

	/**
	 * \method		GetTransform
	 * \fullname	DegenMyPhysicsWrapper::cSphere::GetTransform
	 * \brief		mBody GetTransform wrapper
	 *
	 * \access		virtual public
	 * \return		glm::mat4 & transformOut
	 *
	 * \desc		Get the transform calculation for rendering the object
	 */
	void cSphere::GetTransform(glm::mat4& transformOut)
	{
		mBody->GetTransform(transformOut);
	}

	/**
	 * \method		ApplyForce
	 * \fullname	DegenMyPhysicsWrapper::cSphere::ApplyForce
	 * \brief		mBody ApplyForce Wrapper
	 *
	 * \access		virtual public
	 * \return		void
	 * \param		const glm::vec3 & force
	 *
	 * \desc		add force to the acceleration of the object
	 */
	void cSphere::ApplyForce(const glm::vec3& force)
	{
		mBody->ApplyForce(force);
	}


}