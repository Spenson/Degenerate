#include "Rocket.h"
#include "World.h"
#include "globals.h"

void Rocket::SetPosition(glm::vec3 pos)
{
	pGameObject->position = pos;
}

glm::vec3 Rocket::GetPosition()
{
	return this->pGameObject->position;
}

float Rocket::ReloadTime()
{
	return 10.0f;
}

bool Rocket::IsSightLine()
{
	return false;
}

void Rocket::Shoot(glm::vec3 target)
{
	glm::vec3 dir = target - this->pGameObject->position;
	dir = glm::normalize(dir);
	glm::vec3 pos = this->GetPosition();
	GameObject* arena = ::pFindObjectByFriendlyName("terrain");
	glm::vec3 ground = GroundCheck(pos, arena);
	while (ground.y < pos.y)
	{
		DrawSphere(pos, 1.0f, this->pGameObject->objectColour);
		pos += dir * 0.1f;
		//don't know why but crashes without this
		if (glm::distance(pos, target) <= 0.1)
		{
			World::DealDamage(target, 7.5f, 0.3);

			lasttargetunreachable = false;
		}
		glm::vec3 temp = GroundCheck(pos, arena);
		ground = temp;
	}
	World::DealDamage(ground, 7.5f, 0.3);
	lasttargetunreachable = true;

}
