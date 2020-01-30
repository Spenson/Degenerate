#pragma once

namespace DegenPhysics
{
	//Currently un-needed. To be completed at a later time.
	class iCollisionListener
	{
	public:
		virtual ~iCollisionListener() = 0;
		// virtual void Collide(iPhysicsComponent* compA, iPhysicsComponent* compB) = 0;
	};
}