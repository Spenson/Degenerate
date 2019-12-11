//#include "GLCommon.h"
//#include <glm/glm.hpp>
//#include <glm/vec3.hpp>
////#include <glm/vec4.hpp>
//
//#include "GFLW_callbacks.h"
//#include "globals.h"			// for find m_pGO
//
//#include "Camera/FreeCameraManager.h"
//
////#include <stdio.h>		// for fprintf()
//
//void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
//{
//	// Move the sphere to where the camera is and shoot the ball from there...
//
//	//GameObject* pTheBall = pFindObjectByFriendlyName("Sphere#1");
//
//	//// What's the velocity
//	//// Target - eye = direction
//	//glm::vec3 direction = glm::normalize(cameraTarget - cameraEye);
//
//	//float speed = 10.0f;
//
//	//pTheBall->velocity = direction * speed;
//	//pTheBall->positionXYZ = cameraEye;
//
//	return;
//}
//
//bool firstMouse = true;
//float lastX, lastY;
//
//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos;
//	lastX = xpos;
//	lastY = ypos;
//
//	float sensitivity = 0.05;
//	xoffset *= sensitivity;
//	yoffset *= sensitivity;
//
//	FreeCameraManager::GetCameraInstance()->Pitch(yoffset);
//	FreeCameraManager::GetCameraInstance()->Yaw(xoffset);
//
//}
