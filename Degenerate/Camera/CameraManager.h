#pragma once
#include <glm/glm.hpp>


class CameraManagerImpl;

class CameraManager{
	CameraManagerImpl* impl;
	static CameraManager* pManager;
	CameraManager();

public:
	static CameraManager* GetCameraInstance();

	void LookUp(float rotation); //negitive for down
	void LookRight(float rotation); //negitive for left

	void MoveForward(float distance); // negitive for back
	void MoveRight(float distance); // negitive for left
	void MoveUp(float distance);// negitive for down

	void SetPosition(glm::vec3 position);

	glm::vec3 GetTarget();
	glm::vec3 GetPosition();
	glm::vec3 GetUpVector();
};