#pragma once
#include "components/iSphereComponent.h"
#include "components/iPlaneComponent.h"
#include "iPhysicsWorld.h"

namespace DegenPhysics
{
	class iPhysicsFactory
	{
	public:
		virtual ~iPhysicsFactory() {}
		virtual iPhysicsWorld* CreateWorld() = 0;
		// components
		virtual iSphereComponent* CreateBall(const sSphereDef& def) = 0;
		virtual iPlaneComponent* CreatePlane(const sPlaneDef& def) = 0;
	};
}