#pragma once
#include "../globals.h"
#include "../GameObject/cGameObject.h"
#include "../VAOManager/cVAOManager.h"

void DrawObject(glm::mat4 matModel, cGameObject* pCurrentObject, GLint shaderProgID, cVAOManager* pVAOManager);
void SetUpTextureBindingsForObject(cGameObject* pCurrentObject, GLint shaderProgID);