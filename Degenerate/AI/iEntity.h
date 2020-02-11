#pragma once

#include "../GLCommon.h"

namespace DegenBehaviours
{
	class iEntity
	{
	public:
		virtual glm::vec3 Position() = 0;
		virtual glm::vec3 Velocity() = 0;
		virtual glm::quat Rotation() = 0;
		virtual void Rotation(glm::quat rotation) = 0;
		virtual void Velocity(glm::vec3 velocity) = 0;
		virtual void Diffuse(glm::vec4 diffuse) = 0;

		virtual float Mass() = 0;
		
		virtual float MaxVelocity() = 0;
		virtual float MaxForce() = 0;
		virtual float MaxSpeed() = 0;

		virtual void Action()=0;
	};
}
