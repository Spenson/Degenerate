#include "globals.h"

#include <iostream>
#include <sstream>

#include "UserInputs/GFLW_callbacks.h"
#include "Camera/cFlyCamera.h"
#include "DebugRenderer/cDebugRenderer.h"
#include "LowPassFilter/cLowPassFilter.h"

#include "Commands/cLuaBrain.h"

#include "Rendering/Renderer.h"

#include "Rendering/cSimpleSkybox.h"
#include "LoadingStuff/Load.h"
#include "GameObject/cPhysicsGameObject.h"
#include "Camera/c3rdPersonCamera.h"

cFlyCamera* g_pFlyCamera = nullptr;
bool lockToShip = false;

DegenRendering::cRenderer g_Renderer;
DegenPhysics::iPhysicsWorld* g_World;



int main(void)
{
	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	window = glfwCreateWindow(1280, 720, "Degenerate", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorEnterCallback(window, cursor_enter_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	//void ProcessAsyncMouse(GLFWwindow * window);
	//void ProcessAsyncKeys(GLFWwindow * window);
	//void ShipControls(GLFWwindow * window, cShip * player);

	void ProcessAsyncMouse(GLFWwindow * window, c3rdPersonCamera * camera);
	void ProcessAsyncKeys(GLFWwindow * window, std::vector<cPhysicsGameObject*>& object, size_t& selected, c3rdPersonCamera * camera);

	GLint major, minor;
	glGetIntegerv(GL_MAJOR_VERSION, &major);
	glGetIntegerv(GL_MINOR_VERSION, &minor);
	std::cout << "OpenGL version: " << major << "." << minor << std::endl;

	//TODO: Move if needed
	cDebugRenderer* pDebugRenderer = new cDebugRenderer();
	pDebugRenderer->initialize();



	g_pFreeCamera->UpVector(glm::vec3(0.f, 1.f, 0.f));
	g_pFreeCamera->SetPosition(glm::vec3(0.f, 20.f, -30.f));
	g_pFreeCamera->Target(glm::vec3(0.f));


	g_Renderer.Initialize();
	g_Renderer.AddModel("sphere_hires.ply");
	g_Renderer.AddModel("flat.ply");
	g_Renderer.AddTexture("gridtexture.bmp");
	g_Renderer.AddCubeMap("orbit", "orbital-element_up.bmp", "orbital-element_dn.bmp",
						  "orbital-element_lf.bmp", "orbital-element_rt.bmp",
						  "orbital-element_bk.bmp", "orbital-element_ft.bmp",
						  "assets/textures/cubemaps/");


	g_Renderer.SetCamera(::g_pFreeCamera);
	g_Renderer.SetPerspectiveDetails(0.8f, 0.5f, 1000.0f);

	cSimpleSkybox* skybox = new cSimpleSkybox();
	skybox->mModel = "sphere_hires.ply";
	skybox->CubeMaps()[0].first = "orbit";

	g_Renderer.SetSkybox(skybox);


	
	std::vector<cPhysicsGameObject*> objects;

	::LoadScene("assets/config/Config.json", g_Renderer, g_World, objects);

	size_t selectedObjectIndex = 0;
	c3rdPersonCamera* cam = new c3rdPersonCamera();
	cam->Update(objects[selectedObjectIndex]->Transform());
	g_Renderer.SetCamera(cam);

	cLowPassFilter avgDeltaTimeThingy;
	double lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{

		//Frame Time
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		const double SOME_HUGE_TIME = 0.1;	// 100 ms;
		if (deltaTime > SOME_HUGE_TIME)
			deltaTime = SOME_HUGE_TIME;

		avgDeltaTimeThingy.addValue(deltaTime);

		ProcessAsyncMouse(window, cam);
		ProcessAsyncKeys(window, objects, selectedObjectIndex, cam);

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);

		cam->Update(objects[selectedObjectIndex]->Transform());
		g_Renderer.RenderScene(width, height);

		g_World->Update(deltaTime);


		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glfwDestroyWindow(window);
	glfwTerminate();

	//delete pTheModelLoader;
	delete ::g_pFlyCamera;


	exit(EXIT_SUCCESS);
}
