#pragma once

#include "iPhysicsComponent.h"

namespace DegenPhysics
{
	struct sSphereDef
	{
		float Mass;
		float Radius;
		glm::vec3 Position;
	};

	class iSphereComponent : public iPhysicsComponent
	{
	public:
		virtual ~iSphereComponent() {}

	protected:
		iSphereComponent(sSphereDef def) : iPhysicsComponent(eComponentType::sphere) {}
	private:
		iSphereComponent() = delete;
		iSphereComponent(const iSphereComponent& other) = delete;
		iSphereComponent& operator=(const iSphereComponent& other) = delete;
	};
}