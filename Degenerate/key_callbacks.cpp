#include "GLCommon.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>

#include "GFLW_callbacks.h"
#include "globals.h"			// for find object

#include "FileReaders.h"
#include "LightManager.h"
#include "CameraManager.h"

#include <stdio.h>		// for fprintf()
#include <vector>

extern std::vector<GameObject*> g_vec_pGameObjects;
extern LightManager lightMan;
bool MouseActive = false;
extern float lastX, lastY;
unsigned SelecetedLight = 0;
extern glm::mat4 calculateWorldMatrix(GameObject* pCurrentObject);

bool isShiftKeyDownByAlone(int mods);
bool isCtrlKeyDownByAlone(int mods);
float CAMERASPEED = 2.0f;

bool isDay = true;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	//float CAMERASPEED = 0.1f;
	//const float MOVEMENTSPEED = 0.2f;
	//const float MAXSPEED = 8.0f;

	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
	{

		if (key == GLFW_KEY_UP)
		{
			WriteCamera("../assets/config/Camera.xml");
		}
		if (key == GLFW_KEY_DOWN)
		{
			ReadCamera("../assets/config/Camera.xml");
		}
		//if (key == GLFW_KEY_LEFT)
		//{
		//	CAMERASPEED = 0.1f;
		//}
		//if (key == GLFW_KEY_RIGHT)
		//{
		//	CAMERASPEED = 2.0f;
		//}
		if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
		{
			if (isDay)
			{
				ReadLightsFromFile("../assets/config/Q3/Lights.xml", lightMan, true);

				for (size_t idx = 0; idx < 10; idx++)
				{
					g_fireFlyLights.push_back(lightMan.GetLight((lightMan.GetLightCount() - 1) - idx));

					g_fireFlyLights[idx]->Diffuse = glm::vec3(1.0f, 1.0f, 0.0f);
					g_fireFlyLights[idx]->Position = glm::vec3((rand() % 8) - 4, (rand() % 10) - 5, (rand() % 8) - 4) + glm::vec3(44, 75, -162);
					g_fireFlyLights[idx]->ConstAtten = 0.01;
					g_fireFlyLights[idx]->LinearAtten = 0.5f;
					g_fireFlyLights[idx]->QuadraticAtten = 0.5f;
					g_fireFlyLights[idx]->lightType = Light::POINT_LIGHT;
					g_fireFlyLights[idx]->isLightOn = 1;

				}

			}
			else
			{
				g_fireFlyLights.clear();
				ReadLightsFromFile("../assets/config/Q2/Lights.xml", lightMan, true);
			}
			::g_LightFlicker = !::g_LightFlicker;
			isDay = !isDay;
		}

		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			::g_Drone = false;
			ReadCamera("../assets/config/Q4/Camera1.xml");
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			::g_Drone = false;
			ReadCamera("../assets/config/Q4/Camera2.xml");
		}
		if (key == GLFW_KEY_3 && action == GLFW_PRESS)
		{
			::g_Drone = false;
			ReadCamera("../assets/config/Q4/Camera3.xml");
		}
		if (key == GLFW_KEY_4 && action == GLFW_PRESS)
		{
			::g_Drone = true;
		}
		if (key == GLFW_KEY_5 && action == GLFW_PRESS)
		{
			ReadCamera("../assets/config/Q7/Camera.xml");
		}



		// Move the camera (A & D for left and right, along the x axis)
		if (key == GLFW_KEY_A)
		{
			//cameraEye.x -= CAMERASPEED;		// Move the camera -0.01f units
			CameraManager::GetCameraInstance()->MoveRight(-CAMERASPEED);
		}
		if (key == GLFW_KEY_D)
		{
			//cameraEye.x += CAMERASPEED;		// Move the camera +0.01f units
			CameraManager::GetCameraInstance()->MoveRight(CAMERASPEED);
		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			//cameraEye.y -= CAMERASPEED;		// Move the camera -0.01f units
			CameraManager::GetCameraInstance()->MoveUp(CAMERASPEED);
		}
		if (key == GLFW_KEY_E)
		{
			//cameraEye.y += CAMERASPEED;		// Move the camera +0.01f units
			CameraManager::GetCameraInstance()->MoveUp(-CAMERASPEED);
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			//cameraEye.z -= CAMERASPEED;		// Move the camera -0.01f units
			CameraManager::GetCameraInstance()->MoveForward(CAMERASPEED);
		}
		if (key == GLFW_KEY_S)
		{
			//cameraEye.z += CAMERASPEED;		// Move the camera +0.01f units

			CameraManager::GetCameraInstance()->MoveForward(-CAMERASPEED);
		}



		/*	if (key == GLFW_KEY_1)
			{
				for (std::vector<GameObject*>::iterator it = ::g_vec_pGameObjects.begin(); it != g_vec_pGameObjects.end(); it++)
				{
					(*it)->isWireframe = false;
				}
			}
			if (key == GLFW_KEY_2)
			{
				for (std::vector<GameObject*>::iterator it = ::g_vec_pGameObjects.begin(); it != g_vec_pGameObjects.end(); it++)
				{
					(*it)->isWireframe = true;
				}

			}*/

	}
	///*  Comment Or Uncomment this line for light controls
	if (isShiftKeyDownByAlone(mods))
	{
		// move the light
		if (key == GLFW_KEY_A)
		{
			lightMan.GetLastLight()->Position.x -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_D)
		{
			lightMan.GetLastLight()->Position.x += CAMERASPEED;		// Move the camera +0.01f units
		}
		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			lightMan.GetLastLight()->Position.y -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			lightMan.GetLastLight()->Position.y += CAMERASPEED;		// Move the camera +0.01f units
		}
		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			lightMan.GetLastLight()->Position.z -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_S)
		{
			lightMan.GetLastLight()->Position.z += CAMERASPEED;		// Move the camera +0.01f units
		}
		if (key == GLFW_KEY_KP_4)
		{
			lightMan.GetLastLight()->Direction.x -= 0.01;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_KP_6)
		{
			lightMan.GetLastLight()->Direction.x += 0.01;		// Move the camera +0.01f units
		}
		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_KP_2)
		{
			lightMan.GetLastLight()->Direction.y -= 0.01;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_KP_8)
		{
			lightMan.GetLastLight()->Direction.y += 0.01;		// Move the camera +0.01f units
		}
		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_KP_7)
		{
			lightMan.GetLastLight()->Direction.z -= 0.01;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_KP_9)
		{
			lightMan.GetLastLight()->Direction.z += 0.01;		// Move the camera +0.01f units
		}
		if (key == GLFW_KEY_1)
		{
			lightMan.GetLastLight()->ConstAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_2)
		{
			lightMan.GetLastLight()->ConstAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_3)
		{
			lightMan.GetLastLight()->LinearAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_4)
		{
			lightMan.GetLastLight()->LinearAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_5)
		{
			lightMan.GetLastLight()->QuadraticAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_6)
		{
			lightMan.GetLastLight()->QuadraticAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_V)
		{
			lightMan.GetLastLight()->SpotInnerAngle -= 0.1f;
		}
		if (key == GLFW_KEY_B)
		{
			lightMan.GetLastLight()->SpotInnerAngle += 0.1f;
		}
		if (key == GLFW_KEY_N)
		{
			lightMan.GetLastLight()->SpotOuterAngle -= 0.1f;
		}
		if (key == GLFW_KEY_M)
		{
			lightMan.GetLastLight()->SpotOuterAngle += 0.1f;
		}
		if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
		{
			SelecetedLight++;
			if (SelecetedLight == lightMan.GetLightCount())
			{
				SelecetedLight = 0;
			}
			lightMan.GetLight(SelecetedLight);
		}
		if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
		{
			SelecetedLight--;
			if (SelecetedLight == -1)
			{
				SelecetedLight += lightMan.GetLightCount();
			}
			lightMan.GetLight(SelecetedLight);
		}
		if (key == GLFW_KEY_7)
		{
			lightMan.GetLastLight()->isLightOn = false;
		}
		if (key == GLFW_KEY_8)
		{
			lightMan.GetLastLight()->isLightOn = true;
		}
		if (key == GLFW_KEY_9)
		{
			bLightDebugSheresOn = false;
		}
		if (key == GLFW_KEY_0)
		{
			bLightDebugSheresOn = true;
		}
	}//if (isShiftKeyDownByAlone(mods))

	//*/

	// Moving the pirate ship in a certain direction
	if (isCtrlKeyDownByAlone(mods))
	{

		if (key == GLFW_KEY_Z)
		{
			ReadGameObjectsFromFile("../assets/config/GameObjects.xml", ::g_vec_pGameObjects, true);
			/*for (unsigned int index = 0;
				 index != ::g_vec_pGameObjects.size(); index++)
			{
				if (::g_vec_pGameObjects[index]->physicsShapeType == MESH)
				{
					::g_vec_pGameObjects[index]->matWorld = calculateWorldMatrix(::g_vec_pGameObjects[index]);
				}
			}*/
			//std::vector<Light*> templights;
			//ReadLightsFromFile("../assets/config/Lights.xml", lightMan, true);
			//lightMan.GenerateLights(templights);
		}
		if (key == GLFW_KEY_X && action == GLFW_PRESS)
		{
			if (!MouseActive)
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				glfwSetCursorPos(window, lastX, lastY);
				glfwSetCursorPosCallback(window, mouse_callback);
				MouseActive = true;
			}
			else
			{
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				glfwSetCursorPosCallback(window, NULL);
				MouseActive = false;
			}
		}

	}




	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

}




bool isShiftKeyDownByAlone(int mods)
{
	if (mods == GLFW_MOD_SHIFT)
	{
		// Shift key is down all by itself
		return true;
	}
	//// Ignore other keys and see if the shift key is down
	//if ((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)
	//{

	//}
	return false;
}

bool isCtrlKeyDownByAlone(int mods)
{
	if (mods == GLFW_MOD_CONTROL)
	{
		return true;
	}
	return false;
}