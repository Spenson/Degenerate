#pragma once

#include "GameObject.h"

class Projectile
{
	float radius;
	float damage;
public:
	GameObject* pGameObject;
	void Update(double deltaTime);
	Projectile(glm::vec3 target, float dam, float rad, bool isArch);
};