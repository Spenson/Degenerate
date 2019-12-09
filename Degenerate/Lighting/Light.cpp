#include "Light.h"

Light::Light() :
	Position(glm::vec3(0.0f)), Direction(glm::vec3(0.0f, -1.0f, 0.0f)), matrix(glm::mat4(1.0f)),
	Diffuse(glm::vec3(1.0f)), Specular(glm::vec4(1.0f)),
	ConstAtten(0.0f), LinearAtten(0.0003f), QuadraticAtten(0.0000001f), CutOffDistance(FLT_MAX),
	lightType(POINT_LIGHT), SpotInnerAngle(5.0f), SpotOuterAngle(10.0f), 
	isLightOn(false)
{

	//Position = glm::vec3(0.0f);	
	//Direction = glm::vec3(0.0f,-1.0f,0.0f);
	//Diffuse = glm::vec3(1.0f);
	//Specular = glm::vec4(1.0f);
	////Rotation = glm::vec3(0.0f);
	//matrix = glm::mat4(1.0f);

	//ConstAtten = 0.0f;	
	//LinearAtten = 0.0003f;
	//QuadraticAtten = 0.0000001f;
	//CutOffDistance = FLT_MAX;

	//lightType = POINT_LIGHT;

	//SpotInnerAngle = 5.0f;
	//SpotOuterAngle = 10.0f;

	//isLightOn = false;


}

Light::~Light()
{
}
