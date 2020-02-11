#include "../globals.h"			// for find m_pGO

#include "GFLW_callbacks.h"
#include <stdio.h>		// for fprintf()
#include <iostream>

#include "../Camera/cFlyCamera.h"

#include "../Camera/ThirdPersonCamera.h"
#include "../GameObject/cShip.h"
#include "../AI/Behaviours/cPursueAndEvade.h"


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

extern int HealthRight, HealthLeft;
extern float offset;

#include "../Commands/Commands.h"
#include "../Commands/cLuaBrain.h"
extern iCommand* g_ParentCommandGroup;
extern cLuaBrain* g_pLuaScripts;

extern ThirdPersonCamera* tpc;
// Declared in theMain
//extern cFlyCamera* g_pFlyCamera;



extern std::vector<glm::vec3> PathPoints;
//extern bool g_DoingRun;
extern glm::vec3 g_EndPoint, g_StartPoint;



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

