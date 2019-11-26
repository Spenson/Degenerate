#pragma once
#include "globals.h"

#include "VAOManager.h"
#include "ShaderManager.h"
#include "Texture/cBasicTextureManager.h"


void InitUniformLocations();

void SetUpTextureBindingsForObject(GameObject* pCurrentObject, GLint shaderProgID);

void DrawObject(glm::mat4 m, GameObject* pCurrentObject, GLint shaderProgID, VAOManager* pVAOManager);