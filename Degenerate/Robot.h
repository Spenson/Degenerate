#pragma once
#include "GameObject.h"
#include "iWeapon.h"

class Robot
{
public:
	GameObject* pGameObject;
	double TimeSinceShot;
	float health;
	iWeapon* pWeapon;
	void Update(double deltaTime);

};