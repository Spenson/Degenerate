#pragma once

#include "GameObject.h"
#include <vector>
void ReadGameObjectsFromFile(std::string File, std::vector<GameObject*>& vecGameObjects, bool clearExistingObjects = 1);
void WriteGameObjectsToFile(std::string File, std::vector<GameObject*> vecGameObjects);
void ReadLightsFromFile(std::string File, std::vector<Light*>& lights, bool clearExistingLights = 1);
