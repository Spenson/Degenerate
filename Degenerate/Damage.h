#pragma once
#include "GameObject.h"

class Damage
{
public:
	double timeExisted = 0.0f;
	GameObject* pGameObject;
	void Update(double deltaTime);
};