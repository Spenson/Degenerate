#pragma once

#include "../GLCommon.h"


namespace DegenRendering
{
	class iCamera
	{
	public:
		virtual ~iCamera() = default;
		virtual glm::vec3 Position() = 0;
		virtual glm::vec3 Target() = 0;
		virtual glm::vec3 UpVector() = 0;
	};
}