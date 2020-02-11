#include "cSeek.h"

namespace DegenBehaviours
{
	cSeek::cSeek(iEntity* agent, iEntity* target) : mAgent(agent), mTarget(target)
	{
		
	}

	cSeek::~cSeek(void)
	{
	}

	void cSeek::Update(float dt)
	{
		if (mAgent == nullptr || mTarget == nullptr) return;

		glm::vec3 desired_velocity = glm::normalize(mTarget->Position() - mAgent->Position()) * mAgent->MaxVelocity();
		glm::vec3 steering = desired_velocity - mAgent->Velocity();

		if(glm::length(steering) > mAgent->MaxForce())
			steering = glm::normalize(steering) * mAgent->MaxForce();
		
		steering = steering / mAgent->Mass();

		glm::vec3 velocity = mAgent->Velocity() + steering;
		if(glm::length(velocity) > mAgent->MaxSpeed())
			velocity = glm::normalize(velocity) * mAgent->MaxSpeed();

		mAgent->Velocity(velocity);
		
	}
}