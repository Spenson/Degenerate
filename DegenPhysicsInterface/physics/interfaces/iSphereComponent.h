#pragma once
/**
 * \file	iSphereComponent.h
 * \path	D:\GDP\Degenerate\DegenPhysicsInterface\physics\interfaces
 * \brief	Interface File
 *
 * \desc	contains the iSphereComponent interface
 */
#include "iPhysicsComponent.h"

namespace DegenPhysics
{
	/**
	 * \struct	sSphereDef
	 * \brief	details for creating a sphere
	 */
	struct sSphereDef
	{
		float Mass;
		float Radius;
		glm::vec3 Position;
		glm::vec3 Velocity;
		glm::vec3 Acceleration;

	};

	/**
	 * \class	iSphereComponent
	 * \brief	Interface representing a sphere
	 */
	class iSphereComponent : public iPhysicsComponent
	{
	public:
		/**
		 * \method		~iSphereComponent
		 * \fullname	DegenPhysics::iSphereComponent::~iSphereComponent
		 * \brief		dtor
		 *
		 * \access		virtual public 
		 * \return		
		 *
		 * \desc		default
		 */
		virtual ~iSphereComponent() = default;

	protected:
		/**
		 * \method		iSphereComponent
		 * \fullname	DegenPhysics::iSphereComponent::iSphereComponent
		 * \brief		ctor
		 *
		 * \access		protected 
		 *
		 * \desc		only accessible by subclasses
		 */
		iSphereComponent() : iPhysicsComponent(eComponentType::sphere) {}
	private:
		// deleted to be inaccessible 
		iSphereComponent(const iSphereComponent& other) = delete;
		iSphereComponent& operator=(const iSphereComponent& other) = delete;
	};
}