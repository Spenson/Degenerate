#include "CameraManager.h"
#include <glm/glm.hpp>


FreeCameraManager* g_pFreeCamera = new FreeCameraManager();


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

//FreeCameraManager* FreeCameraManager::pManager = nullptr;


FreeCameraManager::FreeCameraManager()
{
	impl = new FreeCameraManagerImpl();
}


//FreeCameraManager* FreeCameraManager::GetCameraInstance()
//{
//	if (!pManager)
//	{
//		pManager = new FreeCameraManager();
//	}
//	return pManager;
//}

double FreeCameraManager::XChange(double newX)
{
	float diffX = 0.0f;
	if (impl->LastX != 0.0f)
		diffX = newX - impl->LastX;

	impl->LastX = newX;
	return diffX;
}

double FreeCameraManager::YChange(double newY)
{
	float diffY = 0.0f;
	if (impl->LastY != 0.0f)
		diffY = newY - impl->LastY;

	impl->LastY = newY;
	return diffY;
}

void FreeCameraManager::Pitch(float rotation)
{
	impl->pitch += rotation * impl->rotation_speed;
	if (impl->pitch > 89.0f)
		impl->pitch = 89.0f;
	if (impl->pitch < -89.0f)
		impl->pitch = -89.0f;
	impl->LockTarget = false;
	impl->UpdateFront();
}

void FreeCameraManager::Yaw(float rotation)
{
	impl->yaw += rotation * impl->rotation_speed;
	if (impl->yaw > 360)
		impl->yaw -= 360;
	if (impl->yaw < -360)
		impl->yaw += 360;
	impl->LockTarget = false;

	impl->UpdateFront();
}

float FreeCameraManager::Pitch()
{
	return impl->pitch;
}

float FreeCameraManager::Yaw()
{
	return impl->yaw;
}

void FreeCameraManager::Sensitivity(float sens)
{
	impl->rotation_speed = sens;

	if (impl->rotation_speed < 0.001f)
		impl->rotation_speed = 0.001f;
}
float FreeCameraManager::Sensitivity()
{
	return impl->rotation_speed;
}
void FreeCameraManager::Speed(float speed)
{
	impl->movement_speed = speed;
	if (impl->movement_speed < 0.001f)
		impl->movement_speed = 0.001f;
}
float FreeCameraManager::Speed()
{
	return impl->movement_speed;
}

void FreeCameraManager::Target(glm::vec3* target)
{
	impl->LockTarget = true;
	impl->target = *target;
}

void FreeCameraManager::Target(glm::vec3 target)
{
	impl->LockTarget = true;
	impl->target = target;
}

glm::vec3 FreeCameraManager::Target()
{
	return impl->target;
}

bool FreeCameraManager::LockTarget()
{
	return impl->LockTarget;
}

void FreeCameraManager::LockTarget(bool isOnTarget)
{
	impl->LockTarget = isOnTarget;
}

void FreeCameraManager::MoveForward(float distance)
{
	impl->cameraPos += (distance * impl->movement_speed) * impl->cameraFront;
}

void FreeCameraManager::MoveRight(float distance)
{
	impl->cameraPos += glm::normalize(glm::cross(impl->cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * (distance * impl->movement_speed);
}

void FreeCameraManager::MoveUp(float distance)
{
	impl->cameraPos.y += (distance * impl->movement_speed);
}

void FreeCameraManager::SetPosition(glm::vec3 position)
{
	impl->cameraPos = position;
}

glm::vec3 FreeCameraManager::GetTarget()
{

	if (!impl->LockTarget)
	{
		impl->target = impl->cameraFront + impl->cameraPos;
	}

	return impl->target;
}

glm::vec3 FreeCameraManager::GetPosition()
{
	return impl->cameraPos;
}

glm::vec3 FreeCameraManager::GetUpVector()
{
	return glm::vec3(0.0f, 1.0f, 0.0f);
}

