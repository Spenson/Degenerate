#include "globals.h"

#include <iostream>
#include <sstream>

#include "UserInputs/GFLW_callbacks.h"
#include "Camera/cFlyCamera.h"
#include "Camera/ThirdPersonCamera.h"
#include "DebugRenderer/cDebugRenderer.h"
#include "Rendering/SimpleShaderStuff/UniformManager.h"
#include "Rendering/ParticalEffects/cParticleEmitter.h"
#include "LowPassFilter/cLowPassFilter.h"

#include "Commands/Commands.h"
#include "Commands/cLuaBrain.h"

#include "Rendering/Renderer.h"

#include "Rendering/cSimpleSkybox.h"

cFlyCamera* g_pFlyCamera = NULL;
//cBasicTextureManager* g_pTextureManager = NULL;

bool lockToShip = false;

bool bLightDebugSheresOn = false;

iCommand* g_ParentCommandGroup;

extern cGameObject* g_pDebugSphere;
extern cGameObject* g_pDebugCube;

cLuaBrain* g_pLuaScripts;

float offset = 0.f;
int HealthRight = 100, HealthLeft = 100;


std::vector<glm::vec3> PathPoints;
bool doingRun;
glm::vec3 g_EndPoint, g_StartPoint;


ThirdPersonCamera* tpc;


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

	void ProcessAsyncMouse(GLFWwindow * window);
	void ProcessAsyncKeys(GLFWwindow * window);
	void ShipControls(GLFWwindow * window);


	//TODO: Move if needed
	cDebugRenderer* pDebugRenderer = new cDebugRenderer();
	pDebugRenderer->initialize();

	std::string lighterrors;


	cParticleEmitter* pMyPartcles = new cParticleEmitter();
	pMyPartcles->location = glm::vec3(0.0f, 3.0f, 0.0f);
	// TODO:
	pMyPartcles->acceleration = glm::vec3(5.0f, 0.0f, 0.0f);

	pMyPartcles->Initialize(glm::vec3(-10.0f, -10.0f, -10.0f),	// Min Vel
							glm::vec3(10.0f, 10.0f, 10.0f),		// Max Vel
							glm::vec3(0.0f, 0.0f, 0.0f),		// Min Delta Position
							glm::vec3(0.0f, 0.0f, 0.0f),		// Max delta Position
							5.0f,	// Min life
							10.0f,	// Max life
							10,		// Min # of particles per frame
							60);	// Max # of particles per frame



	g_pFreeCamera->SetPosition(glm::vec3(0.f, 0.f, -20.f));
	g_pFreeCamera->Target(glm::vec3(0.f));


	g_ParentCommandGroup = createParent("Parent");


	//g_pLuaScripts = new cLuaBrain();


	//std::ifstream t("assets/script.lua");
	//std::string luaScript = std::string((std::istreambuf_iterator<char>(t)),
	//					 std::istreambuf_iterator<char>());
	//t.close();

	//g_pLuaScripts->RunThis(luaScript);


	std::vector<glm::vec3> todraw;


	DegenRendering::cRenderer renderer;
	renderer.Initialize();
	renderer.AddModel("cube.ply");
	renderer.AddModel("sphere_hires.ply");
	renderer.AddTexture("gridtexture.bmp");
	renderer.AddCubeMap("orbit","orbital-element_up.bmp","orbital-element_dn.bmp",
						"orbital-element_lf.bmp", "orbital-element_rt.bmp",
						"orbital-element_bk.bmp","orbital-element_ft.bmp",
						"assets/textures/cubemaps/");
	
	renderer.SetCamera(::g_pFreeCamera);
	renderer.SetPerspectiveDetails(0.8f,0.5f,100.0f);

	cSimpleSkybox* skybox = new cSimpleSkybox();
	skybox->mModel = "sphere_hires.ply";
	skybox->CubeMaps()[0].first = "orbit";

	renderer.SetSkybox(skybox);
	
	
	cGameObject go;
	go.meshName = "sphere_hires.ply";
	go.doNotLight = true;
	go.scale = 3.f;
	//go.debugColour = glm::vec4(1.f, 0.f, 0.f, 1.f);

	go.diffuseColour = glm::vec4(1.f, 0.f, 0.f, 1.f);

	renderer.AddRenderComponent(&go);


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


		std::stringstream ssTitle;


		glfwSetWindowTitle(window, ssTitle.str().c_str());


		if (lockToShip)
		{
			//ShipControls(window);
		}
		else
		{
			ProcessAsyncKeys(window);
			ProcessAsyncMouse(window);
		}
		
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		//ratio = width / (float)height;

		//p = glm::perspective(0.6f, ratio, 0.5f, 100000.0f);
		//v = glm::mat4(1.0f);
		//v = glm::lookAt(::g_pFlyCamera->eye, ::g_pFlyCamera->getAtInWorldSpace(), ::g_pFlyCamera->getUpVector());
		//v = glm::lookAt(::g_pFreeCamera->GetPosition(), ::g_pFreeCamera->GetTarget(), ::g_pFreeCamera->GetUpVector());




		renderer.RenderScene(width, height);


		g_ParentCommandGroup->Update(deltaTime);


		double averageDeltaTime = avgDeltaTimeThingy.getAverage();

		//pDebugRenderer->RenderDebugObjects(v, p, 0.01f);

		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glfwDestroyWindow(window);
	glfwTerminate();

	//delete pTheModelLoader;
	delete ::g_pFlyCamera;


	exit(EXIT_SUCCESS);
}
