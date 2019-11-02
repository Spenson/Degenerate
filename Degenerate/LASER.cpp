#include "LASER.h"
#include "World.h"
#include "globals.h"

void LASER::SetPosition(glm::vec3 pos)
{
	pGameObject->position = pos;
}

glm::vec3 LASER::GetPosition()
{
	return this->pGameObject->position;
}

float LASER::ReloadTime()
{
	return 1.0f;
}

bool LASER::IsSightLine()
{
	return true;
}

void LASER::Shoot(glm::vec3 target)
{
	DrawLine(this->GetPosition(), target, 0.5, this->pGameObject->objectColour);
	World::DealDamage(target, 1, 0.04f);
}
