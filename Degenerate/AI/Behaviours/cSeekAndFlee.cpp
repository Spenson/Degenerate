#include "cSeekAndFlee.h"

namespace DegenBehaviours
{
	cSeekAndFlee::cSeekAndFlee(iEntity* agent, iEntity* target) : mAgent(agent), mTarget(target)
	{

	}

	cSeekAndFlee::~cSeekAndFlee(void)
	{
	}

	void cSeekAndFlee::Update(float dt)
	{
		if (mAgent == nullptr || mTarget == nullptr) return;

		glm::vec3 desired_velocity;
		if (glm::dot(glm::normalize(mAgent->Position() - mTarget->Position()), mTarget->Rotation() * glm::vec3(0.f, 0.f, 1.f)) < 0.5f)
		{
			desired_velocity = glm::normalize(mTarget->Position() - mAgent->Position()) * mAgent->MaxVelocity();
			mAgent->Diffuse(glm::vec4(1.f, 0.f, 0.f, 1.f));
		}
		else
		{
			desired_velocity = glm::normalize(mAgent->Position() - mTarget->Position()) * mAgent->MaxVelocity();
				mAgent->Diffuse(glm::vec4(0.5f, 0.f, 0.f, 1.f));
		}

		glm::vec3 steering = desired_velocity - mAgent->Velocity();

		if (glm::length(steering) > mAgent->MaxForce())
			steering = glm::normalize(steering) * mAgent->MaxForce();

		steering = steering / mAgent->Mass();
		
		glm::vec3 velocity = mAgent->Velocity() + steering;
		
		if (glm::length(velocity) > mAgent->MaxSpeed())
			velocity = glm::normalize(velocity) * mAgent->MaxSpeed();

		mAgent->Velocity(velocity);
		if (glm::length(velocity) > 0)
			mAgent->Rotation(glm::quatLookAt(-glm::normalize(velocity), glm::vec3(0.f, 1.f, 0.f)));

	}
}