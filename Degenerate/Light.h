#pragma once

#include <glm/glm.hpp>

class Light
{
public:

	Light();
	virtual ~Light();
	//vec4 position;	
	glm::vec3 Position;		// = glm::vec3(-25.0f, 30.0f, 0.0f);
	// This is a "normalized" direction
	// (i.e. the length is 1.0f)
	//vec4 direction;
	glm::vec3 Direction;	// = glm::vec3(0.0f, -1.0f, 0.0f);
	//vec4 diffuse;	
	glm::vec3 Diffuse;

	glm::vec4 Specular;

	//vec4 atten;	
	float ConstAtten;		// = 0.000001f;			// not really used (can turn off and on the light)
	float LinearAtten;		// = 0.0003f;
	float QuadraticAtten;	// = 0.0000001f;
	float CutOffDistance;

	//vec4 param1;			// x = lightType, y = inner angle, z = outer angle, w = TBD
							// 0 = pointlight
							// 1 = spot light
							// 2 = directional light
	enum LightType
	{
		POINT_LIGHT,
		SPOT_LIGHT,
		DIRECTIONAL_LIGHT
	};
	LightType lightType;

	float SpotInnerAngle;	// = 5.0f;
	float SpotOuterAngle;	// = 7.5f;

	//vec4 param2;			// x = 0 for off, 1 for on
	bool isLightOn;			// = 0;



private:

};