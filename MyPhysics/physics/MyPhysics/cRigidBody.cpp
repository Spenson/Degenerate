#include "cRigidBody.h"


namespace MyPhysics
{
	cRigidBody::cRigidBody(const sRigidBodyDef& def, iShape* shape) : mShape(shape), mPosition(def.Position), mVelocity(def.Velocity), mPreviousVelocity(def.Velocity), mAcceleration(def.Acceleration), mMass(def.Mass), mPreviousPosition(def.Position)
	{
		if (0.f == mMass) mInvMass = 0.f;
		else mInvMass = 1.f / mMass;
	}

	void cRigidBody::GetTransform(glm::mat4& transformOut)
	{
		transformOut = glm::mat4(1.f);
		// to do with friction etc.
		//transformOut = glm::rotate(...);
		transformOut = glm::translate(transformOut, mPosition);

	}

	void cRigidBody::ApplyForce(const glm::vec3& force)
	{
		mAcceleration += force * mInvMass;
	}
}