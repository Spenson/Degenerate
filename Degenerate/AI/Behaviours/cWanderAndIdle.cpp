#include "cWanderAndIdle.h"

namespace DegenBehaviours
{
	cWanderAndIdle::cWanderAndIdle(iEntity* agent, iEntity* target) : mAgent(agent)
	{
	}
	cWanderAndIdle::~cWanderAndIdle(void)
	{
	}
	void cWanderAndIdle::Update(float dt)
	{
		if (mAgent == nullptr) return;
		
		this->mTime += dt;
		if (mIdle)
		{
			mAgent->Diffuse(glm::vec4(0.6f, 0.f, 1.f, 1.f));
			float rotation = (rand() % 10)-5;

			//glm::quatLookAt(-glm::normalize(glm::vec3(rand(), 0.f, rand())), glm::vec3(0.f, 1.f, 0.f))
			mAgent->Velocity(glm::vec3(0.f));
			mAgent->Rotation(mAgent->Rotation() * glm::quat(glm::vec3(0.f,glm::radians(rotation),0.f)));
			mAgent->Action();
			if (this->mTime > 3.f)
			{
				this->mTime = 0.f;
				mIdle = false;
			}
		}
		else
		{
			mAgent->Diffuse(glm::vec4(1.f, 0.f, 0.6f, 1.f));
			const int radius = 3;
			float rotation = rand() % 360;
			float varience = (float)(rand() % (radius*100))/100.f;
			const float distance = 5.f;
			glm::vec3 center = mAgent->Position();
			
			if(glm::length(mAgent->Velocity()) > 0.f)
				center += (mAgent->Velocity() * distance);

			glm::vec3 target = glm::quat(glm::vec3(0.f,glm::radians(rotation),0.f)) * glm::vec3(0.f,0.f,varience);
			target += center;



			glm::vec3 desired_velocity = glm::normalize(target - mAgent->Position()) * mAgent->MaxVelocity();
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

			

			if (this->mTime > 6.f)
			{
				this->mTime = 0.f;
				mIdle = true;
			}
		}
	}
}