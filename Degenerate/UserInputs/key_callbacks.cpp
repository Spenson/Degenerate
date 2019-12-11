//#include "GLCommon.h"
//#include <glm/glm.hpp>
//#include <glm/vec3.hpp>
//#include <glm/vec4.hpp>
//#include <iostream>
//
//#include "GFLW_callbacks.h"
//#include "globals.h"			// for find m_pGO
//
//#include "FileReaders.h"
//#include "LightManager/LightManager.h"
//#include "Camera/FreeCameraManager.h"
//
//#include <stdio.h>		// for fprintf()
//#include <vector>
//
//extern std::vector<GameObject*> g_vec_pGameObjects;
//extern LightManager lightMan;
//bool MouseActive = false;
//extern float lastX, lastY;
//unsigned SelecetedLight = 0;
//extern glm::mat4 calculateWorldMatrix(GameObject* pCurrentObject);
//
//bool isShiftKeyDownByAlone(int mods);
//bool isCtrlKeyDownByAlone(int mods);
//
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//
//	const float CAMERASPEED = 0.5f;
//	const float MOVEMENTSPEED = 0.2f;
//	const float MAXSPEED = 8.0f;
//
//	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
//	{
//
//		if (key == GLFW_KEY_UP)
//		{
//
//			glm::vec3 balldir = FreeCameraManager::GetCameraInstance()->GetTarget() - FreeCameraManager::GetCameraInstance()->GetPosition();
//			balldir.y = 0;
//			balldir = glm::normalize(balldir);
//			//pFindObjectByFriendlyName("sphere1")->velocity = glm::vec3(0.0f, pFindObjectByFriendlyName("sphere1")->velocity.y, 0.0f);
//			pFindObjectByFriendlyName("sphere1")->velocity += (MOVEMENTSPEED * balldir);
//			if (glm::length(pFindObjectByFriendlyName("sphere1")->velocity) > MAXSPEED)
//			{
//				pFindObjectByFriendlyName("sphere1")->velocity = glm::normalize(pFindObjectByFriendlyName("sphere1")->velocity) * MAXSPEED;
//			}
//		}
//		if (key == GLFW_KEY_DOWN)
//		{
//				glm::vec3 balldir = FreeCameraManager::GetCameraInstance()->GetTarget() - FreeCameraManager::GetCameraInstance()->GetPosition();
//				balldir.y = 0;
//				balldir = glm::normalize(balldir);
//				//pFindObjectByFriendlyName("sphere1")->velocity = glm::vec3(0.0f, pFindObjectByFriendlyName("sphere1")->velocity.y, 0.0f);
//				pFindObjectByFriendlyName("sphere1")->velocity -= (MOVEMENTSPEED * balldir);
//				if (glm::length(pFindObjectByFriendlyName("sphere1")->velocity) > MAXSPEED)
//				{
//					pFindObjectByFriendlyName("sphere1")->velocity = glm::normalize(pFindObjectByFriendlyName("sphere1")->velocity) * MAXSPEED;
//				}
//		}
//		if (key == GLFW_KEY_LEFT)
//		{
//				glm::vec3 balldir = FreeCameraManager::GetCameraInstance()->GetTarget() - FreeCameraManager::GetCameraInstance()->GetPosition();
//				balldir.y = 0;
//				balldir = glm::normalize(glm::cross(balldir, glm::vec3(0.0f, 1.0f, 0.0f)));
//				//pFindObjectByFriendlyName("sphere1")->velocity = glm::vec3(0.0f, pFindObjectByFriendlyName("sphere1")->velocity.y, 0.0f);
//				pFindObjectByFriendlyName("sphere1")->velocity -= (MOVEMENTSPEED * balldir);
//				if (glm::length(pFindObjectByFriendlyName("sphere1")->velocity) > MAXSPEED)
//				{
//					pFindObjectByFriendlyName("sphere1")->velocity = glm::normalize(pFindObjectByFriendlyName("sphere1")->velocity) * MAXSPEED;
//				}
//		}
//		if (key == GLFW_KEY_RIGHT)
//		{
//				glm::vec3 balldir = FreeCameraManager::GetCameraInstance()->GetTarget() - FreeCameraManager::GetCameraInstance()->GetPosition();
//				balldir.y = 0;
//				balldir = glm::normalize(glm::cross(balldir, glm::vec3(0.0f, 1.0f, 0.0f)));
//				//pFindObjectByFriendlyName("sphere1")->velocity = glm::vec3(0.0f, pFindObjectByFriendlyName("sphere1")->velocity.y, 0.0f);
//				pFindObjectByFriendlyName("sphere1")->velocity += (MOVEMENTSPEED * balldir);
//				if (glm::length(pFindObjectByFriendlyName("sphere1")->velocity) > MAXSPEED)
//				{
//					pFindObjectByFriendlyName("sphere1")->velocity = glm::normalize(pFindObjectByFriendlyName("sphere1")->velocity) * MAXSPEED;
//				}
//		}
//
//
//
//		// Move the camera (A & D for left and right, along the x axis)
//		if (key == GLFW_KEY_A)
//		{
//			//cameraEye.x -= CAMERASPEED;		// Move the camera -0.01f units
//			FreeCameraManager::GetCameraInstance()->MoveRight(-CAMERASPEED);
//		}
//		if (key == GLFW_KEY_D)
//		{
//			//cameraEye.x += CAMERASPEED;		// Move the camera +0.01f units
//			FreeCameraManager::GetCameraInstance()->MoveRight(CAMERASPEED);
//		}
//
//		// Move the camera (Q & E for up and down, along the y axis)
//		if (key == GLFW_KEY_Q)
//		{
//			//cameraEye.y -= CAMERASPEED;		// Move the camera -0.01f units
//			FreeCameraManager::GetCameraInstance()->MoveUp(CAMERASPEED);
//		}
//		if (key == GLFW_KEY_E)
//		{
//			//cameraEye.y += CAMERASPEED;		// Move the camera +0.01f units
//			FreeCameraManager::GetCameraInstance()->MoveUp(-CAMERASPEED);
//		}
//
//		// Move the camera (W & S for towards and away, along the z axis)
//		if (key == GLFW_KEY_W)
//		{
//			//cameraEye.z -= CAMERASPEED;		// Move the camera -0.01f units
//			FreeCameraManager::GetCameraInstance()->MoveForward(CAMERASPEED);
//		}
//		if (key == GLFW_KEY_S)
//		{
//			//cameraEye.z += CAMERASPEED;		// Move the camera +0.01f units
//
//			FreeCameraManager::GetCameraInstance()->MoveForward(-CAMERASPEED);
//		}
//
//		if (key == GLFW_KEY_1)
//		{
//			for (std::vector<GameObject*>::iterator it = ::g_vec_pGameObjects.begin(); it != g_vec_pGameObjects.end(); it++)
//			{
//				(*it)->isWireframe = false;
//			}
//		}
//		if (key == GLFW_KEY_2)
//		{
//			for (std::vector<GameObject*>::iterator it = ::g_vec_pGameObjects.begin(); it != g_vec_pGameObjects.end(); it++)
//			{
//				(*it)->isWireframe = true;
//			}
//
//		}
//
//	}
//
//	if (isShiftKeyDownByAlone(mods))
//	{
//		// move the light
//		if (key == GLFW_KEY_A)
//		{
//			lightMan.GetLastLight()->Position.x -= CAMERASPEED;		// Move the camera -0.01f units
//
//		}
//		if (key == GLFW_KEY_D)
//		{
//			lightMan.GetLastLight()->Position.x += CAMERASPEED;		// Move the camera +0.01f units
//
//
//		}
//
//		// Move the camera (Q & E for up and down, along the y axis)
//		if (key == GLFW_KEY_Q)
//		{
//			lightMan.GetLastLight()->Position.y -= CAMERASPEED;		// Move the camera -0.01f units
//		}
//		if (key == GLFW_KEY_E)
//		{
//			lightMan.GetLastLight()->Position.y += CAMERASPEED;		// Move the camera +0.01f units
//		}
//
//		// Move the camera (W & S for towards and away, along the z axis)
//		if (key == GLFW_KEY_W)
//		{
//			lightMan.GetLastLight()->Position.z -= CAMERASPEED;		// Move the camera -0.01f units
//
//		}
//		if (key == GLFW_KEY_S)
//		{
//			lightMan.GetLastLight()->Position.z += CAMERASPEED;		// Move the camera +0.01f units
//		}
//
//		if (key == GLFW_KEY_1)
//		{
//			lightMan.GetLastLight()->ConstAtten *= 0.99f;			// 99% of what it was
//		}
//		if (key == GLFW_KEY_2)
//		{
//			lightMan.GetLastLight()->ConstAtten *= 1.01f;			// 1% more of what it was
//		}
//		if (key == GLFW_KEY_3)
//		{
//			lightMan.GetLastLight()->LinearAtten *= 0.99f;			// 99% of what it was
//		}
//		if (key == GLFW_KEY_4)
//		{
//			lightMan.GetLastLight()->LinearAtten *= 1.01f;			// 1% more of what it was
//		}
//		if (key == GLFW_KEY_5)
//		{
//			lightMan.GetLastLight()->QuadraticAtten *= 0.99f;			// 99% of what it was
//		}
//		if (key == GLFW_KEY_6)
//		{
//			lightMan.GetLastLight()->QuadraticAtten *= 1.01f;			// 1% more of what it was
//		}
//		if (key == GLFW_KEY_V)
//		{
//			lightMan.GetLastLight()->SpotInnerAngle -= 0.1f;
//		}
//		if (key == GLFW_KEY_B)
//		{
//			lightMan.GetLastLight()->SpotInnerAngle += 0.1f;
//		}
//		if (key == GLFW_KEY_N)
//		{
//			lightMan.GetLastLight()->SpotOuterAngle -= 0.1f;
//		}
//		if (key == GLFW_KEY_M)
//		{
//			lightMan.GetLastLight()->SpotOuterAngle += 0.1f;
//		}
//		if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
//		{
//
//			SelecetedLight++;
//			if (SelecetedLight == lightMan.GetLightCount())
//			{
//				SelecetedLight = 0;
//			}
//			lightMan.GetLight(SelecetedLight);
//
//		}
//		if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
//		{
//
//			SelecetedLight--;
//			if (SelecetedLight == -1)
//			{
//				SelecetedLight += lightMan.GetLightCount();
//			}
//			lightMan.GetLight(SelecetedLight);
//
//		}
//
//		if (key == GLFW_KEY_7)
//		{
//			lightMan.GetLastLight()->isLightOn = false;
//		}
//		if (key == GLFW_KEY_8)
//		{
//			lightMan.GetLastLight()->isLightOn = true;
//		}
//
//		if (key == GLFW_KEY_9)
//		{
//			bLightDebugSheresOn = false;
//		}
//		if (key == GLFW_KEY_0)
//		{
//			bLightDebugSheresOn = true;
//		}
//
//	}//if (isShiftKeyDownByAlone(mods))
//
//
//	// Moving the pirate ship in a certain direction
//	if (isCtrlKeyDownByAlone(mods))
//	{
//
//		if (key == GLFW_KEY_Z)
//		{
//			LoadGameObjectsFromXMLFile("../assets/config/GameObjects.xml", ::g_vec_pGameObjects, true);
//			for (unsigned int index = 0;
//				 index != ::g_vec_pGameObjects.size(); index++)
//			{
//				if (::g_vec_pGameObjects[index]->physicsShapeType == MESH)
//				{
//					::g_vec_pGameObjects[index]->matWorld = calculateWorldMatrix(::g_vec_pGameObjects[index]);
//				}
//			}
//			//std::vector<Light*> templights;
//			LoadLightsFromXMLFile("../assets/config/Lights.xml", lightMan, true);
//			//lightMan.GenerateLights(templights);
//		}
//		if (key == GLFW_KEY_X && action == GLFW_PRESS)
//		{
//			if (!MouseActive)
//			{
//				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//				glfwSetCursorPos(window, lastX, lastY);
//				glfwSetCursorPosCallback(window, mouse_callback);
//				MouseActive = true;
//			}
//			else
//			{
//				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
//				glfwSetCursorPosCallback(window, NULL);
//				MouseActive = false;
//			}
//
//		}
//
//	}
//
//
//
//
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GLFW_TRUE);
//
//}
//
//
//
//
//bool isShiftKeyDownByAlone(int mods)
//{
//	if (mods == GLFW_MOD_SHIFT)
//	{
//		// Shift key is down all by itself
//		return true;
//	}
//	//// Ignore other keys and see if the shift key is down
//	//if ((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
//	//{
//
//	//}
//	return false;
//}
//
//bool isCtrlKeyDownByAlone(int mods)
//{
//	if (mods == GLFW_MOD_CONTROL)
//	{
//		return true;
//	}
//	return false;
//}