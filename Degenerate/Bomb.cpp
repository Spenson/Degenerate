#include "Bomb.h"
#include "World.h"
#include "globals.h"

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
	float vel;
	glm::vec3 dir;
	if (target == lastHitTarget)
	{
		vel = lastVelocity;
	}
	else
	{
		vel = 5.0f;
	}

	dir = target - this->pGameObject->position;
	dir = glm::normalize(dir);
	dir.y = vel;
	glm::vec3 pos = this->GetPosition();
	GameObject* arena = ::pFindObjectByFriendlyName("terrain");
	glm::vec3 ground = GroundCheck(pos, arena);


	float gravity = 0.1f;
	while (ground.y < pos.y)
	{
		DrawSphere(pos, 1.0f, this->pGameObject->objectColour);
		pos += dir;
		dir.y -= gravity;
		//don't know why but crashes without this
		glm::vec3 temp = GroundCheck(pos, arena);
		ground = temp;
	}
	if (glm::distance(ground, target) < 5.0f)
	{
		lastHitTarget = target;
	}
	else if (glm::distance(ground, this->pGameObject->position) > glm::distance(this->pGameObject->position, target))
	{
		vel *= 0.9;
	}
	else if (glm::distance(ground, this->pGameObject->position) < glm::distance(this->pGameObject->position, target))
	{
		vel *= 1.1;
	}
	lastVelocity = vel;

	World::DealDamage(ground, 5.0f, 0.25f);

}

