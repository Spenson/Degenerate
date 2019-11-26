#pragma once


#include "../globals.h"

#include "../VAOManager/cVAOManager.h"
#include "../ModelStuff/cModelLoader.h"

void TestLoad(cVAOManager* pTheVAOManager, cModelLoader* pTheModelLoader, GLuint shaderProgID, 
			  iDebugRenderer* pDebugRenderer, std::vector<cGameObject*>& vec_pGameObjects, 
			  LightManager* pLightManager, cBasicTextureManager* pTextureManager);