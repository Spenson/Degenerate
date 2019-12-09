#pragma once

#include "GLCommon.h"
#include "Texture/cBasicTextureManager.h"
#include "GameObject/cGameObject.h"
#include "Lighting/LightManager.h"
#include "Camera/CameraManager.h"

extern cBasicTextureManager* g_pTextureManager;
extern std::vector<cGameObject*> g_vec_pGameObjects;
extern LightManager* g_pLightManager;
extern FreeCameraManager* g_pFreeCamera;
extern bool lockToShip;


glm::mat4 calculateWorldMatrix(cGameObject* pCurrentObject, glm::mat4 matWorld = glm::mat4(1.0f));