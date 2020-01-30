#pragma once


#include "eShapeType.h"

namespace MyPhysics
{
	class iShape
	{
	public:
		virtual ~iShape() {}
		inline const eShapeType& GetShapeType() { return mShapeType; }

	protected:
		iShape(eShapeType shapeType) : mShapeType(shapeType) {}
	private:
		eShapeType mShapeType;

		// do not use!!!
		iShape() = delete;
		iShape(const iShape& other) = delete;
		iShape& operator=(const iShape& other) = delete;
	};
}