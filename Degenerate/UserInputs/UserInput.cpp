#include "../globals.h"			// for find m_pGO

#include "GFLW_callbacks.h"
#include <stdio.h>		// for fprintf()
#include <iostream>

#include "../Camera/cFlyCamera.h"
#include "../LoadingStuff/FileReaders.h"

bool isOnlyShiftKeyDown(int mods);
bool isOnlyCtrlKeyDown(int mods);
bool isOnlyAltKeyDown(int mods);
bool isShiftDown(GLFWwindow* window);
bool isCtrlDown(GLFWwindow* window);
bool isAltDown(GLFWwindow* window);
bool areAllModifiersUp(GLFWwindow* window);

bool g_MouseIsInsideWindow = false;
bool g_MouseLeftButtonIsDown = false;

glm::vec3 inputRotation = glm::vec3(0.0f);
float speed = 3.0f;

const float CAMERASPEED = 0.5f;
unsigned SelecetedLight = 0;
extern bool bLightDebugSheresOn;

// Declared in theMain
//extern cFlyCamera* g_pFlyCamera;

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		::g_MouseIsInsideWindow = true;
		//std::cout << "Mouse moved inside window" << std::endl;
	}
	else
	{
		::g_MouseIsInsideWindow = false;
		//std::cout << "Mouse moved outside window" << std::endl;
	}
	return;
}//cursor_enter_callback(...

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	const float SPEED = 20.0f;


	if (!isShiftDown(window) && !isCtrlDown(window))
	{
		if (key == GLFW_KEY_ENTER && action == GLFW_PRESS)
		{
			lockToShip = !lockToShip;
		}

		/*	if (key == GLFW_KEY_B)
			{
				// Shoot a bullet from the pirate ship
				// Find the pirate ship...
				// returns NULL (0) if we didn't find it.
	//			cGameObject* pShip = pFindObjectByFriendlyName("PirateShip");
				//cGameObject* pShip = pFindObjectByFriendlyNameMap("PirateShip");
				// Maybe check to see if it returned something...

				// Find the sphere#2
	//			cGameObject* pBall = pFindObjectByFriendlyName("Sphere#2");
				//cGameObject* pBall = pFindObjectByFriendlyNameMap("Sphere#2");

				// Set the location velocity for sphere#2
				//pBall->positionXYZ = pShip->positionXYZ;
				//pBall->inverseMass = 1.0f;		// So it's updated
				// 20.0 units "to the right"
				// 30.0 units "up"
				//pBall->velocity = glm::vec3( 15.0f, 20.0f, 0.0f );
				//pBall->accel = glm::vec3(0.0f,0.0f,0.0f);
				//pBall->diffuseColour = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
			}//if ( key == GLFW_KEY_B )

		}
		*/
		/*if (isOnlyCtrlKeyDown(mods))
		{
			if (key == GLFW_KEY_1)
			{
				//cGameObject* pCannon1 = pFindObjectByFriendlyName("C1");
				// Can move the m_pGO relative to the "parent" m_pGO
				//pCannon1->positionXYZ.z -= 1.0f;
			}
			if (key == GLFW_KEY_2)
			{
				//cGameObject* pCannon2 = pFindObjectByFriendlyName("C2");
				//pCannon2->positionXYZ.z -= 1.0f;
			}
		}
		*/
		if (key == GLFW_KEY_1 && action == GLFW_PRESS)
		{
			for (std::vector<cGameObject*>::iterator it = ::g_vec_pGameObjects.begin(); it != g_vec_pGameObjects.end(); it++)
			{
				(*it)->isWireframe = false;
			}
		}
		if (key == GLFW_KEY_2 && action == GLFW_PRESS)
		{
			for (std::vector<cGameObject*>::iterator it = ::g_vec_pGameObjects.begin(); it != g_vec_pGameObjects.end(); it++)
			{
				(*it)->isWireframe = true;
			}

		}
	}
	if (isOnlyShiftKeyDown(mods))
	{


		if (key == GLFW_KEY_A)
		{
			g_pLightManager->GetLastLight()->Position.x -= CAMERASPEED;		// Move the camera -0.01f units

		}
		if (key == GLFW_KEY_D)
		{
			g_pLightManager->GetLastLight()->Position.x += CAMERASPEED;		// Move the camera +0.01f units


		}

		// Move the camera (Q & E for up and down, along the y axis)
		if (key == GLFW_KEY_Q)
		{
			g_pLightManager->GetLastLight()->Position.y -= CAMERASPEED;		// Move the camera -0.01f units
		}
		if (key == GLFW_KEY_E)
		{
			g_pLightManager->GetLastLight()->Position.y += CAMERASPEED;		// Move the camera +0.01f units
		}

		// Move the camera (W & S for towards and away, along the z axis)
		if (key == GLFW_KEY_W)
		{
			g_pLightManager->GetLastLight()->Position.z -= CAMERASPEED;		// Move the camera -0.01f units

		}
		if (key == GLFW_KEY_S)
		{
			g_pLightManager->GetLastLight()->Position.z += CAMERASPEED;		// Move the camera +0.01f units
		}

		if (key == GLFW_KEY_1)
		{
			g_pLightManager->GetLastLight()->ConstAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_2)
		{
			g_pLightManager->GetLastLight()->ConstAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_3)
		{
			g_pLightManager->GetLastLight()->LinearAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_4)
		{
			g_pLightManager->GetLastLight()->LinearAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_5)
		{
			g_pLightManager->GetLastLight()->QuadraticAtten *= 0.99f;			// 99% of what it was
		}
		if (key == GLFW_KEY_6)
		{
			g_pLightManager->GetLastLight()->QuadraticAtten *= 1.01f;			// 1% more of what it was
		}
		if (key == GLFW_KEY_V)
		{
			g_pLightManager->GetLastLight()->SpotInnerAngle -= 0.1f;
		}
		if (key == GLFW_KEY_B)
		{
			g_pLightManager->GetLastLight()->SpotInnerAngle += 0.1f;
		}
		if (key == GLFW_KEY_N)
		{
			g_pLightManager->GetLastLight()->SpotOuterAngle -= 0.1f;
		}
		if (key == GLFW_KEY_M)
		{
			g_pLightManager->GetLastLight()->SpotOuterAngle += 0.1f;
		}
		if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
		{

			SelecetedLight++;
			if (SelecetedLight == g_pLightManager->GetLightCount())
			{
				SelecetedLight = 0;
			}
			g_pLightManager->GetLight(SelecetedLight);

		}
		if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
		{

			SelecetedLight--;
			if (SelecetedLight == -1)
			{
				SelecetedLight += g_pLightManager->GetLightCount();
			}
			g_pLightManager->GetLight(SelecetedLight);

		}

		if (key == GLFW_KEY_7)
		{
			g_pLightManager->GetLastLight()->isLightOn = false;
		}
		if (key == GLFW_KEY_8)
		{
			g_pLightManager->GetLastLight()->isLightOn = true;
		}

		if (key == GLFW_KEY_9)
		{
			bLightDebugSheresOn = false;
		}
		if (key == GLFW_KEY_0)
		{
			bLightDebugSheresOn = true;
		}


		if (key == GLFW_KEY_L && action == GLFW_PRESS)
		{
			LoadLightsFromXMLFile("assets/config/Lights.xml", g_pLightManager);
		}
		if (key == GLFW_KEY_O && action == GLFW_PRESS)
		{
			SaveLightsToXMLFile("assets/config/Lights.xml", g_pLightManager);
		}

	}//if (isShiftKeyDownByAlone(mods))


	// Moving the pirate ship in a certain direction
	/*if (isOnlyCtrlKeyDown(mods))
	{
		const float SHIP_SPEED_CHANGE = 0.01f;
		const float SHIP_ANGLE_CHANGE = 1.0f;

		//cGameObject* pShip = pFindObjectByFriendlyName("PirateShip");
		// Turn the ship around
		if (key == GLFW_KEY_A)
		{	// Left
			//pShip->HACK_AngleAroundYAxis -= SHIP_ANGLE_CHANGE;
			//pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
			//pShip->updateOrientation( glm::vec3(0.0f, -SHIP_ANGLE_CHANGE, 0.0f));
		}
		if (key == GLFW_KEY_D)
		{	// Right
			//pShip->HACK_AngleAroundYAxis += SHIP_ANGLE_CHANGE;
			//pShip->rotationXYZ.y = pShip->HACK_AngleAroundYAxis;
			//pShip->updateOrientation( glm::vec3(0.0f, +SHIP_ANGLE_CHANGE, 0.0f));
		}
		if (key == GLFW_KEY_W)
		{	// Faster
			//pShip->HACK_speed += SHIP_SPEED_CHANGE;
		}
		if (key == GLFW_KEY_S)
		{	// Slower
			//pShip->HACK_speed -= SHIP_SPEED_CHANGE;
		}
	}
	*/


	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);

}




