#pragma once

#include "glmIncludes.hpp"
#include "iPhysicsComponent.h"

namespace DegenPhysics
{
	struct sPlaneDef
	{
		float Constant;
		glm::vec3 Normal;
	};
	class iPlaneComponent : public iPhysicsComponent
	{
	public:
		virtual ~iPlaneComponent() {}

	protected:
		iPlaneComponent() : iPhysicsComponent(eComponentType::plane) {}
	private:
		iPlaneComponent() = delete;
		iPlaneComponent(const iPlaneComponent& other) = delete;
		iPlaneComponent& operator=(const iPlaneComponent& other) = delete;
	};
}