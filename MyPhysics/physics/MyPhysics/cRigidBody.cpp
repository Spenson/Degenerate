#include "cRigidBody.h"


namespace MyPhysics
{
	cRigidBody::cRigidBody(const sRigidBodyDef& def, iShape* shape) : mShape(shape), mVelocity(def.Velocity), mAcceleration(def.Acceleration)
	{
		if (0.f == mMass) mInvMass = 0.f;
		else mInvMass == 1.f / mMass;
	}

	void cRigidBody::GetTransform(glm::mat4& transformOut)
	{
		transformOut = glm::mat4(1.f);
		//transformOut = glm::rotate(...);
		transformOut = glm::translate(transformOut, mPosition);

	}

	void cRigidBody::ApplyForce(const glm::vec3& force)
	{
		mAcceleration += force * mInvMass;
	}
}