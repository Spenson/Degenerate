/**
 * \file	cSphere.cpp
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class Implementation File
 *
 * \desc	contains the implementation of cSphere class
 */

#include "cSphere.h"
#include "nConvert.h"


namespace DegenBulletPhysicsWrapper
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
		mBody->setUserPointer(nullptr);
		delete mBody->getCollisionShape();
		delete mBody->getMotionState();
		delete mBody;
		mBody = nullptr;
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
		btCollisionShape* shape = new btSphereShape(def.Radius);

		btTransform transform;
		transform.setIdentity();
		transform.setOrigin(nConvert::ToBullet(def.Position));

		btScalar mass(def.Mass);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if (isDynamic)
		{
			shape->calculateLocalInertia(mass, localInertia);
		}

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, localInertia);
		rbInfo.m_restitution = 0.95f;
		
		mBody = new btRigidBody(rbInfo);
		mBody->setUserPointer(this);

		// impulse effected by mass velocity is dirrectly set
		//mBody->applyCentralImpulse(nConvert::ToBullet(def.Velocity));
		mBody->setLinearVelocity(nConvert::ToBullet(def.Velocity));

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
		btTransform transform;
		mBody->getMotionState()->getWorldTransform(transform);
		nConvert::ToGLM(transform, transformOut);
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
		mBody->activate(true);
		mBody->applyCentralForce(nConvert::ToBullet(force));
	}


}
