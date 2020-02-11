#pragma once
/**
 * \file	iCollisionListener.h
 * \path	D:\GDP\Degenerate\DegenPhysicsInterface\physics\interfaces
 * \brief	Interface File
 *
 * \desc	contains the iCollisionListener interface
 */
namespace DegenPhysics
{
	/**
	 * \class	iCollisionListener
	 * \brief	Interface Class
	 *
	 * \desc	collision report interface to be implemented later
	 */
	class iCollisionListener
	{
	public:
		virtual ~iCollisionListener() = 0;
		// virtual void Collide(iPhysicsComponent* compA, iPhysicsComponent* compB) = 0;
	};
}