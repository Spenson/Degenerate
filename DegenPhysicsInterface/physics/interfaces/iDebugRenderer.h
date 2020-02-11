#pragma once
/**
 * \file	iDebugRenderer.h
 * \path	D:\GDP\Degenerate\DegenPhysicsInterface\physics\interfaces
 * \brief	Interface File
 *
 * \desc	contains the iDebugRenderer interface
 */
#include "glmCommon.h"

// TODO: Implement
namespace DegenPhysics
{
	class iDebugRenderer
	{
	/**
	 * \class	iDebugRenderer
	 * \brief	Not Implemented
	 *
	 * \member	iDebugRenderer
	 *
	 * \desc	
	 */
	public:
		virtual ~iDebugRenderer() {}
		//virtual void DrawLine(const glm::vec3& startPoing, const glm::vec3& endPoint) = 0;
		//virtual void DrawCube(const glm::vec3& center, float halfLength) = 0;
		virtual void DrawSphere(const glm::vec3& center, float radius) = 0;
	};
}