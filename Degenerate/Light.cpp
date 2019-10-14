#include "Light.h"

Light::Light()
{

	Position = glm::vec3(0.0f);	
	Direction = glm::vec3(0.0f,-1.0f,0.0f);
	Diffuse = glm::vec3(1.0f);

	ConstAtten = 0.000001f;	//			// not really used (can turn off and on the light)
	LinearAtten = 0.0003f;
	QuadraticAtten = 0.0000001f;
	CutOffDistance = FLT_MAX;

	LightType lightType = POINT_LIGHT;

	SpotInnerAngle = 5.0f;	
	SpotOuterAngle = 10.0f;	

	isLightOn = false;


}

Light::~Light()
{
}
