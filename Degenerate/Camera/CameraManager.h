#pragma once
#include <glm/glm.hpp>
#include "../Rendering/iCamera.h"


class FreeCameraManagerImpl;

class FreeCamera: public DegenRendering::iCamera
{
	FreeCameraManagerImpl* impl;
	//static FreeCamera* pManager;

public:
	FreeCamera();
	//static FreeCamera* GetCameraInstance();


	double XChange(double newX);
	double YChange(double newY);

	void Pitch(float rotation); //negitive for down
	void Yaw(float rotation); //negitive for left
	float Pitch(); //negitive for down
	float Yaw(); //negitive for left

	void Sensitivity(float sens);
	float Sensitivity();
	void Speed(float sens);
	float Speed();

	void Target(glm::vec3* target);
	void Target(glm::vec3 target);
	glm::vec3 GetTarget();

	void UpVector(const glm::vec3& up);

	bool LockTarget();
	void LockTarget(bool isOnTarget);

	void MoveForward(float distance); // negitive for back
	void MoveRight(float distance); // negitive for left
	void MoveUp(float distance);// negitive for down

	void SetPosition(glm::vec3 position);

	glm::vec3 Target() override;
	glm::vec3 Position() override;
	glm::vec3 UpVector() override;
};