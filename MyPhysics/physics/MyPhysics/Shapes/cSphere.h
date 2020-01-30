#pragma once

#include "iShape.h"

namespace MyPhysics
{
	class cSphere : public iShape
	{
	public:
		virtual ~cSphere() {}
		cSphere(float radius) : iShape(eShapeType::sphere), mRadius(radius) {}

		inline const float GetRadius() { return mRadius; }
	private:
		float mRadius;

		// in private defualt, copy, operator=
		cSphere() = delete;
		cSphere(const cSphere& other) = delete;
		cSphere& operator=(const cSphere& other) = delete;

	};

}