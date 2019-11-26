#pragma once

#include "../globals.h"
#include "../ModelStuff/cModelLoader.h"

//#include "../GameObject/cGameObject.h"
//#include "../Lighting/LightManager.h"



void LoadMeshesFromXMLFile(std::string File, std::string MeshDir, std::map<std::string, cMesh>& mapMeshes, cModelLoader* modelLoader);
void LoadTexturesFromFile(std::string File, cBasicTextureManager* TextureManager);

void LoadGameObjectsFromXMLFile(std::string File, std::vector<cGameObject*>& vecGameObjects, bool clearExistingObjects = 1);
void SaveGameObjectsToXMLFile(std::string File, std::vector<cGameObject*> vecGameObjects);

void LoadLightsFromXMLFile(std::string File, LightManager *g_pLightManager, bool clearExistingLights = 1);
void SaveLightsToXMLFile(std::string File, LightManager *g_pLightManager);

void LoadCamera(std::string File, FreeCameraManager* Camera);
void SaveCamera(std::string File, FreeCameraManager* Camera);
