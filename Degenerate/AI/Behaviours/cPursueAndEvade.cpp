#include "cPursueAndEvade.h"

namespace DegenBehaviours
{
	std::vector<iEntity*> cPursueAndEvade::mEvade;

	cPursueAndEvade::cPursueAndEvade(iEntity* agent, iEntity* target) : mAgent(agent), mTarget(target)
	{
	}
	cPursueAndEvade::~cPursueAndEvade(void)
	{
	}
	void cPursueAndEvade::Update(float dt)
	{

		if (mAgent == nullptr) return;



		float dis_over_speed = distance(mAgent->Position(), mTarget->Position()) / mAgent->MaxSpeed();
		glm::vec3 desired_velocity;
		if (mEvade.empty())
		{
			glm::vec3 perdicted_position = mTarget->Position() + (mTarget->Velocity() * (dis_over_speed / 2.f));
			desired_velocity = glm::normalize(perdicted_position - mAgent->Position()) * mAgent->MaxVelocity();
			mAgent->Diffuse(glm::vec4(0.f, 1.f, 0.f, 1.f));
		}
		else
		{
			mAgent->Diffuse(glm::vec4(0.f, 0.5f, 0.f, 1.f));
			iEntity* target = mEvade.front();

			for (auto& entity : mEvade)
			{
				if (glm::distance(target->Position(), mAgent->Position()) > glm::distance(entity->Position(), mAgent->Position()))
				{
					target = entity;
				}
			}

			glm::vec3 perdicted_position = target->Position() + (target->Velocity() * (dis_over_speed / 2.f));
			desired_velocity = glm::normalize(mAgent->Position() - perdicted_position) * mAgent->MaxVelocity();

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
	void cPursueAndEvade::AddEvade(iEntity* evade)
	{
		mEvade.push_back(evade);
	}
	void cPursueAndEvade::RemoveEvade(iEntity* evade)
	{
		
		auto iter = std::find(mEvade.begin(), mEvade.end(), evade);
		if (iter != mEvade.end())
			mEvade.erase(iter);
	}
}