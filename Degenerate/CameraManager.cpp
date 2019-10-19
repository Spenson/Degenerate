#include "CameraManager.h"
#include <glm/glm.hpp>


class CameraManagerImpl
{
public:
	float yaw;
	float pitch;
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 target;
	CameraManagerImpl()
	{
		yaw = 90.0f;
		pitch = 0.0f;
		cameraPos = glm::vec3(0.0f);
		cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);
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

CameraManager* CameraManager::pManager = nullptr;


CameraManager::CameraManager()
{
	impl = new CameraManagerImpl();
}


CameraManager* CameraManager::GetCameraInstance()
{
	if (!pManager)
	{
		pManager = new CameraManager();
	}
	return pManager;
}

void CameraManager::LookUp(float rotation)
{
	impl->pitch += rotation;
	if (impl->pitch > 89.0f)
		impl->pitch = 89.0f;
	if (impl->pitch < -89.0f)
		impl->pitch = -89.0f;

	impl->UpdateFront();
}

void CameraManager::LookRight(float rotation)
{
	impl->yaw += rotation;

	impl->UpdateFront();
}

void CameraManager::MoveForward(float distance)
{
	impl->cameraPos += distance * impl->cameraFront;
}

void CameraManager::MoveRight(float distance)
{
	impl->cameraPos += glm::normalize(glm::cross(impl->cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * distance;
}

void CameraManager::MoveUp(float distance)
{
	impl->cameraPos.y += distance;
}

void CameraManager::SetPosition(glm::vec3 position)
{
	impl->cameraPos = position;
}

glm::vec3 CameraManager::GetTarget()
{
	impl->target = impl->cameraFront + impl->cameraPos;
	return impl->cameraFront + impl->cameraPos;
}

glm::vec3 CameraManager::GetPosition()
{
	return impl->cameraPos;
}

glm::vec3 CameraManager::GetUpVector()
{
	return glm::vec3(0.0f, 1.0f, 0.0f);
}
