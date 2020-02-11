#pragma once
/**
 * \file	iPhysicsComponent.h
 * \path	D:\GDP\Degenerate\DegenPhysicsInterface\physics\interfaces
 * \brief	Interface File
 *
 * \desc	contains the iPhysicsComponent interface
 */

#include "eComponentType.h"
#include "glmCommon.h"


namespace DegenPhysics
{
	/**
	 * \class	iPhysicsComponent
	 * \brief	Interface
	 *
	 * \member	iPhysicsComponent
	 *
	 * \desc	General layout of physics components +
	 */
	class iPhysicsComponent
	{
		
	public:
		/**
		 * \method		~iPhysicsComponent
		 * \fullname	DegenPhysics::iPhysicsComponent::~iPhysicsComponent
		 * \brief		dtor
		 *
		 * \access		virtual public 
		 * \return		
		 *
		 * \desc		default implementation
		 */
		virtual ~iPhysicsComponent() = default;
		/**
		 * \method		GetComponentType
		 * \fullname	DegenPhysics::iPhysicsComponent::GetComponentType
		 * \brief		accessor
		 *
		 * \access		public 
		 * \return		const DegenPhysics::eComponentType&
		 *
		 * \desc		returns the component type
		 */
		inline const eComponentType& GetComponentType() { return mComponentType; }

		/**
		 * \method		GetTransform
		 * \fullname	DegenPhysics::iPhysicsComponent::GetTransform
		 * \brief		get the location/rotation transform of the component
		 *
		 * \access		virtual public 
		 * \return		void
		 * \return		glm::mat4 & transformOut
		 */
		virtual void GetTransform(glm::mat4& transformOut) = 0;
		/**
		 * \method		ApplyForce
		 * \fullname	DegenPhysics::iPhysicsComponent::ApplyForce
		 * \brief		apply force to component
		 *
		 * \access		virtual public 
		 * \return		void
		 * \param		const glm::vec3 & force
		 */
		virtual void ApplyForce(const glm::vec3& force) = 0;

	protected:
		/**
		 * \method		iPhysicsComponent
		 * \fullname	DegenPhysics::iPhysicsComponent::iPhysicsComponent
		 * \brief		ctor
		 *
		 * \access		protected 
		 * \param		eComponentType componentType
		 *
		 * \desc		only accessible by subclasses
		 */
		iPhysicsComponent(eComponentType componentType) : mComponentType(componentType) {}
		
	private:
		eComponentType mComponentType;

		// get rid of these!
		//deleted constructors
		iPhysicsComponent() = delete;
		iPhysicsComponent(const iPhysicsComponent& other) = delete;
		iPhysicsComponent& operator=(const iPhysicsComponent& other) = delete;
	};
}