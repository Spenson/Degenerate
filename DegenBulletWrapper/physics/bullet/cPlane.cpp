/**
 * \file	cPlane.cpp
 * \path	D:\GDP\Degenerate\DegenMyPhysicsWrapper\physics
 * \brief	Class Implementation File
 *
 * \desc	contains the implementation of the cPhysicsFactory class
 */
#include "cPlane.h"
#include "nConvert.h"


namespace DegenBulletPhysicsWrapper
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
		mBody->setUserPointer(nullptr);
		delete mBody->getCollisionShape();
		delete mBody->getMotionState();
		delete mBody;
		mBody = nullptr;
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
		btCollisionShape* shape = new btStaticPlaneShape(nConvert::ToBullet(def.Normal), def.Constant);

		btTransform transform;
		transform.setIdentity();


		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(0.f, myMotionState, shape, btVector3(0,0,0));
		rbInfo.m_restitution = 1.f;
		mBody = new btRigidBody(rbInfo);
		mBody->setUserPointer(this);
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
		const float& constant = ((btStaticPlaneShape*)mBody->getCollisionShape())->getPlaneConstant();
		const glm::vec3& normal = nConvert::ToGLM(((btStaticPlaneShape*)mBody->getCollisionShape())->getPlaneNormal());
		//calculate matrix off of plane shape info
		transformOut = glm::translate(glm::mat4(1.f), normal * constant);
		if (normal == glm::vec3(0.f, 1.f, 0.f))
			transformOut *= glm::mat4(glm::quatLookAt(normal, glm::vec3(0.f, 0.f, 1.f)));
		else
			transformOut *= glm::mat4(glm::quatLookAt(normal, glm::vec3(0.f, 1.f, 0.f)));
		//mBody->GetTransform(transformOut);
		//mBody->getCollisionShape()
		/*btTransform transform;
		mBody->getMotionState()->getWorldTransform(transform);
		nConvert::ToGLM(transform, transformOut);*/
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
		
	}

}
