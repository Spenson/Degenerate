#include "GLCommon.h"

#include "globals.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>		// c libs
#include <stdio.h>		// c libs

#include <iostream>		// C++ IO standard stuff
#include <map>			// Map aka "dictonary" 
#include <algorithm>


#include "ModelLoader.h"			
#include "VAOManager.h"		// NEW
#include "GameObject.h"
#include "Camera/CameraManager.h"


#include <sstream>

#include <limits.h>
#include <float.h>

// The Physics function
#include "PhysicsStuff.h"
#include "cPhysics.h"

#include "cLowPassFilter.h"
//#include "DebugRenderer/cDebugRenderer.h"

// Used to visualize the attenuation of the lights...
#include "LightManager/LightHelper.h"

// Keyboard, error, mouse, etc. are now here
#include "GFLW_callbacks.h"
#include "LightManager/LightManager.h"

#include "FileReaders.h"


#include "DrawCalls.h"
#include "MatrixCalc.h"


//void DrawObject(glm::mat4 m, GameObject* pCurrentObject, GLint shaderProgID, VAOManager* pVAOManager);
//glm::mat4 calculateWorldMatrix(GameObject* pCurrentObject);
bool bLightDebugSheresOn = false;



// Load up my "scene"  (now global)
std::vector<GameObject*> g_vec_pGameObjects;
std::map<std::string /*FriendlyName*/, GameObject*> g_map_GameObjectsByFriendlyName;

std::map<std::string, Mesh> mMeshes;
LightManager lightMan;

//bool g_BallCollided = false;


//global so these are seen by the draw call... TODO: Find a better way if needed


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

	window = glfwCreateWindow(1280, 720, "Degenerate Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, key_callback);
	// Set the mouse button callback
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);



	//cDebugRenderer* pDebugRenderer = new cDebugRenderer();
	//pDebugRenderer->initialize();


	//	pDebugRenderer->RenderDebugObjects(glm::mat4(1.0f), glm::mat4(1.0f), 0.0f);

		// OpenGL and GLFW are good to go, so load the model
		//ModelLoader theModelLoader;   // Stack
		//theModelLoader.LoadPlyModel();


	ModelLoader* pTheModelLoader = new ModelLoader();	// Heap


	ReadMeshesFromFile("../assets/config/Meshes.xml", "../assets/models/", mMeshes, pTheModelLoader);
	pTheModelLoader->LoadPlyModel("../assets/models/Sphere_Radius_1_XYZ_n.ply", mMeshes["sphereMesh"]);


	// Create a VAO Manager...
	// #include "VAOManager.h"  (at the top of your file)
	VAOManager* pTheVAOManager = new VAOManager();
	std::vector<ModelDrawInfo> vecDrawInfo;
	// Note, the "filename" here is really the "model name" 
	//  that we can look up later (i.e. it doesn't have to be the file name)
	for (std::map<std::string, Mesh>::iterator iter = mMeshes.begin(); iter != mMeshes.end(); iter++)
	{
		ModelDrawInfo drawInfo;
		pTheVAOManager->LoadModelIntoVAO(iter->first,
										 iter->second,
										 drawInfo,
										 shaderProgID);
		vecDrawInfo.push_back(drawInfo);
	}

	ModelDrawInfo sphereMeshInfo;
	pTheVAOManager->LoadModelIntoVAO("sphere",
									 mMeshes["sphereMesh"],		// Sphere mesh info
									 sphereMeshInfo,
									 shaderProgID);



	ReadGameObjectsFromFile("../assets/config/GameObjects.xml", ::g_vec_pGameObjects, true);
	


	// Will be moved placed around the scene
	GameObject* pDebugSphere = new GameObject();
	pDebugSphere->meshName = "sphere";
	pDebugSphere->friendlyName = "debug_sphere";
	pDebugSphere->position = glm::vec3(0.0f, 0.0f, 0.0f);
	//pDebugSphere->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	pDebugSphere->scale = glm::vec3(0.1f);
	//	pDebugSphere->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	pDebugSphere->isWireframe = true;
	pDebugSphere->inverseMass = 0.0f;			// Sphere won't move




	//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);


	glEnable(GL_DEPTH);			// Write to the depth buffer
	glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing

	//float shipVelocityZ = 1.0f;
	//float shipAccelz = 1000.0f;


	cPhysics* pPhsyics = new cPhysics();

	cLowPassFilter avgDeltaTimeThingy;


	LightHelper* pLightHelper = new LightHelper();

	// Get the initial time
	double lastTime = glfwGetTime();





	std::string lighterrors;

	std::vector<Light*> templights;

	ReadLightsFromFile("../assets/config/Lights.xml", lightMan);

	lightMan.InitilizeLightUinformLocations(shaderProgID, "theLights", 10, lighterrors);
	//Light* sexyLight = lightMan.GetLight(0);

	CameraManager::GetCameraInstance()->SetPosition(glm::vec3(0, 0, 30.f));
	CameraManager::GetCameraInstance()->LookRight(180);

	while (!glfwWindowShouldClose(window))
	{

		// Get the initial time
		double currentTime = glfwGetTime();

		// Frame time... (how many seconds since last frame)
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		const double SOME_HUGE_TIME = 0.1;	// 100 ms;
		if (deltaTime > SOME_HUGE_TIME)
		{
			deltaTime = SOME_HUGE_TIME;
		}

		avgDeltaTimeThingy.addValue(deltaTime);


		glUseProgram(shaderProgID);

		float ratio;
		int width, height;
		//       mat4x4 m, p, mvp;
		//glm::mat4 m, p, v, mvp;
		glm::mat4 p, v;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		// Projection matrix
		p = glm::perspective(0.6f,		// FOV
							 ratio,			// Aspect ratio
							 0.1f,			// Near clipping plane
							 1000.0f);		// Far clipping plane

		// View matrix
		v = glm::mat4(1.0f);

		v = glm::lookAt(CameraManager::GetCameraInstance()->GetPosition(),
						CameraManager::GetCameraInstance()->GetTarget(),
						CameraManager::GetCameraInstance()->GetUpVector());


		glViewport(0, 0, width, height);

		// Clear both the colour buffer (what we see) and the 
		//  depth (or z) buffer.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		lightMan.PassLightsToShader();





		glUniform4f(eyeLocation_UL,
					CameraManager::GetCameraInstance()->GetPosition().x, 
					CameraManager::GetCameraInstance()->GetPosition().y, 
					CameraManager::GetCameraInstance()->GetPosition().z, 1.0f);


		//std::stringstream ssTitle;
		//ssTitle
		//	<< lightMan.GetLastLight()->Position.x << ", "
		//	<< lightMan.GetLastLight()->Position.y << ", "
		//	<< lightMan.GetLastLight()->Position.z
		//	<< "Atten: "
		//	<< lightMan.GetLastLight()->ConstAtten << " : "
		//	<< lightMan.GetLastLight()->LinearAtten << " : "
		//	<< lightMan.GetLastLight()->QuadraticAtten;
		//glfwSetWindowTitle(window, ssTitle.str().c_str());


		glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));


		// **************************************************
		// **************************************************
		// Loop to draw everything in the scene


		for (int index = 0; index != ::g_vec_pGameObjects.size(); index++)
		{
			glm::mat4 matModel = glm::mat4(1.0f);

			GameObject* pCurrentObject = ::g_vec_pGameObjects[index];

			DrawObject(matModel, pCurrentObject,
					   shaderProgID, pTheVAOManager);

		}//for (int index...


		// Update the objects through physics
