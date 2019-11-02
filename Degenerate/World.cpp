#include "World.h"
#include "globals.h"
#include "Bomb.h"
#include "Bullets.h"
#include "LASER.h"
#include "Rocket.h"
#include <iostream>

size_t World::robotCount = 0;
size_t World::damageCount = 0;
std::vector<Robot*> World::robots;
std::vector<Damage*> World::damagepoints;

bool World::slightLineCheck;

glm::vec3 GroundCheck(glm::vec3 pointXYZ, GameObject* pB)
{

	Mesh mesh = mMeshes[pB->meshName];


	for (unsigned int triIndex = 0;
		 triIndex != mesh.vecTriangles.size();
		 triIndex++)
	{
		TriangleIndex& curTriangle = mesh.vecTriangles[triIndex];


		// Get the vertices of the triangle
		VertexPosNormTex triVert1 = mesh.vecVertices[curTriangle.a];
		VertexPosNormTex triVert2 = mesh.vecVertices[curTriangle.b];
		VertexPosNormTex triVert3 = mesh.vecVertices[curTriangle.c];

		glm::vec3 triVertPoint1;
		triVertPoint1.x = triVert1.pos.x;
		triVertPoint1.y = triVert1.pos.y;
		triVertPoint1.z = triVert1.pos.z;

		glm::vec3 triVertPoint2;
		triVertPoint2.x = triVert2.pos.x;
		triVertPoint2.y = triVert2.pos.y;
		triVertPoint2.z = triVert2.pos.z;

		glm::vec3 triVertPoint3;
		triVertPoint3.x = triVert3.pos.x;
		triVertPoint3.y = triVert3.pos.y;
		triVertPoint3.z = triVert3.pos.z;


		glm::vec3 triVertPoint1_y_is_zero = triVertPoint1;
		glm::vec3 triVertPoint2_y_is_zero = triVertPoint2;
		glm::vec3 triVertPoint3_y_is_zero = triVertPoint3;
		glm::vec3 testPoint_y_is_zero = pointXYZ;


		triVertPoint1_y_is_zero.y = 0.0f;
		triVertPoint2_y_is_zero.y = 0.0f;
		triVertPoint3_y_is_zero.y = 0.0f;
		testPoint_y_is_zero.y = 0.0f;

		glm::vec3 curClosetPoint_y_is_zero = pPhsyics->ClosestPtPointTriangle(testPoint_y_is_zero, triVertPoint1_y_is_zero, triVertPoint2_y_is_zero, triVertPoint3_y_is_zero);


		if (curClosetPoint_y_is_zero == testPoint_y_is_zero)
			return 	pPhsyics->ClosestPtPointTriangle(pointXYZ, triVertPoint1, triVertPoint2, triVertPoint3);;


	}
}

