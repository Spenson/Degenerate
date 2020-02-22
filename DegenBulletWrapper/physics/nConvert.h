#pragma once
/**
 * \file	nConvert.h
 * \path	D:\GDP\Degenerate\DegenBulletWrapper\physics
 * \brief	Utility file
 *
 * \desc	contains needed conversions from and to Bullet/GLM
 */

#include <glmCommon.hpp>
#include "bullet/btBulletDynamicsCommon.h"


namespace nConvert
{
	
	/**
	 * \method		ToBullet
	 * \fullname	nConvert::ToBullet
	 * \brief		vector 3 from glm to bullet
	 *
	 * \access		public 
	 * \return		btVector3
	 * \param		const glm::vec3 & vec
	 */
	inline btVector3 ToBullet(const glm::vec3& vec)
	{
		//return btVector3(vec.x, vec.y, vec.z);
		return {vec.x, vec.y, vec.z};
	}



	/**
	 * \method		ToGLM
	 * \fullname	nConvert::ToGLM
	 * \brief		transform matrix from bullet to glm
	 *
	 * \access		public 
	 * \return		void
	 * \param		const btTransform & transformIn
	 * \return		glm::mat4 & transformOut	
	 */
	inline void ToGLM(const btTransform& transformIn, glm::mat4& transformOut)
	{
		transformIn.getOpenGLMatrix(&transformOut[0][0]);
	}


	/**
	 * \method		ToGLM
	 * \fullname	nConvert::ToGLM
	 * \brief		vector 3 from bullet to glm
	 *
	 * \access		public 
	 * \return		glm::vec3
	 * \param		const btVector3 & vec
	 */
	inline glm::vec3 ToGLM(const btVector3& vec)
	{
		return glm::vec3(vec.getX(), vec.getY(), vec.getZ());
	}


}
