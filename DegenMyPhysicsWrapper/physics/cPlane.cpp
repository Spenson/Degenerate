/**
 * \file	cPlane.cpp
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class Implementation File
 *
 * \desc	contains the implementation of the cPhysicsFactory class
 */
#include "cPlane.h"

namespace DegenMyPhysicsWrapper
{
	/**
	 * \method		~cPlane
	 * \fullname	DegenMyPhysicsWrapper::cPlane::~cPlane
	 * \brief		dtor
	 *
	 * \access		virtual public
	 *
	 * \desc		cleans up mBody and mShape
	 */
	cPlane::~cPlane()
	{
		delete mBody;
		delete mShape;
	}

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
	cPlane::cPlane(DegenPhysics::sPlaneDef def)
	{
		mShape = new MyPhysics::cPlane(def.Normal,def.Constant);
		
		MyPhysics::sRigidBodyDef rigiddef;
		rigiddef.Position = glm::vec3(0.f);
		rigiddef.Acceleration = glm::vec3(0.f);
		rigiddef.Mass = 0.f;
		rigiddef.Velocity = glm::vec3(0.f);
		
		mBody = new MyPhysics::cRigidBody(rigiddef, mShape);
		
	}

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
	void cPlane::GetTransform(glm::mat4& transformOut)
	{
		//calculate matrix off of plane shape info
		transformOut = glm::mat4(1.f);
		transformOut = glm::translate(transformOut, mShape->GetNormal() * mShape->GetConstant());
		if(mShape->GetNormal() == glm::vec3(0.f,1.f,0.f))
			transformOut *= glm::mat4(glm::quatLookAt(mShape->GetNormal(), glm::vec3(0.f, 0.f, 1.f)));
		else
		transformOut *= glm::mat4(glm::quatLookAt(mShape->GetNormal(), glm::vec3(0.f, 1.f, 0.f)));
		//mBody->GetTransform(transformOut);
	}

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
	void cPlane::ApplyForce(const glm::vec3& force)
	{
		mBody->ApplyForce(force);
	}

}
