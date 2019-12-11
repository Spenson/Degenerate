#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera()
{
	m_pPlayerObject = g_vec_pGameObjects[0];
	m_ReletivePosition = glm::vec3(0.0f, 2.0f, -10.0f);
	m_ReletiveTarget = glm::vec3(0.0f, 1.0f, 0.0f);
	m_UpVector = glm::vec3(0.0f, 1.0f, 0.0f);
}

void ThirdPersonCamera::SetPlayerObject(cGameObject* m_pGO)
{
	m_pPlayerObject = m_pGO;
}

void ThirdPersonCamera::SetPositionRelitiveToObject(glm::vec3 pos)
{
	m_ReletivePosition = pos;
}

void ThirdPersonCamera::SetTargetRelitiveToObject(glm::vec3 tar)
{
	m_ReletiveTarget = tar;
}

void ThirdPersonCamera::SetUpVector(glm::vec3 up)
{
	m_UpVector = up;
}

glm::vec3 ThirdPersonCamera::Position()
{
	glm::vec3 pos = glm::mat4(m_pPlayerObject->getQOrientation()) * glm::vec4(m_ReletivePosition, 1.0f);

	pos += m_pPlayerObject->positionXYZ;

	return pos;
}

glm::vec3 ThirdPersonCamera::Target()
{
	glm::vec3 tar = glm::mat4(m_pPlayerObject->getQOrientation()) * glm::vec4(m_ReletiveTarget, 1.0f);

	tar += m_pPlayerObject->positionXYZ;

	return tar;
}

glm::vec3 ThirdPersonCamera::UpVector()
{
	glm::vec3 up = glm::mat4(m_pPlayerObject->getQOrientation()) * glm::vec4(m_UpVector, 1.0f);

	return up;
}
