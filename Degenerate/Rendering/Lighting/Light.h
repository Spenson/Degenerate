#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	Light();
	virtual ~Light();

	//glm::vec3 Rotation; // Euler Degree will convert to quat
	glm::mat4 matrix;
	glm::vec3 Direction; 
	glm::vec3 Position;
	glm::vec3 Diffuse;
	glm::vec4 Specular;

	float ConstAtten;	
	float LinearAtten;	
	float QuadraticAtten;	
	float CutOffDistance;

	//vec4 param1;			// x = lightType, y = inner angle, z = outer angle, w = TBD					
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


};