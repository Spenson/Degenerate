#include "Bomb.h"
#include "World.h"

void Bomb::SetPosition(glm::vec3 pos)
{
	pGameObject->position = pos;
}

glm::vec3 Bomb::GetPosition()
{
	return this->pGameObject->position;
}
float Bomb::ReloadTime()
{
	return 5.0f;
}

bool Bomb::IsSightLine()
{
	return false;
}

void Bomb::Shoot(glm::vec3 target)
{
	World::DealDamage(target, 5, 0.25f);
}

