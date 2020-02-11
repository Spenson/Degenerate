#pragma once
#include <physics/interfaces/iPhysicsFactory.h>
#include <string>

namespace DegenPhysics
{
	static iPhysicsFactory* PhysicsFactory;

	bool LoadPhysicsFactory(std::string dll);
	iSphereComponent* CreateObject(sSphereDef def);
	iPlaneComponent* CreateObject(sPlaneDef def);
	iPhysicsWorld* CreateWorld();
}