bool isOnlyShiftKeyDown(int mods)
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

bool isOnlyCtrlKeyDown(int mods)
{
	if (mods == GLFW_MOD_CONTROL)
	{
		return true;
	}
	return false;
}

bool isOnlyAltKeyDown(int mods)
{
	if (mods == GLFW_MOD_ALT)
	{
		return true;
	}
	return false;
}

bool isShiftDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT)) { return true; }
	// both are up
	return false;
}

bool isCtrlDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL)) { return true; }
	// both are up
	return false;
}

bool isAltDown(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) { return true; }
	if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT)) { return true; }
	// both are up
	return false;
}

bool areAllModifiersUp(GLFWwindow* window)
{
	if (isShiftDown(window)) { return false; }
	if (isCtrlDown(window)) { return false; }
	if (isAltDown(window)) { return false; }
	// Yup, they are all UP
	return true;
}

// Mouse (cursor) callback
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	return;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	// A regular mouse wheel returns the y value
	//::g_pFlyCamera->setMouseWheelDelta(yoffset);
	::g_pFreeCamera->Sensitivity(::g_pFreeCamera->Sensitivity() + (yoffset * 0.01f));
	//	std::cout << "Mouse wheel: " << yoffset << std::endl;

	return;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		::g_MouseLeftButtonIsDown = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		::g_MouseLeftButtonIsDown = false;
	}

	return;
}

