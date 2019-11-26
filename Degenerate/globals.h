#pragma once

#include "GLCommon.h"

#include "GameObject.h"

#include "Texture/cBasicTextureManager.h"

// returns NULL (0) if we didn't find it.
GameObject* pFindObjectByFriendlyName(std::string name);
GameObject* pFindObjectByFriendlyNameMap(std::string name);


extern cBasicTextureManager* g_pTextureManager;
extern GLuint shaderProgID;
extern GLint eyeLocation_UL;
extern GLint matView_UL;
extern GLint matProj_UL;
extern bool bLightDebugSheresOn;

//extern GLint matModel_UL;
//extern GLint matModelIT_UL;
//extern GLint diffuseColour_UL;
//extern GLint specularColour_UL;
//extern GLint debugColour_UL;
//extern GLint bDoNotLight_UL;
//extern GLint newColour_location;



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

