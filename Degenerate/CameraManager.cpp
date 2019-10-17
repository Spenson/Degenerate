#include "CameraManager.h"
#include <glm/glm.hpp>

CameraManager* CameraManager::pManager = nullptr;


CameraManager::CameraManager()
{
	yaw = 0;
	pitch = 0;
	cameraPos = glm::vec3(0.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);

}

void CameraManager::UpdateFront()
{
	glm::vec3 front;
	front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.y = sin(glm::radians(pitch));
	front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	cameraFront = glm::normalize(front);
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
	pitch += rotation;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	UpdateFront();
}

void CameraManager::LookRight(float rotation)
{
	yaw += rotation;

	UpdateFront();
}

void CameraManager::MoveForward(float distance)
{
	cameraPos += distance * cameraFront;
}

void CameraManager::MoveRight(float distance)
{
	cameraPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * distance;
}

void CameraManager::MoveUp(float distance)
{
	cameraPos.y += distance;
}

void CameraManager::SetPosition(glm::vec3 position)
{
	cameraPos = position;
}

glm::vec3 CameraManager::GetTarget()
{
	return cameraFront + cameraPos;
}

glm::vec3 CameraManager::GetPosition()
{
	return cameraPos;
}

glm::vec3 CameraManager::GetUpVector()
{
	return glm::vec3(0.0f, 1.0f, 0.0f);
}
