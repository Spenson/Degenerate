#include "cWorld.h"
#include "cIntegrator.h"
#include "nCollide.h"

namespace MyPhysics
{
	cWorld::cWorld() : mDt(0.f), mIntegrator(), mGravity(glm::vec3(0.f, -5.f, 0.f))
	{
	}

	void cWorld::GetGravity(glm::vec3& gravityOut)
	{
		gravityOut = mGravity;
	}

	void cWorld::SetGravity(const glm::vec3& newGravity)
	{
		mGravity = newGravity;
	}

	void cWorld::IntegrateRigidBody(cRigidBody* body, float dt)
	{
		if (body->IsStatic()) return;
		body->mPreviousPosition = body->mPosition;
		body->mPreviousVelocity = body->mVelocity;
		mIntegrator.RK4(body->mPosition, body->mVelocity, body->mAcceleration, mGravity, dt);
		body->mAcceleration = glm::vec3(0.f);
		body->mVelocity *= pow(0.95f, dt);
	}


	void cWorld::Update(float dt)
	{
		size_t numBodies = mBodies.size();
		if (0 == numBodies)
		{
			return;
		}

		mDt = dt;

		// Step 1: Integrate
		for (size_t c = 0; c < numBodies; c++)
		{
			IntegrateRigidBody(mBodies[c], mDt); 
		}
		// Step 2: Handle Collisions!
		for (size_t idxA = 0; idxA < numBodies - 1; idxA++)
		{
			for (size_t idxB = idxA + 1; idxB < numBodies; idxB++)
			{
				Collide(mBodies[idxA], mBodies[idxB]);
			}
		}
		// Step 3: Clear the accelerations!
		for (size_t c = 0; c < numBodies; c++)
		{
			mBodies[c]->mAcceleration = glm::vec3(0.0f, 0.0f, 0.0f);
		}

	}

	bool cWorld::AddRigidBody(cRigidBody* rigidBody)
	{
		if (!rigidBody) return false;
		std::vector<cRigidBody*>::iterator itBody = std::find(mBodies.begin(), mBodies.end(), rigidBody);
		if (mBodies.end() == itBody)
		{
			mBodies.push_back(rigidBody);
			return true;
		}
		return false;
	}

	bool cWorld::RemoveRigidBody(cRigidBody* rigidBody)
	{
		if (!rigidBody) return false;
		std::vector<cRigidBody*>::iterator itBody = std::find(mBodies.begin(), mBodies.end(), rigidBody);
		if (mBodies.end() == itBody) return false;
		mBodies.erase(itBody);
		return true;
	}

	bool cWorld::Collide(cRigidBody* bodyA, cRigidBody* bodyB)
	{
		eShapeType shapeTypeA = bodyA->GetShapeType();
		eShapeType shapeTypeB = bodyB->GetShapeType();
		if (shapeTypeA == eShapeType::plane)
		{
			if (shapeTypeB == eShapeType::plane)
			{
				return false;
			}
			if (shapeTypeB == eShapeType::sphere)
			{
				return CollideSpherePlane(bodyB, dynamic_cast<cSphere*>(bodyB->GetShape()),
										  bodyA, dynamic_cast<cPlane*>(bodyA->GetShape()));
			}
		}
		if (shapeTypeA == eShapeType::sphere)
		{
			if (shapeTypeB == eShapeType::plane)
			{
				return CollideSpherePlane(bodyA, dynamic_cast<cSphere*>(bodyA->GetShape()),
										  bodyB, dynamic_cast<cPlane*>(bodyB->GetShape()));
			}
			if (shapeTypeB == eShapeType::sphere)
			{
				return CollideSphereSphere(bodyA, dynamic_cast<cSphere*>(bodyA->GetShape()),
										   bodyB, dynamic_cast<cSphere*>(bodyB->GetShape()));
			}
		}

		return false;
	}

