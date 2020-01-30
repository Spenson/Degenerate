#pragma once


namespace DegenPhysics
{
	class iPhysicsWorld
	{
	public:
		virtual ~iPhysicsWorld(){}

		virtual void Update(float dt) = 0;
		virtual void AddObject(iPhysicsComponent* component) = 0;
		virtual void RemoveObject(iPhysicsComponent* component) = 0;
	};
}