#include "cFireFromDistance.h"
namespace DegenBehaviours
{
	cFireFromDistance::cFireFromDistance(iEntity* agent, iEntity* target) : mAgent(agent), mTarget(target)
	{
	}
	cFireFromDistance::~cFireFromDistance(void)
	{
	}
	void cFireFromDistance::Update(float dt)
	{
		if (mAgent == nullptr || mTarget == nullptr) return;
		
		float dis = distance(mAgent->Position(), mTarget->Position());
		float dis_over_speed = dis / mAgent->MaxSpeed();
		glm::vec3 desired_velocity;
		if (dis_over_speed < 3.f)
		{
			mAgent->Diffuse(glm::vec4(0.f,0.f,0.2f,1.f));
			desired_velocity = glm::normalize(mAgent->Position() - mTarget->Position()) * mAgent->MaxVelocity();
		}
		else if (dis_over_speed < 3.2f)
		{
			mAgent->Diffuse(glm::vec4(0.f, 0.0f, 0.5f, 1.f));
			mAgent->Velocity(glm::vec3(0.f));
			mAgent->Rotation(glm::quatLookAt(-glm::normalize(mTarget->Position() - mAgent->Position()), glm::vec3(0.f, 1.f, 0.f)));
			mAgent->Action();
			return;
		}
		else if (dis_over_speed < 4.5f)
		{
			mAgent->Diffuse(glm::vec4(0.f, 0.2f, 0.8f, 1.f));
			desired_velocity = glm::normalize(mTarget->Position() - mAgent->Position()) * (mAgent->MaxVelocity()/(1/(dis_over_speed-3.f)));

		}
		else
		{
			mAgent->Diffuse(glm::vec4(0.f, 0.3f, 1.f, 1.f));
			desired_velocity = glm::normalize(mTarget->Position() - mAgent->Position()) * mAgent->MaxVelocity();
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