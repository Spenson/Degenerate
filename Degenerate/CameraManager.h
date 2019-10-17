#pragma once
#include <glm/glm.hpp>

class CameraManager{
	float yaw;
	float pitch;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	static CameraManager* pManager;
	CameraManager();

	void UpdateFront();
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