#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera()
{
	mPlayerObject = g_vec_pGameObjects[0];
	mReletivePosition = glm::vec3(0.0f, 2.0f, -10.0f);
	mReletiveTarget = glm::vec3(0.0f, 1.0f, 0.0f);
	mUpVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

void ThirdPersonCamera::SetPlayerObject(cGameObject* m_pGO)
{
	mPlayerObject = m_pGO;
}

void ThirdPersonCamera::SetPositionRelitiveToObject(glm::vec3 pos)
{
	mReletivePosition = pos;
}

void ThirdPersonCamera::SetTargetRelitiveToObject(glm::vec3 tar)
{
	mReletiveTarget = tar;
}

void ThirdPersonCamera::SetUpVector(glm::vec3 up)
{
	mUpVector = up;
}

glm::vec3 ThirdPersonCamera::Position()
{
	glm::vec3 pos = glm::mat4(mPlayerObject->getQOrientation()) * glm::vec4(mReletivePosition, 1.0f);

	pos += mPlayerObject->positionXYZ;

	return pos;
}

glm::vec3 ThirdPersonCamera::Target()
{
	glm::vec3 tar = glm::mat4(mPlayerObject->getQOrientation()) * glm::vec4(mReletiveTarget, 1.0f);

	tar += mPlayerObject->positionXYZ;

	return tar;
}

glm::vec3 ThirdPersonCamera::UpVector()
{
	glm::vec3 up = glm::mat4(mPlayerObject->getQOrientation()) * glm::vec4(mUpVector, 1.0f);

	return up;
}
