#pragma once
/**
 * \file	iPlaneComponent.h
 * \path	D:\GDP\Degenerate\DegenPhysicsInterface\physics\interfaces
 * \brief	Interface File
 *
 * \desc	contains the iPlaneComponent interface

 */
#include "iPhysicsComponent.h"

namespace DegenPhysics
{
	/**
	 * \struct	sPlaneDef
	 * \brief	details for creating a plane
	 */
	struct sPlaneDef
	{
		float Constant;
		glm::vec3 Normal;
	};
	/**
	 * \class	iPlaneComponent
	 * \brief	Interface representing a plane
	 */
	class iPlaneComponent : public iPhysicsComponent
	{
	public:

		/**
		 * \method		~iPlaneComponent
		 * \fullname	DegenPhysics::iPlaneComponent::~iPlaneComponent
		 * \brief		dtor
		 *
		 * \access		virtual public 
		 * \return		
		 *
		 * \desc		default
		 */
		virtual ~iPlaneComponent() = default;

	protected:
		/**
		 * \method		iPlaneComponent
		 * \fullname	DegenPhysics::iPlaneComponent::iPlaneComponent
		 * \brief		ctor
		 *
		 * \access		protected 
		 *
		 * \desc		only accessible by subclasses 
		 */
		iPlaneComponent() : iPhysicsComponent(eComponentType::plane) {}
	private:
		// deleted to be inaccessible 
		iPlaneComponent(const iPlaneComponent& other) = delete;
		iPlaneComponent& operator=(const iPlaneComponent& other) = delete;
	};
}