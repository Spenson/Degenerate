#pragma once
#include "../globals.h"


class ThirdPersonCamera
{
	cGameObject* mPlayerObject;
	glm::vec3 mReletivePosition;
	glm::vec3 mReletiveTarget;
	glm::vec3 mUpVector;

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