void ProcessAsyncMouse(GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);

	//::g_pFlyCamera->setMouseXY(x, y);

	//const float MOUSE_SENSITIVITY = 0.1f;

	//	std::cout << ::g_pFlyCamera->getMouseX() << ", " << ::g_pFlyCamera->getMouseY() << std::endl;

		// Mouse left (primary?) button pressed? 
		// AND the mouse is inside the window...
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		&& ::g_MouseIsInsideWindow)
	{
		::g_pFreeCamera->Yaw(::g_pFreeCamera->XChange(-x));

		::g_pFreeCamera->Pitch(::g_pFreeCamera->YChange(y));
		// Mouse button is down so turn the camera
		//::g_pFlyCamera->Yaw_LeftRight(-::g_pFlyCamera->getDeltaMouseX() * MOUSE_SENSITIVITY);
		//::g_pFlyCamera->Pitch_UpDown(::g_pFlyCamera->getDeltaMouseY() * MOUSE_SENSITIVITY);

	}
	else
	{
		::g_pFreeCamera->XChange(-x);
		::g_pFreeCamera->YChange(y);
	}

	// Adjust the mouse speed
	if (::g_MouseIsInsideWindow)
	{
		const float MOUSE_WHEEL_SENSITIVITY = 0.1f;

		// Adjust the movement speed based on the wheel position
		//::g_pFlyCamera->movementSpeed += (::g_pFlyCamera->getMouseWheel() * MOUSE_WHEEL_SENSITIVITY);
		//if (::g_pFlyCamera->movementSpeed <= 0.0f)
		//{
		//	::g_pFlyCamera->movementSpeed = 0.0f;
		//}
	}


	// HACK 
	//::g_pFlyCamera->movementSpeed = 2.0f;

	return;
}//ProcessAsyncMouse(...


