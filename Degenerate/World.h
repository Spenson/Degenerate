#pragma once

#include "Robot.h"
#include <vector>
#include "Damage.h"
#include "Projectile.h"

class World
{
public:
	static size_t robotCount;
	static size_t damageCount;
	static size_t projectileCount;
	static std::vector<Robot*> robots;
	static std::vector<Damage*> damagepoints;
	static std::vector<Projectile*> projectiles;
	static void Update(double deltaTime);
	static void makeRobots(size_t count);
	static void DealDamage(glm::vec3 at, float radius, float amount);
	static glm::vec3 GetTarget(glm::vec3 pos, bool isSightLineTpye);
	static glm::vec3 GetRandomPosition();
};