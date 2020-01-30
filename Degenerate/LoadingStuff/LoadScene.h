#pragma once


#include "../globals.h"

#include "../Rendering/VAOManager/cVAOManager.h"
#include "../Rendering/ModelStuff/cModelLoader.h"

void TestLoad(cVAOManager* pTheVAOManager, cModelLoader* pTheModelLoader, GLuint shaderProgID, 
			  iDebugRenderer* pDebugRenderer, std::vector<cGameObject*>& vec_pGameObjects, 
			  LightManager* pLightManager, cBasicTextureManager* pTextureManager);