//		PhysicsUpdate( vec_pGameObjects, 0.01f );



//		pPhsyics->IntegrationStep(::g_vec_pGameObjects, 0.01f);
//		pPhsyics->IntegrationStep(::g_vec_pGameObjects, (float)deltaTime);
		double averageDeltaTime = avgDeltaTimeThingy.getAverage();
		pPhsyics->IntegrationStep(::g_vec_pGameObjects, (float)averageDeltaTime);
		pPhsyics->TestForCollisions(::g_vec_pGameObjects);
		pPhsyics->ProcessCollisions();
		// Let's draw all the closest points to the sphere
		// on the terrain mesh....
		// 
		// For each triangle in the terrain mesh:
		// - Run ClosestPointToTriangle
		// - Place the debug sphere "there"
		// - Draw it.




		if (bLightDebugSheresOn)
		{
			{// Draw where the light is at
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->position = lightMan.GetLastLight()->Position;
				pDebugSphere->scale = glm::vec3(0.5f);
				pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}

			// Draw spheres to represent the attenuation...
			{   // Draw a sphere at 1% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->position = lightMan.GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.01f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLastLight()->ConstAtten,
					lightMan.GetLastLight()->LinearAtten,
					lightMan.GetLastLight()->QuadraticAtten);
				pDebugSphere->scale = glm::vec3(sphereSize);
				pDebugSphere->debugColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 25% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->position = lightMan.GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.25f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLastLight()->ConstAtten,
					lightMan.GetLastLight()->LinearAtten,
					lightMan.GetLastLight()->QuadraticAtten);
				pDebugSphere->scale = glm::vec3(sphereSize);
				pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 50% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->position = lightMan.GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.50f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLastLight()->ConstAtten,
					lightMan.GetLastLight()->LinearAtten,
					lightMan.GetLastLight()->QuadraticAtten);
				pDebugSphere->scale = glm::vec3(sphereSize);
				pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 75% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->position = lightMan.GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.75f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLastLight()->ConstAtten,
					lightMan.GetLastLight()->LinearAtten,
					lightMan.GetLastLight()->QuadraticAtten);
				pDebugSphere->scale = glm::vec3(sphereSize);
				pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 95% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->position = lightMan.GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.95f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLastLight()->ConstAtten,
					lightMan.GetLastLight()->LinearAtten,
					lightMan.GetLastLight()->QuadraticAtten);
				pDebugSphere->scale = glm::vec3(sphereSize);
				pDebugSphere->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
		}// if (bLightDebugSheresOn) 

		 // **************************************************
		// **************************************************



		//pDebugRenderer->RenderDebugObjects(v, p, 0.01f);



		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();


	// Delete everything
	delete pTheModelLoader;
	//	delete pTheVAOManager;

		// Watch out!!
		// sVertex* pVertices = new sVertex[numberOfVertsOnGPU];
	//	delete [] pVertices;		// If it's an array, also use [] bracket

	exit(EXIT_SUCCESS);
}


// 

// returns NULL (0) if we didn't find it.
GameObject* pFindObjectByFriendlyName(std::string name)
{
	// Do a linear search 
	for (unsigned int index = 0;
		 index != g_vec_pGameObjects.size(); index++)
	{
		if (::g_vec_pGameObjects[index]->friendlyName == name)
		{
			// Found it!!
			return ::g_vec_pGameObjects[index];
		}
	}
	// Didn't find it
	return NULL;
}

// returns NULL (0) if we didn't find it.
GameObject* pFindObjectByFriendlyNameMap(std::string name)
{
	//std::map<std::string, GameObject*> g_map_GameObjectsByFriendlyName;
	return ::g_map_GameObjectsByFriendlyName[name];
}



