#pragma once

#include "GameObject.h"
#include "Mesh.h"
#include "Light.h"
#include "cPhysics.h"
#include <vector>
#include <map>

// returns NULL (0) if we didn't find it.
GameObject* pFindObjectByFriendlyName(std::string name);
GameObject* pFindObjectByFriendlyNameMap(std::string name);

extern std::map<std::string, Mesh> mMeshes;
extern cPhysics* pPhsyics;
extern std::vector<GameObject*> g_vec_pGameObjects;
extern void DrawLine(glm::vec3 start, glm::vec3 end, float radius, glm::vec4 colour);
extern void DrawSphere(glm::vec3 pos, float radius, glm::vec4 colour);
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
//
extern bool bLightDebugSheresOn;
//extern bool g_LightFlicker;
//extern bool g_Drone;
//
//extern std::vector<Light*> g_fireFlyLights;