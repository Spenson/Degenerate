#pragma once

#include "GameObject.h"
#include "Light.h"
#include <vector>

// returns NULL (0) if we didn't find it.
GameObject* pFindObjectByFriendlyName(std::string name);
GameObject* pFindObjectByFriendlyNameMap(std::string name);

//extern glm::vec3 sexyLightPosition;
//extern float sexyLightConstAtten;
//extern float sexyLightLinearAtten;
//extern float sexyLightQuadraticAtten;
//
//extern float sexyLightSpotInnerAngle;
//extern float sexyLightSpotOuterAngle;
//
//// This is a "normalized" direction
//// (i.e. the length is 1.0f)
//extern glm::vec3 sexyLightSpotDirection;

extern bool bLightDebugSheresOn;
extern bool g_LightFlicker;
extern bool g_Drone;

extern std::vector<Light*> g_fireFlyLights;