void ProcessAsyncKeys(GLFWwindow* window)
{
	//const float CAMERA_MOVE_SPEED_SLOW = 0.1f;
	//const float CAMERA_MOVE_SPEED_FAST = 1.0f;

	//const float CAMERA_TURN_SPEED = 0.1f;

	// WASD + q = "up", e = down		y axis = up and down
	//									x axis = left and right
	//									z axis = forward and backward
	// 

	//float cameraSpeed = CAMERA_MOVE_SPEED_SLOW;
	//if ( glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS  )
	//{
	//	cameraSpeed = CAMERA_MOVE_SPEED_FAST;
	//}

	//float cameraMoveSpeed = ::g_pFlyCamera->movementSpeed;

	// If no keys are down, move the camera
	if (areAllModifiersUp(window))
	{
		if (glfwGetKey(window, GLFW_KEY_W))
		{
			::g_pFreeCamera->MoveForward(1.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_S))
		{
			::g_pFreeCamera->MoveForward(-1.0f);
		}
		//else
		//{
		//	::g_pFreeCamera->MoveForward(0.0f);
		//}

		if (glfwGetKey(window, GLFW_KEY_A))
		{
			::g_pFreeCamera->MoveRight(-1.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_D))
		{
			::g_pFreeCamera->MoveRight(1.0f);
		}
		//else
		//{
		//	::g_pFreeCamera->MoveRight(0.0f);
		//}

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			::g_pFreeCamera->MoveUp(-1.0f);
		}
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			::g_pFreeCamera->MoveUp(1.0f);
		}
		//else
		//{
		//	::g_pFreeCamera->MoveUp(0.0f);
		//}
		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		{
			::g_pFreeCamera->Speed(::g_pFreeCamera->Speed() - 0.1f);
		}
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		{
			::g_pFreeCamera->Speed(::g_pFreeCamera->Speed() + 0.1f);
		}

	}//if(AreAllModifiersUp(window)

	return;
}// ProcessAsyncKeys(..





void ShipControls(GLFWwindow* window)
{

	if (areAllModifiersUp(window))
	{

	/*	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			inputRotation.x = 30.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			inputRotation.x = -30.0f;
		}
		else
		{
			inputRotation.x = 0.0f;
		}


		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			inputRotation.y = 30.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			inputRotation.y = -30.0f;
		}
		else
		{
			inputRotation.y = 0.0f;
		}


		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			inputRotation.z = 30.0f;
		}
		else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			inputRotation.z = -30.0f;
		}
		else
		{
			inputRotation.z = 0.0f;
		}*/

		//pFindObjectByFriendlyName("Ship")->setAngularVelocity(inputRotation);


		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			glm::vec4 accel = glm::vec4(0.0f, 0.0f, speed, 1.0f);
			accel = glm::mat4(pFindObjectByFriendlyName("Ship")->getQOrientation()) * accel;

			pFindObjectByFriendlyName("Ship")->accel = accel;
		}
		else
		{
			pFindObjectByFriendlyName("Ship")->accel = glm::vec3(0.0f);
		}

		if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
		{
			//::g_pFreeCamera->Speed(::g_pFreeCamera->Speed() - 0.1f);
			speed -= 0.1;
		}
		if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
		{
			//::g_pFreeCamera->Speed(::g_pFreeCamera->Speed() + 0.1f);
			speed += 0.1;
		}

	}//if(AreAllModifiersUp(window)

	// If shift is down, do the rotation camera stuff...
	// If no keys are down, move the camera
	if (isShiftDown(window))
	{
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)	// "down"
		{
			glm::vec4 accel = glm::vec4(0.0f, 0.0f, -speed, 1.0f);
			accel = glm::mat4(pFindObjectByFriendlyName("Ship")->getQOrientation()) * accel;

			pFindObjectByFriendlyName("Ship")->accel = accel;
		}
		else
		{
			pFindObjectByFriendlyName("Ship")->accel = glm::vec3(0.0f);
		}

	}//IsShiftDown(window)


	return;
}// ProcessAsyncKeys(..