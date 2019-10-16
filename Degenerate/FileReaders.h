#pragma once

#include "GameObject.h"
#include <vector>
void ReadGameObjectsFromFile(std::string File, std::vector<GameObject*>& vecGameObjects, bool clearExistingObjects = 1);
void WriteGameObjectsToFile(std::string File, std::vector<GameObject*> vecGameObjects);
void ReadLightsFromFile(std::string File, std::vector<Light*>& vecLights, bool clearExistingLights = 1);
void WriteLightsToFile(std::string File, std::vector<Light*> vecLights);
void ReadMeshesFromFile(std::string File, std::string MeshDir, std::map<std::string, Mesh>& mapMeshes, ModelLoader* modelLoader);