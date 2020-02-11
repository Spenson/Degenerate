#include "../globals.h"			// for find m_pGO
#include "../Camera/c3rdPersonCamera.h"
#include "../GameObject/cPhysicsGameObject.h"

static float lastX, lastY;
static double LastBallChange = 0;

extern bool g_MouseIsInsideWindow;

void ProcessAsyncMouse(GLFWwindow* window, c3rdPersonCamera* camera)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	

	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) && ::g_MouseIsInsideWindow)
	{
		float diffX = x - lastX;
		float diffY = y - lastY;
		camera->AddPitch(diffY * 0.5f);
		camera->AddYaw(diffX * 0.5f);
	}
	else if((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) && ::g_MouseIsInsideWindow)
	{
		float diffY = y - lastY;
		camera->AddZoom(diffY * 0.2f);
	}

	lastX = x;
	lastY = y;
}
void ProcessAsyncKeys(GLFWwindow* window, std::vector<cPhysicsGameObject*>& object, size_t& selected, c3rdPersonCamera* camera)
{
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		glm::vec3 force = glm::normalize(camera->Target() - camera->Position()) * 5.f;
		object[selected]->mPhysicsComponent->ApplyForce(force);
	}
	else if (glfwGetKey(window, GLFW_KEY_S))
	{

		glm::vec3 force = glm::normalize(camera->Target() - camera->Position()) * 5.f;
		object[selected]->mPhysicsComponent->ApplyForce(-force);
	}

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		glm::vec3 force = glm::normalize(glm::cross(camera->Target() - camera->Position(), glm::vec3(0.0f, 1.0f, 0.0f))) * 5.f;
		object[selected]->mPhysicsComponent->ApplyForce(-force);
	}
	else if (glfwGetKey(window, GLFW_KEY_D))
	{
		glm::vec3 force = glm::normalize(glm::cross(camera->Target() - camera->Position(), glm::vec3(0.0f, 1.0f, 0.0f))) * 5.f;
		object[selected]->mPhysicsComponent->ApplyForce(force);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE))
	{
		glm::vec3 force = glm::vec3(0.0f, 1.0f, 0.0f) * 10.f;
		object[selected]->mPhysicsComponent->ApplyForce(force);
	}

	if (glfwGetKey(window, GLFW_KEY_TAB))
	{
		if (glfwGetTime() - LastBallChange > 0.5f)
		{
			do
			{
				selected++;
				if (selected == object.size())
					selected = 0;
			} while (object[selected]->mPhysicsComponent->GetComponentType() != DegenPhysics::eComponentType::sphere);

			LastBallChange = glfwGetTime();
		}
	}
}