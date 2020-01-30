#pragma once

#include "GLCommon.h"
#include "GameObject/cGameObject.h"
#include "Camera/CameraManager.h"
#include "Rendering/Texture/cBasicTextureManager.h"
#include "Rendering/Lighting/LightManager.h"

//extern cBasicTextureManager* g_pTextureManager;
extern std::vector<cGameObject*> g_vec_pGameObjects;
//extern LightManager* g_pLightManager;
extern FreeCamera* g_pFreeCamera;
extern bool lockToShip;


//glm::mat4 calculateWorldMatrix(cGameObject* pCurrentObject, glm::mat4 matWorld = glm::mat4(1.0f));