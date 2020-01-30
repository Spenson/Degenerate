#pragma once

#include "../GLCommon.h"


namespace DegenRendering
{
	enum class LightType
	{
		POINT_LIGHT,
		SPOT_LIGHT,
		DIRECTIONAL_LIGHT
	};

	class iLight
	{
	public:
		virtual ~iLight() = default;

		virtual glm::vec4 GetTransform() = 0; //translate and rotate

		virtual glm::vec4 Diffuse() = 0;
		virtual glm::vec4 Specular() = 0;

		virtual float ConstAtten() = 0;
		virtual float LinearAtten() = 0;
		virtual float QuadraticAtten() = 0;
		virtual float CutOffDistance() = 0;

		virtual LightType Type() = 0;

		virtual float SpotInnerAngle() = 0;
		virtual float SpotOuterAngle() = 0;

		virtual bool TurnOn() = 0;

	};
}