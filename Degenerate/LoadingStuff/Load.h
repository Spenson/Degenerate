#pragma once
#include "../Rendering/Renderer.h"
#include "../Physics/Physics.h"
#include "../GameObject/cPhysicsGameObject.h"


void LoadScene(std::string file, DegenRendering::cRenderer& renderer, DegenPhysics::iPhysicsWorld*& world, std::vector<cPhysicsGameObject*>& objects);
