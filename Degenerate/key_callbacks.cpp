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
double lastCtrlXInput = -1.5;
extern float lastX, lastY;

bool isShiftKeyDownByAlone(int mods);
bool isCtrlKeyDownByAlone(int mods);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	const float CAMERASPEED = 0.5f;

	if (!isShiftKeyDownByAlone(mods) && !isCtrlKeyDownByAlone(mods))
	{

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

		if (key == GLFW_KEY_B)
		{
			//			// Shoot a bullet from the pirate ship
			//			// Find the pirate ship...
			//			// returns NULL (0) if we didn't find it.
			////			cGameObject* pShip = pFindObjectByFriendlyName("PirateShip");
			//			cGameObject* pShip = pFindObjectByFriendlyNameMap("PirateShip");
			//			// Maybe check to see if it returned something... 
			//
			//			// Find the sphere#2
			////			cGameObject* pBall = pFindObjectByFriendlyName("Sphere#2");
			//			cGameObject* pBall = pFindObjectByFriendlyNameMap("Sphere#2");
			//
			//			// Set the location velocity for sphere#2
			//			pBall->positionXYZ = pShip->positionXYZ;
			//			pBall->inverseMass = 1.0f;		// So it's updated
			//			// 20.0 units "to the right"
			//			// 30.0 units "up"
			//			pBall->velocity = glm::vec3(15.0f, 20.0f, 0.0f);
			//			pBall->accel = glm::vec3(0.0f, 0.0f, 0.0f);
			//			pBall->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
		}//if ( key == GLFW_KEY_B )

	}

	if (isShiftKeyDownByAlone(mods))
	{
		// move the light
		if (key == GLFW_KEY_A)
		{
			lightMan.GetLight(0)->Position.x -= CAMERASPEED;		// Move the camera -0.01f units

		}
		if (key == GLFW_KEY_D)
		{
			lightMan.GetLight(0)->Position.x += CAMERASPEED;		// Move the camera +0.01f units


		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			lightMan.GetLight(0)->Position.y -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			lightMan.GetLight(0)->Position.y += CAMERASPEED;		// Move the camera +0.01f units
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			lightMan.GetLight(0)->Position.z -= CAMERASPEED;		// Move the camera -0.01f units

		}
		if (key == GLFW_KEY_S)
		{
			lightMan.GetLight(0)->Position.z += CAMERASPEED;		// Move the camera +0.01f units
		}

		if (key == GLFW_KEY_1)
		{
			lightMan.GetLight(0)->ConstAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_2)
		{
			lightMan.GetLight(0)->ConstAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_3)
		{
			lightMan.GetLight(0)->LinearAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_4)
		{
			lightMan.GetLight(0)->LinearAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_5)
		{
			lightMan.GetLight(0)->QuadraticAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_6)
		{
			lightMan.GetLight(0)->QuadraticAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_V)
		{
			lightMan.GetLight(0)->SpotInnerAngle -= 0.1f;
		}
		if (key == GLFW_KEY_B)
		{
			lightMan.GetLight(0)->SpotInnerAngle += 0.1f;
		}
		if (key == GLFW_KEY_N)
		{
			lightMan.GetLight(0)->SpotOuterAngle -= 0.1f;
		}
		if (key == GLFW_KEY_M)
		{
			lightMan.GetLight(0)->SpotOuterAngle += 0.1f;
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


	// Moving the pirate ship in a certain direction
	if (isCtrlKeyDownByAlone(mods))
	{
		const float SHIP_SPEED_CHANGE = 0.01f;
		const float SHIP_ANGLE_CHANGE = 0.01f;



		if (key == GLFW_KEY_Z)
		{
			ReadGameObjectsFromFile("../assets/config/GameObjects.xml", ::g_vec_pGameObjects, true);
			std::vector<Light*> templights;
			ReadLightsFromFile("../assets/config/Lights.xml", templights, true);
			lightMan.GenerateLights(templights);
		}
		if (key == GLFW_KEY_X)
		{
			//std::cout << glfwGetTime() << std::endl;
			if (glfwGetTime() - lastCtrlXInput > 1.5)
			{
				if (!MouseActive)
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
					glfwSetCursorPos(window, lastX,lastY);
					glfwSetCursorPosCallback(window, mouse_callback);
					MouseActive = true;
				}
				else
				{
					glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
					glfwSetCursorPosCallback(window, NULL);
					MouseActive = false;
				}
				lastCtrlXInput = glfwGetTime();
			}
		}
		//cGameObject* pShip = pFindObjectByFriendlyName("PirateShip");
		//// Turn the ship around
		//if (key == GLFW_KEY_A)
		//{	// Left
		//	pShip->HACK_AngleAroundYAxis -= SHIP_ANGLE_CHANGE;
		//	pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
		//}
		//if (key == GLFW_KEY_D)
		//{	// Right
		//	pShip->HACK_AngleAroundYAxis += SHIP_ANGLE_CHANGE;
		//	pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
		//}
		//if (key == GLFW_KEY_W)
		//{	// Faster
		//	pShip->HACK_speed += SHIP_SPEED_CHANGE;
		//}
		//if (key == GLFW_KEY_S)
		//{	// Slower
		//	pShip->HACK_speed -= SHIP_SPEED_CHANGE;
		//}
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