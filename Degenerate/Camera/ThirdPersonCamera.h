#pragma once
#include "../globals.h"


class ThirdPersonCamera
{
	cGameObject* m_pPlayerObject;
	glm::vec3 m_ReletivePosition;
	glm::vec3 m_ReletiveTarget;
	glm::vec3 m_UpVector;

public:
	ThirdPersonCamera();
	void SetPlayerObject(cGameObject* m_pGO);
	void SetPositionRelitiveToObject(glm::vec3 pos);
	void SetTargetRelitiveToObject(glm::vec3 tar);
	void SetUpVector(glm::vec3 up);

	glm::vec3 Position();
	glm::vec3 Target();

	
	glm::vec3 UpVector();
};