glm::vec3 World::GetTarget(glm::vec3 pos, glm::vec3 lastTarget, bool isSightLineTpye, bool lasttargetmiss)
{
	glm::vec3 target = glm::vec3(0.0f);
	if(!lasttargetmiss)
		for (size_t inner = 0; inner < robots.size(); ++inner)
		{
			if (lastTarget == robots[inner]->pGameObject->position && robots[inner]->health > 0.0f)
				lastTarget;
		}


	if (isSightLineTpye)
	{
		float LastClosest;
		if(lasttargetmiss)
			LastClosest = glm::distance(pos, lastTarget);
		else
			LastClosest = 0.0f;

		float NextClosest = FLT_MAX;
		size_t botsChecked = 0;

		while (botsChecked < robots.size())
		{
			// get next closest robot position as target
			for (size_t inner = 0; inner < robots.size(); ++inner)
			{
				if (pos == robots[inner]->pGameObject->position)
					continue;
				float dis = glm::distance(pos, robots[inner]->pGameObject->position);

				if (dis > LastClosest && dis < NextClosest)
				{
					if (robots[inner]->health > 0.0f)
					{
						target = robots[inner]->pGameObject->position;
						NextClosest = dis;
					}
				}
			}

			//start pos and direction
			glm::vec3 checkpoint = pos;
			glm::vec3 dir = glm::normalize(target - pos);
			float step = 0.2f;
			//loop check if hit ground
			while (step < glm::distance(target, checkpoint))
			{
				GameObject* areana = ::pFindObjectByFriendlyName("terrain");
				glm::vec3 ground = GroundCheck(checkpoint, areana);
				//std::cout << ground.y << ":" << checkpoint.y << std::endl;
				if (ground.y > checkpoint.y)
				{
					//std::cout << "HIT GROUND!" << std::endl;
					//set target to non for fail to hit
					target = glm::vec3(0.0f);
					break;
				}
				checkpoint += dir * step;
			}

			//std::cout << "AFTER LOOP : (" << target.x << ", " << target.y << ", " << target.z << ")" << std::endl;
			if (target.x != 0.0f || target.y != 0.0f || target.x != 0.0f)
				break;

			LastClosest = NextClosest;
			NextClosest = FLT_MAX;
			botsChecked++;
		}

	}
	else
	{
		float closest = FLT_MAX;

		for (size_t inner = 0; inner < robots.size(); ++inner)
		{
			if (pos == robots[inner]->pGameObject->position)
				continue;

			float dis = glm::distance(pos, robots[inner]->pGameObject->position);

			if (dis < closest)
			{
				if (robots[inner]->health > 0.0f)
				{
					target = robots[inner]->pGameObject->position;
					closest = dis;
				}
			}
		}

	}
	if (target.x != 0.0f || target.y != 0.0f || target.x != 0.0f)
		std::cout << "Target from: (" << pos.x << ", " << pos.y << ", " << pos.z << ")" << " to: (" << target.x << ", " << target.y << ", " << target.z << ")" << std::endl;
	else
		std::cout << "No sight line" << std::endl;

	return target;
}

glm::vec3 World::GetRandomPosition()
{
	float x = (float)((rand() % 256) - 128);
	float z = (float)((rand() % 256) - 128);

	return GroundCheck(
		glm::vec3(x, 100.0f, z),
		::pFindObjectByFriendlyName("terrain"));

}

void World::Update(double deltaTime)
{
	for (size_t idx = 0; idx < robots.size(); idx++)
	{
		if (robots[idx]->health > 0.0f)
		{
			robots[idx]->Update(deltaTime);
		}
		else
		{
			std::cout << robots[idx]->pGameObject->friendlyName << " is dead." << std::endl;
		}
	}
	for (size_t idx = 0; idx < damagepoints.size(); idx++)
	{
		damagepoints[idx]->Update(deltaTime);
	}

}

