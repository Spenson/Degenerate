#pragma once

#include "GameObject.h"
#include "LightManager/LightManager.h"
#include "ModelLoader.h"
#include <vector>
#include <map>

void ReadGameObjectsFromFile(std::string File, std::vector<GameObject*>& vecGameObjects, bool clearExistingObjects = 1);
void WriteGameObjectsToFile(std::string File, std::vector<GameObject*> vecGameObjects);
void ReadLightsFromFile(std::string File, LightManager& lightMan, bool clearExistingLights = 1);
void WriteLightsToFile(std::string File, LightManager lightMan);
void ReadMeshesFromFile(std::string File, std::string MeshDir, std::map<std::string, Mesh>& mapMeshes, ModelLoader* modelLoader);