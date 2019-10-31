#pragma once
#include <glm/glm.hpp>


class CameraManagerImpl;

class CameraManager{
	CameraManagerImpl* impl;
	static CameraManager* pManager;
	CameraManager();

public:
	static CameraManager* GetCameraInstance();

	void Pitch(float rotation); //negitive for down
	void Yaw(float rotation); //negitive for left

	float Pitch(); //negitive for down
	float Yaw(); //negitive for left

	void SetTarget(glm::vec3 target);

	void MoveForward(float distance); // negitive for back
	void MoveRight(float distance); // negitive for left
	void MoveUp(float distance);// negitive for down

	void SetPosition(glm::vec3 position);

	glm::vec3 GetTarget();
	glm::vec3 GetPosition();
	glm::vec3 GetUpVector();
};