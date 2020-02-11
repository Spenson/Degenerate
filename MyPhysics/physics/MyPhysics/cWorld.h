#pragma once

#include <vector>

#include "cRigidBody.h"
#include "Shapes/cSphere.h"
#include "Shapes/cPlane.h"
#include "cIntegrator.h"

namespace MyPhysics
{
	class cWorld
	{
	public:
		cWorld();
		virtual ~cWorld() = default;
		
		void GetGravity(glm::vec3& gravityOut);
		void SetGravity(const glm::vec3& newGravity);

		void Update(float dt);

		bool AddRigidBody(cRigidBody* rigidBody);
		bool RemoveRigidBody(cRigidBody* rigidBody);
		
	protected:
		void IntegrateRigidBody(cRigidBody*, float dt);
		bool Collide(cRigidBody* bodyA, cRigidBody* bodyB);
		bool CollideSpherePlane(cRigidBody* sphereBody, cSphere* sphereShape, cRigidBody* planeBody, cPlane* planeShape);
		bool CollideSphereSphere(cRigidBody* bodyA, cSphere* shapeA, cRigidBody* bodyB, cSphere* shapeB);

	private:
		float mDt;
		cIntegrator mIntegrator;
		glm::vec3 mGravity;
		std::vector<cRigidBody*> mBodies;

		
		cWorld(const cWorld& other) = delete;
		cWorld& operator=(const cWorld& other) = delete;
	};

}
