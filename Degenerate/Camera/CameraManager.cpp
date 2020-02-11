#include "CameraManager.h"
#include <glm/glm.hpp>


FreeCamera* g_pFreeCamera = new FreeCamera();


class FreeCameraManagerImpl
{
public:
	float yaw;
	float pitch;
	float LastX;
	float LastY;
	float movement_speed;
	float rotation_speed;
	bool LockTarget;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 target;
	glm::vec3 up;
	FreeCameraManagerImpl()
	{
		this->yaw = 90.0f;
		this->pitch = 0.0f;
		this->movement_speed = 1.0f;
		this->rotation_speed = 0.05f;
		this->cameraPos = glm::vec3(0.0f);
		this->cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
		this->LockTarget = false;
		UpdateFront();
	}

	void UpdateFront()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
		front.y = sin(glm::radians(pitch));
		front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
		cameraFront = glm::normalize(front);
	}
};

//FreeCamera* FreeCamera::pManager = nullptr;


FreeCamera::FreeCamera()
{
	impl = new FreeCameraManagerImpl();
}


//FreeCamera* FreeCamera::GetCameraInstance()
//{
//	if (!pManager)
//	{
//		pManager = new FreeCamera();
//	}
//	return pManager;
//}

double FreeCamera::XChange(double newX)
{
	float diffX = 0.0f;
	if (impl->LastX != 0.0f)
		diffX = (float)newX - impl->LastX;

	impl->LastX = (float)newX;
	return diffX;
}

double FreeCamera::YChange(double newY)
{
	float diffY = 0.0f;
	if (impl->LastY != 0.0f)
		diffY = (float)newY - impl->LastY;

	impl->LastY = (float)newY;
	return diffY;
}

void FreeCamera::Pitch(float rotation)
{
	impl->pitch += rotation * impl->rotation_speed;
	if (impl->pitch > 89.0f)
		impl->pitch = 89.0f;
	if (impl->pitch < -89.0f)
		impl->pitch = -89.0f;
	impl->LockTarget = false;
	impl->UpdateFront();
}

void FreeCamera::Yaw(float rotation)
{
	impl->yaw += rotation * impl->rotation_speed;
	if (impl->yaw > 360)
		impl->yaw -= 360;
	if (impl->yaw < -360)
		impl->yaw += 360;
	impl->LockTarget = false;

	impl->UpdateFront();
}

float FreeCamera::Pitch()
{
	return impl->pitch;
}

float FreeCamera::Yaw()
{
	return impl->yaw;
}

void FreeCamera::Sensitivity(float sens)
{
	impl->rotation_speed = sens;

	if (impl->rotation_speed < 0.001f)
		impl->rotation_speed = 0.001f;
}
float FreeCamera::Sensitivity()
{
	return impl->rotation_speed;
}
void FreeCamera::Speed(float speed)
{
	impl->movement_speed = speed;
	if (impl->movement_speed < 0.001f)
		impl->movement_speed = 0.001f;
}
float FreeCamera::Speed()
{
	return impl->movement_speed;
}

void FreeCamera::Target(glm::vec3* target)
{
	impl->LockTarget = true;
	impl->target = *target;
}

void FreeCamera::Target(glm::vec3 target)
{
	impl->LockTarget = true;
	impl->target = target;
}

glm::vec3 FreeCamera::GetTarget()
{
	return impl->target;
}

void FreeCamera::UpVector(const glm::vec3& up)
{
	impl->up = up;
}

bool FreeCamera::LockTarget()
{
	return impl->LockTarget;
}

void FreeCamera::LockTarget(bool isOnTarget)
{
	impl->LockTarget = isOnTarget;
}

void FreeCamera::MoveForward(float distance)
{
	impl->cameraPos += (distance * impl->movement_speed) * impl->cameraFront;
}

void FreeCamera::MoveRight(float distance)
{
	impl->cameraPos += glm::normalize(glm::cross(impl->cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * (distance * impl->movement_speed);
}

void FreeCamera::MoveUp(float distance)
{
	impl->cameraPos.y += (distance * impl->movement_speed);
}

void FreeCamera::SetPosition(glm::vec3 position)
{
	impl->cameraPos = position;
}

glm::vec3 FreeCamera::Target()
{

	if (!impl->LockTarget)
	{
		impl->target = impl->cameraFront + impl->cameraPos;
	}

	return impl->target;
}

glm::vec3 FreeCamera::Position()
{
	return impl->cameraPos;
}

glm::vec3 FreeCamera::UpVector()
{
	return impl->up;
}

