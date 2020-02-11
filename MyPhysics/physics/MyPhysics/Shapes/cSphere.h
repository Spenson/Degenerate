#pragma once
/**
 * \file	cSphere.h
 * \path	D:\GDP\Degenerate\MyPhysics\physics\MyPhysics\Shapes
 * \brief	Class Header File
 *
 * \desc	contains the description of cSphere
 */
#include "../iShape.h"

namespace MyPhysics
{
	/**
	 * \class	cSphere
	 * \brief	representation of a sphere
	 */
	class cSphere : public iShape
	{
	public:
		/**
		 * \method		~cSphere
		 * \fullname	MyPhysics::cSphere::~cSphere
		 * \brief		dtor default
		 *
		 * \access		virtual public 
		 */
		virtual ~cSphere() = default;
		
		/**
		 * \method		cSphere
		 * \fullname	MyPhysics::cSphere::cSphere
		 * \brief		ctor
		 *
		 * \access		public 
		 * \param		float radius
		 */
		cSphere(float radius) : iShape(eShapeType::sphere), mRadius(radius) {}

		/**
		 * \method		GetRadius
		 * \fullname	MyPhysics::cSphere::GetRadius
		 * \brief		returns sphere radius
		 *
		 * \access		public 
		 * \return		const float
		 */
		inline const float GetRadius() { return mRadius; }
	private:
		float mRadius;

		// deleted to be make inaccessible
		cSphere() = delete;
		cSphere(const cSphere& other) = delete;
		cSphere& operator=(const cSphere& other) = delete;

	};

}