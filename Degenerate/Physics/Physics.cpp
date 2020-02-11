#include "Physics.h"
#include <Windows.h>

#include <string>
#include <iostream>

namespace DegenPhysics
{
	typedef iPhysicsFactory* (*func_createMathFactory)();

	bool LoadPhysicsFactory(std::string dll)
	{
		char hold[] = "\0";

		HMODULE hModule = 0;

		std::cout << "Loading DLL: " << dll << std::endl;
		hModule = LoadLibrary(dll.c_str());

		if (!hModule)
		{
			std::cout << "Failed to load Library: " << dll << std::endl;
			return 1;
		}

		func_createMathFactory createFactory = (func_createMathFactory)GetProcAddress(hModule, "CreatePhysicsFactory");

		if (!createFactory)
		{
			std::cout << "Failed to get CreatePhysicsFactory function" << std::endl;
			FreeLibrary(hModule);
			return 1;
		}

		std::cout << "Making factory with CreatePhysicsFactory" << std::endl;

		PhysicsFactory = createFactory();
		if (!PhysicsFactory)
		{
			std::cout << "Failed to create PhysicsFactory" << std::endl;
			FreeLibrary(hModule);
			return 1;
		}
		return 0;
	}


	iSphereComponent* CreateObject(sSphereDef def)
	{
		return PhysicsFactory->CreateSphere(def);
	}
	iPlaneComponent* CreateObject(sPlaneDef def)
	{
		return PhysicsFactory->CreatePlane(def);
	}

	iPhysicsWorld* CreateWorld()
	{
		return PhysicsFactory->CreateWorld();
	}
	
}
