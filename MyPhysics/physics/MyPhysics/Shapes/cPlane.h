#pragma once
/**
 * \file	cPlane.h
 * \path	D:\GDP\Degenerate\MyPhysics\physics\MyPhysics\Shapes
 * \brief	Class Header File
 *
 * \desc	contains the description of cPlane
 */
#include "../iShape.h"

namespace MyPhysics
{
	/**
	 * \class	cPlane
	 * \brief	representation of a plane
	 */
	class cPlane : public iShape
	{
	public:
		/**
		 * \method		~cPlane
		 * \fullname	MyPhysics::cPlane::~cPlane
		 * \brief		default dtor
		 *
		 * \access		virtual public 	
		 */
		virtual ~cPlane() = default;
		/**
		 * \method		cPlane
		 * \fullname	MyPhysics::cPlane::cPlane
		 * \brief		ctor
		 *
		 * \access		public 
		 * \param		glm::vec3 normal
		 * \param		float constant
		 */
		cPlane(glm::vec3 normal, float constant) : iShape(eShapeType::plane), mNormal(normal), mConstant(constant) {}

		
		/**
		 * \method		GetNormal
		 * \fullname	MyPhysics::cPlane::GetNormal
		 * \brief		returns plane normal
		 *
		 * \access		public 
		 * \return		const glm::vec3
		 */
		inline const glm::vec3 GetNormal() { return mNormal; }
		/**
		 * \method		GetConstant
		 * \fullname	MyPhysics::cPlane::GetConstant
		 * \brief		returns plane constant
		 *
		 * \access		public 
		 * \return		const float
		 */
		inline const float GetConstant() { return mConstant; }

	private:
		glm::vec3 mNormal;
		float mConstant;

		// deleted to be make inaccessible
		cPlane() = delete;
		cPlane(const cPlane& other) = delete;
		cPlane& operator=(const cPlane& other) = delete;
	};

}