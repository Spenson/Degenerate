#pragma once

namespace DegenPhysics
{
	class iCollisionListener
	{
	public:
		virtual ~iCollisionListener() = 0;
		// virtual void Collide(iPhysicsComponent* compA, iPhysicsComponent* compB) = 0;
	};
}