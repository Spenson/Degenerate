#pragma once


namespace DegenPhysics
{
	class iPhysicsWorld
	{
	public:
		virtual ~iPhysicsWorld(){}

		virtual void Update(float dt) = 0;
		virtual void AddObject(/*TODO: physics object*/) = 0;
		virtual void RemoveObject(/*TODO: physics object*/) = 0;
	};
}