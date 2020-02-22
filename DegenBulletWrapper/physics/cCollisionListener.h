#pragma once
#include <physics/interfaces/iCollisionListener.h>
#include <physics/interfaces/iPhysicsComponent.h>
#include "bullet/btBulletDynamicsCommon.h"

namespace DegenBulletPhysicsWrapper
{
	/* TODO:Add later when fixing physics after project 3
	class cCollisionListener
	{
		DegenPhysics::iCollisionListener* mCollisionListener;
	public:
		cCollisionListener(DegenPhysics::iCollisionListener* collisionListener);
		virtual ~cCollisionListener();

		virtual void Collide(btRigidBody bodyA, btRigidBody bodyB);
	};
	//*/
}
