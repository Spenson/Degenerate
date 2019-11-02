#include "Robot.h"
#include "World.h"

#include <iostream>


void Robot::Update(double deltaTime)
{
	std::cout << this->pGameObject->friendlyName << "'s Turn" << std::endl;
	TimeSinceShot += deltaTime;

	//darken as dying
	if (health > 0.0f)
		this->pGameObject->objectColour = glm::vec4(0.0f, 0.0f, health, 1.0f);
	else
		this->pGameObject->objectColour = glm::vec4(0.7f, 0.7f, 0.7f, 1.0f);


	if (TimeSinceShot > pWeapon->ReloadTime())
	{
		std::cout << this->pGameObject->friendlyName << " Looks for target" << std::endl;
		glm::vec3 target = World::GetTarget(this->pGameObject->position, lastTarget, pWeapon->IsSightLine(), pWeapon->LastTargetUnreachable());
		while (target == glm::vec3(0.0f))
		{
			this->pGameObject->position = World::GetRandomPosition();
			this->pGameObject->position += 3.0f;
			lastTarget == glm::vec3(-100.0);
			std::cout << this->pGameObject->friendlyName << " teleports to (" << this->pGameObject->position.x << ", " << this->pGameObject->position.y << ", " << this->pGameObject->position.z << ")" << std::endl;

			this->pWeapon->SetPosition(glm::vec3(this->pGameObject->position.x, this->pGameObject->position.y + 3.0f, this->pGameObject->position.z));

			std::cout << this->pGameObject->friendlyName << " Looks for target" << std::endl;

			target = World::GetTarget(this->pGameObject->position, lastTarget, pWeapon->IsSightLine());
		}
		std::cout << this->pGameObject->friendlyName << " Shoots" << std::endl;
		pWeapon->Shoot(target);
		lastTarget = target;
		TimeSinceShot = 0.0f;
	}
	else
	{
		std::cout << this->pGameObject->friendlyName << " time to reload: " << pWeapon->ReloadTime() - TimeSinceShot << std::endl;

	}
}
