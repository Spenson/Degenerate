#pragma once
#include <glmCommon.hpp>
#include "btBulletDynamicsCommon.h"


namespace nConvert
{
	
	inline btVector3 ToBullet(const glm::vec3& vec)
	{
		//return btVector3(vec.x, vec.y, vec.z);
		return {vec.x, vec.y, vec.z};
	}



	inline void ToGLM(const btTransform& transformIn, glm::mat4& transformOut)
	{
		transformIn.getOpenGLMatrix(&transformOut[0][0]);
	}
	inline glm::vec3 ToGLM(const btVector3& vec)
	{
		return glm::vec3(vec.getX(), vec.getY(), vec.getZ());
	}


}
