#pragma once

#include "Robot.h"
#include <vector>
#include "Damage.h"
glm::vec3 GroundCheck(glm::vec3 pointXYZ, GameObject* pB);
class World
{
	
public:
	static size_t robotCount;
	static size_t damageCount;
	static std::vector<Robot*> robots;
	static std::vector<Damage*> damagepoints;
	static void Update(double deltaTime);
	static void makeRobots(size_t count);
	static void DealDamage(glm::vec3 at, float radius, float amount);
	static glm::vec3 GetTarget(glm::vec3 pos, glm::vec3 lastTarget, bool isSightLineTpye, bool lasttargetmiss = false);
	static glm::vec3 GetRandomPosition();
	

	static bool slightLineCheck;
};