#include "cEvade.h"
namespace DegenBehaviours
{
	cEvade::cEvade(iEntity* agent, iEntity* target) : mAgent(agent), mTarget(target)
	{
	}
	cEvade::~cEvade(void)
	{
	}
	void cEvade::Update(float dt)
	{
		if (mAgent == nullptr || mTarget == nullptr) return;

		glm::vec3 perdicted_position = mTarget->Position() + (mTarget->Velocity() * (glm::distance(mTarget->Position(), mAgent->Position()) / mAgent->MaxSpeed()));

		glm::vec3 desired_velocity = glm::normalize(mAgent->Position() - perdicted_position) * mAgent->MaxVelocity();

		glm::vec3 steering = desired_velocity - mAgent->Velocity();

		if (glm::length(steering) > mAgent->MaxForce())
			steering = glm::normalize(steering) * mAgent->MaxForce();

		steering = steering / mAgent->Mass();

		glm::vec3 velocity = mAgent->Velocity() + steering;

		if (glm::length(velocity) > mAgent->MaxSpeed())
			velocity = glm::normalize(velocity) * mAgent->MaxSpeed();

		mAgent->Velocity(velocity);
	}
}