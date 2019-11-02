#pragma once
#include "iWeapon.h"
#include "GameObject.h"

class Bomb : public iWeapon
{
public:
	GameObject* pGameObject;

	virtual void SetPosition(glm::vec3 pos);
	virtual glm::vec3 GetPosition();
	virtual float ReloadTime();
	virtual bool IsSightLine();
	virtual void Shoot(glm::vec3 target);
};
