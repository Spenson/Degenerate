#pragma once

#include "iShape.h"
#include "glmCommon.h"

namespace MyPhysics
{
	struct sRigidBodyDef
	{
		float Mass;
		glm::vec3 Position;
		glm::vec3 Velocity;
		//glm::vec3 Acceleration;
	};
	class cRigidBody
	{
		friend class cWorld;
	public:
		cRigidBody(const sRigidBodyDef& def, iShape* shape);

		void GetTransform(glm::mat4& transformOut);
		void ApplyForce(const glm::vec3& force);


		inline bool IsStatic() { return mMass == 0.f; }
		inline iShape* GetShape() { return mShape; }
		inline eShapeType GetShapeType() { return mShape->GetShapeType(); }

	private:
		iShape* mShape;
		
		float mMass;
		float mInvMass;
		
		glm::vec3 mPosition;
		glm::vec3 mPreviousPosition;
		
		glm::vec3 mVelocity;
		glm::vec3 mAcceleration;

		cRigidBody() = delete;
		cRigidBody(const cRigidBody&) = delete;
		cRigidBody& operator=(const cRigidBody&) = delete;
	};
}