	bool cWorld::CollideSpherePlane(cRigidBody* sphereBody, cSphere* sphereShape, cRigidBody* planeBody, cPlane* planeShape)
	{
		// CHAPTER 5.5 IntersectionMovingShperePlane

		// IntersectionMovingShperePlane

		
		glm::vec3 c = sphereBody->mPreviousPosition;
		float r = sphereShape->GetRadius();
		glm::vec3 v = sphereBody->mPosition - sphereBody->mPreviousPosition;
		glm::vec3 n = planeShape->GetNormal();
		float d = planeShape->GetConstant();
		float t(0.f);
		glm::vec3 q(0.f);

		//test collision
		int result = nCollide::intersect_moving_sphere_plane(c, r, v, n, d, t, q);
		if (0 == result)
		{
			// no collision
			return false;
		}
		if (-1 == result)
		{
			// about where it collided
			glm::vec3 pointOnPlane = nCollide::closest_point_on_plane(sphereBody->mPreviousPosition, planeShape->GetNormal(), planeShape->GetConstant());

			// figure out impulse ffor sphere to escape plane
			float distance = glm::distance(sphereBody->mPreviousPosition, pointOnPlane);
			float targetDistance = r;
			glm::vec3 impulse = n * (targetDistance - distance) / mDt;
			// reset sphere and apply impulse
			sphereBody->mPosition = sphereBody->mPreviousPosition;
			sphereBody->mVelocity = sphereBody->mPreviousVelocity;
			sphereBody->mVelocity += impulse;
			// reintegrate
			IntegrateRigidBody(sphereBody, mDt);

			return true;
		}

		// reset to collision point
		sphereBody->mVelocity = glm::reflect(sphereBody->mVelocity, planeShape->GetNormal());

		glm::vec3 nComponent = glm::proj(sphereBody->mVelocity, planeShape->GetNormal());
		sphereBody->mVelocity -= nComponent * 0.2f;

		sphereBody->mPosition = (c + v * t);

		// reintegrate
		IntegrateRigidBody(sphereBody, mDt * (1.f - t));


		return true;
	}

	bool cWorld::CollideSphereSphere(cRigidBody* bodyA, cSphere* shapeA, cRigidBody* bodyB, cSphere* shapeB)
	{
		glm::vec3 cA = bodyA->mPreviousPosition;
		glm::vec3 cB = bodyB->mPreviousPosition;
		glm::vec3 vA = bodyA->mPosition - bodyA->mPreviousPosition;
		glm::vec3 vB = bodyB->mPosition - bodyB->mPreviousPosition;
		float rA = shapeA->GetRadius();
		float rB = shapeB->GetRadius();
		float t(0.f);
		// test for collision
		int result = nCollide::intersect_moving_sphere_sphere(cA, rA, vA, cB, rB, vB, t);

		if (0 == result)
		{
			// no collision
			return false;
		}
		// object mass for weighted response
		float ma = bodyA->mMass;
		float mb = bodyB->mMass;
		float mt = ma + mb;

		if (-1 == result)
		{
			// get adjust dist
			float initDist = glm::distance(bodyA->mPreviousPosition, bodyB->mPreviousPosition);
			float targDist = rA + rB;

			// get direction spheres will move
			glm::vec3 impulseToA = glm::normalize(bodyA->mPreviousPosition - bodyB->mPreviousPosition);
			impulseToA *= targDist - initDist;

			// reset position and velocity
			bodyA->mPosition = bodyA->mPreviousPosition;
			bodyB->mPosition = bodyB->mPreviousPosition;
			bodyA->mVelocity = bodyA->mPreviousVelocity;
			bodyB->mVelocity = bodyB->mPreviousVelocity;

			// adjust velocity
			bodyA->mVelocity += impulseToA * (mb / mt);
			bodyB->mVelocity -= impulseToA * (ma / mt);

			// reintegrate
			IntegrateRigidBody(bodyA, mDt);
			IntegrateRigidBody(bodyB, mDt);

			return true;
		}

		//set to point of collision
		bodyA->mPosition = bodyA->mPreviousPosition + vA * t;
		bodyB->mPosition = bodyB->mPreviousPosition + vB * t;

		// get velocities for response calc
		vA = bodyA->mVelocity;
		vB = bodyB->mVelocity;

		// calculate responses
		float c = 0.2f;
		bodyA->mVelocity = (c * mb * (vB - vA) + ma * vA + mb * vB) / mt;
		bodyB->mVelocity = (c * ma * (vA - vB) + ma * vA + mb * vB) / mt;

		// reintegrate
		IntegrateRigidBody(bodyA, mDt * (1.f - t));
		IntegrateRigidBody(bodyB, mDt * (1.f - t));


		return true;
	}

}
