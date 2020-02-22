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
	//void ProcessAsyncKeys(GLFWwindow * window, std::vector<cPhysicsGameObject*>& object, size_t& selected, c3rdPersonCamera * camera);
	void ProcessAsyncKeys(GLFWwindow * window, std::vector<cGameObject*> & object, size_t & selected, c3rdPersonCamera * camera);

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



	std::vector<cGameObject*> stuff;
	cGameObject* parent;// = new cGameObject();

	{
		parent = new cGameObject();
		parent->mSkinnedMesh = new cSkinnedMesh();
		parent->mIsSkinnedMesh = true;
		parent->mSkinnedMesh->LoadMeshFromFile("Clothes", "assets/models/Animation/Archer/Idle.fbx", 2);
		parent->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Jumping", "assets/models/Animation/Archer/Jumping.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Left Strafe", "assets/models/Animation/Archer/Walk Strafe Left.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Right Strafe", "assets/models/Animation/Archer/Walk Strafe Right.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Run", "assets/models/Animation/Archer/Run.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("RunningJump", "assets/models/Animation/Archer/RunningJump.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Action", "assets/models/Animation/Archer/Standing Draw Arrow.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Walk", "assets/models/Animation/Archer/NewWalking.fbx");
		parent->meshName = "Clothes";
		parent->friendlyName = "Archer";	// Friendly name
		parent->positionXYZ = glm::vec3(10.0f, 0.0f, 0.0f);
		parent->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
		parent->scale = .1f;
		parent->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		parent->inverseMass = 0.0f;
		parent->CurrentAnimation("Idle");
		parent->doNotLight = true;
		parent->isVisible = true;
		parent->isWireframe = false;
		parent->useDiffuse = true;
		parent->diffuseColour = glm::vec4(.5f, .5f, .5f, 1.f);



		{
			cGameObject* temp = new cGameObject();

			temp->mSkinnedMesh = new cSkinnedMesh();
			temp->mIsSkinnedMesh = true;
			temp->mSkinnedMesh->LoadMeshFromFile("Skin", "assets/models/Animation/Archer/Idle.fbx", 5);
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Jumping", "assets/models/Animation/Archer/Jumping.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Left Strafe", "assets/models/Animation/Archer/Walk Strafe Left.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Right Strafe", "assets/models/Animation/Archer/Walk Strafe Right.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Run", "assets/models/Animation/Archer/Run.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("RunningJump", "assets/models/Animation/Archer/RunningJump.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Action", "assets/models/Animation/Archer/Standing Draw Arrow.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Walk", "assets/models/Animation/Archer/NewWalking.fbx");
			temp->meshName = "Skin";
			temp->friendlyName = "Archer";	// Friendly name
			temp->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
			temp->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
			temp->scale = .1f;
			temp->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			temp->inverseMass = 0.0f;
			temp->doNotLight = true;
			temp->isVisible = true;
			temp->isWireframe = false;
			temp->useDiffuse = true;
			temp->diffuseColour = glm::vec4(.0f, .0f, .0f, 1.f);

			parent->vec_pChildObjects.push_back(temp);
			g_Renderer.AddModel(temp->mSkinnedMesh);
		}
		{
			cGameObject* temp = new cGameObject();

			temp->mSkinnedMesh = new cSkinnedMesh();
			temp->mIsSkinnedMesh = true;
			temp->mSkinnedMesh->LoadMeshFromFile("Bow", "assets/models/Animation/Archer/Idle.fbx", 0);
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Jumping", "assets/models/Animation/Archer/Jumping.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Left Strafe", "assets/models/Animation/Archer/Walk Strafe Left.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Right Strafe", "assets/models/Animation/Archer/Walk Strafe Right.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Run", "assets/models/Animation/Archer/Run.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("RunningJump", "assets/models/Animation/Archer/RunningJump.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Action", "assets/models/Animation/Archer/Standing Draw Arrow.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Walk", "assets/models/Animation/Archer/NewWalking.fbx");
			temp->meshName = "Bow";
			temp->friendlyName = "Archer";	// Friendly name
			temp->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
			temp->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
			temp->scale = .1f;
			temp->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			temp->inverseMass = 0.0f;
			temp->doNotLight = true;
			temp->isVisible = true;
			temp->isWireframe = false;
			temp->useDiffuse = true;
			temp->diffuseColour = glm::vec4(.4f, .2f, .1f, 1.f);

			parent->vec_pChildObjects.push_back(temp);
			g_Renderer.AddModel(temp->mSkinnedMesh);
		}
		{
			cGameObject* temp = new cGameObject();

			temp->mSkinnedMesh = new cSkinnedMesh();
			temp->mIsSkinnedMesh = true;
			temp->mSkinnedMesh->LoadMeshFromFile("Eyes1", "assets/models/Animation/Archer/Idle.fbx", 3);
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Jumping", "assets/models/Animation/Archer/Jumping.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Left Strafe", "assets/models/Animation/Archer/Walk Strafe Left.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Right Strafe", "assets/models/Animation/Archer/Walk Strafe Right.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Run", "assets/models/Animation/Archer/Run.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("RunningJump", "assets/models/Animation/Archer/RunningJump.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Action", "assets/models/Animation/Archer/Standing Draw Arrow.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Walk", "assets/models/Animation/Archer/NewWalking.fbx");
			temp->meshName = "Eyes1";
			temp->friendlyName = "Archer";	// Friendly name
			temp->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
			temp->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
			temp->scale = .1f;
			temp->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			temp->inverseMass = 0.0f;
			temp->doNotLight = true;
			temp->isVisible = true;
			temp->isWireframe = false;
			temp->useDiffuse = true;
			temp->diffuseColour = glm::vec4(.3f, .3f, .6f, 1.f);

			parent->vec_pChildObjects.push_back(temp);
			g_Renderer.AddModel(temp->mSkinnedMesh);
		}
		{
			cGameObject* temp = new cGameObject();

			temp->mSkinnedMesh = new cSkinnedMesh();
			temp->mIsSkinnedMesh = true;
			temp->mSkinnedMesh->LoadMeshFromFile("Eyes2", "assets/models/Animation/Archer/Idle.fbx", 4);
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Archer/Idle.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Jumping", "assets/models/Animation/Archer/Jumping.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Left Strafe", "assets/models/Animation/Archer/Walk Strafe Left.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Right Strafe", "assets/models/Animation/Archer/Walk Strafe Right.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Run", "assets/models/Animation/Archer/Run.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("RunningJump", "assets/models/Animation/Archer/RunningJump.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Action", "assets/models/Animation/Archer/Standing Draw Arrow.fbx");
			temp->mSkinnedMesh->LoadMeshAnimation("Walk", "assets/models/Animation/Archer/NewWalking.fbx");
			temp->meshName = "Eyes2";
			temp->friendlyName = "Archer";	// Friendly name
			temp->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
			temp->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
			temp->scale = .1f;
			temp->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
			temp->inverseMass = 0.0f;
			temp->doNotLight = true;
			temp->isVisible = true;
			temp->isWireframe = false;
			temp->useDiffuse = true;
			temp->diffuseColour = glm::vec4(1.f, 1.f, 1.f, 1.f);

			parent->vec_pChildObjects.push_back(temp);
			g_Renderer.AddModel(temp->mSkinnedMesh);
		}
		parent->CurrentAnimation("Idle");
		stuff.push_back(parent);
		g_Renderer.AddModel(parent->mSkinnedMesh);
		g_Renderer.AddRenderComponent(parent);
	}
	{
		parent = new cGameObject();
		parent->mSkinnedMesh = new cSkinnedMesh();
		parent->mIsSkinnedMesh = true;
		parent->mSkinnedMesh->LoadMeshFromFile("FullWarrior", "assets/models/Animation/Warrior/Catwalk Idle.fbx", 0);

		parent->mSkinnedMesh->LoadMeshAnimation("Idle", "assets/models/Animation/Warrior/Catwalk Idle.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Jumping", "assets/models/Animation/Warrior/Jump.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Left Strafe", "assets/models/Animation/Warrior/Left Strafe.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Right Strafe", "assets/models/Animation/Warrior/Right Strafe.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Run", "assets/models/Animation/Warrior/Running.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("RunningJump", "assets/models/Animation/Warrior/Sprinting Forward Roll.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Action", "assets/models/Animation/Warrior/Standing 2H Magic Attack 05.fbx");
		parent->mSkinnedMesh->LoadMeshAnimation("Walk", "assets/models/Animation/Warrior/Walking.fbx");

		parent->meshName = "FullWarrior";
		parent->friendlyName = "Warrior";	// Friendly name
		parent->positionXYZ = glm::vec3(-10.0f, 0.0f, 0.0f);
		parent->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
		parent->scale = .1f;
		parent->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		parent->inverseMass = 0.0f;
		parent->CurrentAnimation("Idle");
		parent->doNotLight = true;
		parent->isVisible = true;
		parent->isWireframe = false;
		parent->useDiffuse = true;
		parent->diffuseColour = glm::vec4(.5f, .5f, .5f, 1.f);


		parent->CurrentAnimation("Idle");
		stuff.push_back(parent);
		g_Renderer.AddModel(parent->mSkinnedMesh);
		g_Renderer.AddRenderComponent(parent);
	}




	size_t selectedObjectIndex = 0;
	c3rdPersonCamera* cam = new c3rdPersonCamera();
	cam->SetOffset(glm::vec3(0.f, 0.f, -1.f));
	cam->AddPitch(20.f);
	cam->AddZoom(40.f);
	cam->Update(parent->Transform());
	g_Renderer.SetCamera(cam);
	g_Renderer.AddRenderComponent(parent);
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
		//ProcessAsyncKeys(window, objects, selectedObjectIndex, cam);
		ProcessAsyncKeys(window, stuff, selectedObjectIndex, cam);

		int width, height;

		glfwGetFramebufferSize(window, &width, &height);


		cam->Update(stuff[selectedObjectIndex]->Transform());
		//cam->Update(
		//	glm::scale(stuff[selectedObjectIndex]->mSkinnedMesh->mBoneInfo[stuff[selectedObjectIndex]->mSkinnedMesh->m_mapBoneNameToBoneIndex["Hips"]].FinalTransformation,
		//			  glm::vec3(stuff[selectedObjectIndex]->scale)));

		//cam->Update(objects[selectedObjectIndex]->Transform());
		g_Renderer.RenderScene(width, height);

		stuff[0]->AnimationTimeStep(deltaTime);
		stuff[1]->AnimationTimeStep(deltaTime);

		g_World->Update(deltaTime);


		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glfwDestroyWindow(window);
	glfwTerminate();

	//delete pTheModelLoader;
	delete ::g_pFlyCamera;
	delete g_World;
	for (auto* obj : objects)
	{
		delete obj;
	}

	exit(EXIT_SUCCESS);
}
