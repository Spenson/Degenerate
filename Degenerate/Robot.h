#pragma once
#include "GameObject.h"
#include "iWeapon.h"

class Robot
{
	glm::vec3 lastTarget;
public:
	GameObject* pGameObject;
	double TimeSinceShot;
	float health;
	iWeapon* pWeapon;
	void Update(double deltaTime);

};