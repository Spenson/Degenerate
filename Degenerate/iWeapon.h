#pragma once
#include <glm/glm.hpp>


class iWeapon
{
public:
	virtual void SetPosition(glm::vec3 pos) = 0;
	virtual glm::vec3 GetPosition() = 0;
	virtual float ReloadTime() = 0;
	virtual bool IsSightLine() = 0;
	virtual void Shoot(glm::vec3 target) = 0;
};