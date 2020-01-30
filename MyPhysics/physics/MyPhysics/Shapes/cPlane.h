#pragma once

#include "iShape.h"
#include"glmCommon.h"

namespace MyPhysics
{
	class cPlane : public iShape
	{
	public:
		virtual ~cPlane() {}
		cPlane(glm::vec3 normal, float constant) : iShape(eShapeType::plane), mNormal(normal), mConstant(constant) {}
		//ax + by + cz = d

		inline const glm::vec3 GetNormal() { return mNormal; }
		inline const float GetConstant() { return mConstant; }

	private:
		glm::vec3 mNormal;
		float mConstant;

		// in private defualt, copy, operator=
		cPlane() = delete;
		cPlane(const cPlane& other) = delete;
		cPlane& operator=(const cPlane& other) = delete;
	};

}