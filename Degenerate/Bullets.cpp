#include "Bullets.h"
#include "World.h"
#include "globals.h"

void Bullets::SetPosition(glm::vec3 pos)
{
	pGameObject->position = pos;
}
glm::vec3 Bullets::GetPosition()
{
	return this->pGameObject->position;
}
float Bullets::ReloadTime()
{
	return 0.0f;
}

bool Bullets::IsSightLine()
{
	return true;
}

void Bullets::Shoot(glm::vec3 target)
{
	DrawLine(this->GetPosition(), target, 0.5, this->pGameObject->objectColour);

	World::DealDamage(target, 1, 0.02f);
}
