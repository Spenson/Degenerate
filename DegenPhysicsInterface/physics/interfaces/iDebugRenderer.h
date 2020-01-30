#pragma once

#include "glmCommon.h"

// TODO: implenment
namespace DegenPhysics
{
	class iDebugRenderer
	{
	public:
		virtual ~iDebugRenderer() {}
		//virtual void DrawLine(const glm::vec3& startPoing, const glm::vec3& endPoint) = 0;
		//virtual void DrawCube(const glm::vec3& center, float halfLength) = 0;
		virtual void DrawSphere(const glm::vec3& center, float radius) = 0;
	};
}