void World::makeRobots(size_t count)
{
	for (size_t idx = 0; idx < count; idx++)
	{
		Robot* robo = new Robot();
		robo->health = 1.0f;
		robo->pGameObject = new GameObject();
		robo->pGameObject->meshName = "robot";
		robo->pGameObject->friendlyName = "robot" + std::to_string(robotCount);
		robo->pGameObject->objectColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
		robo->pGameObject->specularColour = glm::vec4(1.0f);
		robo->pGameObject->scale = glm::vec3(40);
		robo->pGameObject->position = GetRandomPosition();
		robo->pGameObject->position.y += 3.0f;

		//iWeapon* weapon;
		int randWeapon = rand() % 100;
		if (randWeapon < 30)
		{
			std::cout << robo->pGameObject->friendlyName << " has bullets" << std::endl;
			Bullets* bill = new Bullets();
			bill->pGameObject = new GameObject();
			bill->pGameObject->meshName = "cube";
			bill->pGameObject->friendlyName = "weapon" + std::to_string(robotCount);
			bill->pGameObject->objectColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
			bill->pGameObject->specularColour = glm::vec4(1.0f);
			bill->pGameObject->scale = glm::vec3(1.0f);
			bill->pGameObject->position = robo->pGameObject->position;
			bill->pGameObject->position.y += 3.0f;
			robo->pWeapon = bill;
			g_vec_pGameObjects.push_back(bill->pGameObject);
		}
		else if (randWeapon < 30)
		{
			std::cout << robo->pGameObject->friendlyName << " has LASER" << std::endl;
			LASER* theLASER = new LASER();
			theLASER->pGameObject = new GameObject();
			theLASER->pGameObject->meshName = "cube";
			theLASER->pGameObject->friendlyName = "weapon" + std::to_string(robotCount);
			theLASER->pGameObject->objectColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
			theLASER->pGameObject->specularColour = glm::vec4(1.0f);
			theLASER->pGameObject->scale = glm::vec3(1.0f);
			theLASER->pGameObject->position = robo->pGameObject->position;
			theLASER->pGameObject->position.y += 3.0f;
			robo->pWeapon = theLASER;
			g_vec_pGameObjects.push_back(theLASER->pGameObject);
		}
		else if (randWeapon < 90)
		{
			std::cout << robo->pGameObject->friendlyName << " has Bomb" << std::endl;
			Bomb* daBomb = new Bomb();
			daBomb->pGameObject = new GameObject();
			daBomb->pGameObject->meshName = "cube";
			daBomb->pGameObject->friendlyName = "weapon" + std::to_string(robotCount);
			daBomb->pGameObject->objectColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
			daBomb->pGameObject->specularColour = glm::vec4(1.0f);
			daBomb->pGameObject->scale = glm::vec3(1.0f);
			daBomb->pGameObject->position = robo->pGameObject->position;
			daBomb->pGameObject->position.y += 3.0f;
			robo->pWeapon = daBomb;
			g_vec_pGameObjects.push_back(daBomb->pGameObject);
		}
		else if (randWeapon < 100)
		{
			std::cout << robo->pGameObject->friendlyName << " has Bomb" << std::endl;
			Rocket* rocket = new Rocket();
			rocket->pGameObject = new GameObject();
			rocket->pGameObject->meshName = "cube";
			rocket->pGameObject->friendlyName = "weapon" + std::to_string(robotCount);
			rocket->pGameObject->objectColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
			rocket->pGameObject->specularColour = glm::vec4(1.0f);
			rocket->pGameObject->scale = glm::vec3(1.0f);
			rocket->pGameObject->position = robo->pGameObject->position;
			rocket->pGameObject->position.y += 3.0f;
			robo->pWeapon = rocket;
			g_vec_pGameObjects.push_back(rocket->pGameObject);
		}

		//Fire on first frame
		robo->TimeSinceShot = robo->pWeapon->ReloadTime() - 0.1f;

		g_vec_pGameObjects.push_back(robo->pGameObject);
		robots.push_back(robo);
		robotCount++;
	}
}

void World::DealDamage(glm::vec3 at, float radius, float amount)
{
	Damage* dam = new Damage();
	dam->pGameObject = new GameObject();
	dam->pGameObject->meshName = "sphere";
	dam->pGameObject->friendlyName = "damage" + std::to_string(damageCount);
	dam->pGameObject->objectColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	dam->pGameObject->specularColour = glm::vec4(1.0f);
	dam->pGameObject->scale = glm::vec3(radius);
	dam->pGameObject->position = at;
	//dam->pGameObject->isVisible = true;
	damagepoints.push_back(dam);
	::g_vec_pGameObjects.push_back(dam->pGameObject);
	damageCount++;

	for (size_t idx = 0; idx < robots.size(); ++idx)
	{
		if (glm::distance(at, robots[idx]->pGameObject->position) <= radius)
		{
			robots[idx]->health -= amount;
			std::cout << robots[idx]->pGameObject->friendlyName << " takes " << amount * 100 << "% damage. " << robots[idx]->health * 100 << " Remaining." << std::endl;
		}
	}

}



