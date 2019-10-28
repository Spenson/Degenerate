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
#include "CameraManager.h"

#include "ShaderManager.h"

#include <sstream>

#include <limits.h>
#include <float.h>

// The Physics function
#include "PhysicsStuff.h"
#include "cPhysics.h"

#include "cLowPassFilter.h"
//#include "DebugRenderer/cDebugRenderer.h"

// Used to visualize the attenuation of the lights...
#include "LightHelper.h"

// Keyboard, error, mouse, etc. are now here
#include "GFLW_callbacks.h"
#include "LightManager.h"

#include "FileReaders.h"


void DrawObject(glm::mat4 m, GameObject* pCurrentObject, GLint shaderProgID, VAOManager* pVAOManager);
glm::mat4 calculateWorldMatrix(GameObject* pCurrentObject);
bool bLightDebugSheresOn = false;



// Load up my "scene"  (now global)
std::vector<GameObject*> g_vec_pGameObjects;
std::map<std::string /*FriendlyName*/, GameObject*> g_map_GameObjectsByFriendlyName;

std::map<std::string, Mesh> mMeshes;
LightManager lightMan;

//bool g_BallCollided = false;


//global so these are seen by the draw call... TODO: Find a better way if needed
GLint matModel_UL;
GLint matModelIT_UL;
GLint diffuseColour_UL;
GLint specularColour_UL;
GLint debugColour_UL;
GLint bDoNotLight_UL;
GLint newColour_location;


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




	ShaderManager* pTheShaderManager = new ShaderManager();

	ShaderManager::Shader vertexShad;
	vertexShad.fileName = "../assets/shaders/vertexShader01.glsl";

	ShaderManager::Shader fragShader;
	fragShader.fileName = "../assets/shaders/fragmentShader01.glsl";

	if (!pTheShaderManager->createProgramFromFile("SimpleShader", vertexShad, fragShader))
	{
		std::cout << "Error: didn't compile the shader" << std::endl;
		std::cout << pTheShaderManager->getLastError();
		return -1;
	}

	GLuint shaderProgID = pTheShaderManager->getIDFromFriendlyName("SimpleShader");


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

	for (unsigned int index = 0;
		 index != ::g_vec_pGameObjects.size(); index++)
	{
		if (::g_vec_pGameObjects[index]->physicsShapeType == MESH)
		{
			::g_vec_pGameObjects[index]->matWorld = calculateWorldMatrix(::g_vec_pGameObjects[index]);
		}
	}


	// Will be moved placed around the scene
	GameObject* pDebugSphere = new GameObject();
	pDebugSphere->meshName = "sphere";
	pDebugSphere->friendlyName = "debug_sphere";
	pDebugSphere->position = glm::vec3(0.0f, 0.0f, 0.0f);
	pDebugSphere->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
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


	GLint eyeLocation_UL = glGetUniformLocation(shaderProgID, "eyeLocation");

	GLint matView_UL = glGetUniformLocation(shaderProgID, "matView");
	GLint matProj_UL = glGetUniformLocation(shaderProgID, "matProj");

	// Declared above in global. TODO: As above
	matModel_UL = glGetUniformLocation(shaderProgID, "matModel");
	matModelIT_UL = glGetUniformLocation(shaderProgID, "matModelInverseTranspose");
	diffuseColour_UL = glGetUniformLocation(shaderProgID, "diffuseColour");
	specularColour_UL = glGetUniformLocation(shaderProgID, "specularColour");
	debugColour_UL = glGetUniformLocation(shaderProgID, "debugColour");
	bDoNotLight_UL = glGetUniformLocation(shaderProgID, "bDoNotLight");
	newColour_location = glGetUniformLocation(shaderProgID, "newColour");


	std::string lighterrors;

	std::vector<Light*> templights;

	ReadLightsFromFile("../assets/config/Lights.xml", lightMan);

	lightMan.InitilizeLightUinformLocations(shaderProgID, "theLights", 10, lighterrors);
	//Light* sexyLight = lightMan.GetLight(0);

	CameraManager::GetCameraInstance()->SetPosition(glm::vec3(6000.0f, 3000.0f, 7000.0f));
	CameraManager::GetCameraInstance()->LookRight(145);
	CameraManager::GetCameraInstance()->LookUp(-18);

	double TimeSinceAsteroid = 0.0;
	unsigned AsteroidCount = 0;

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
							 1.0f,			// Near clipping plane
							 25000.0f);		// Far clipping plane

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

		TimeSinceAsteroid += avgDeltaTimeThingy.getAverage();

		if (TimeSinceAsteroid > 1.0)
		{
			GameObject* newAstroid = new GameObject();
			newAstroid->friendlyName = "Asteroid" + std::to_string(AsteroidCount);
			newAstroid->position.z = 4000.0;
			newAstroid->position.x = (rand() % 15000) - 7500.0;
			newAstroid->position.y = (rand() % 15000) - 7500.0;
			newAstroid->velocity.z = -((rand() % 1000) + 1);
			newAstroid->velocity.x = 0;
			newAstroid->velocity.y = 0;
			newAstroid->scale = glm::vec3(1.0f);
			newAstroid->physicsShapeType = SPHERE;
			newAstroid->objectColour = glm::vec4(((rand() % 60) * 0.01) + 0.2);
			newAstroid->specularColour = glm::vec4(1.0f, 1.0f, 1.0f, 0.01f);
			newAstroid->inverseMass = 1.0f;
			newAstroid->isWireframe = 0;
			newAstroid->isVisible = 1;
			newAstroid->disableDepthBufferTest = 0;
			newAstroid->disableDepthBufferWrite = 0;



			int AstroidMeshNumber = rand() % 3;
			newAstroid->meshName = "Asteroid" + std::to_string(AstroidMeshNumber);
			newAstroid->SPHERE_radius = (AstroidMeshNumber = 0 ? 55.9f : AstroidMeshNumber = 1 ? 24.4f : 80.6f);
			if (AstroidMeshNumber == 1)
			{
				newAstroid->SPHERE_radius *= 2;
				newAstroid->scale *= 2;
			}

			::g_vec_pGameObjects.push_back(newAstroid);

			std::cout << ::g_vec_pGameObjects.size() << std::endl;
			AsteroidCount++;
			//TimeSinceAsteroid = 0.0;
		}




		//		pPhsyics->IntegrationStep(::g_vec_pGameObjects, 0.01f);
		//		pPhsyics->IntegrationStep(::g_vec_pGameObjects, (float)deltaTime);
		pPhsyics->IntegrationStep(::g_vec_pGameObjects, (float)avgDeltaTimeThingy.getAverage());
		pPhsyics->TestForCollisions(::g_vec_pGameObjects);
		// Let's draw all the closest points to the sphere
		// on the terrain mesh....
		// 
		// For each triangle in the terrain mesh:
		// - Run ClosestPointToTriangle
		// - Place the debug sphere "there"
		// - Draw it.


		//Remove astroids to far away to matter && remove destroyed items
		for (std::vector<GameObject*>::iterator it = ::g_vec_pGameObjects.begin(); it != ::g_vec_pGameObjects.end(); it++)
		{
			if ((*it) == nullptr)
			{
				::g_vec_pGameObjects.erase(it);
			}
			else if ((*it)->position.z < -20000 || (*it)->position.z > 20000 ||
				(*it)->position.x < -20000 || (*it)->position.x > 20000 ||
				(*it)->position.y < -20000 || (*it)->position.y > 20000)
			{
				delete (*it);
				::g_vec_pGameObjects.erase(it);
			}
		}


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


void DrawObject(glm::mat4 m,
				GameObject* pCurrentObject,
				GLint shaderProgID,
				VAOManager* pVAOManager)
{
	// mat4x4_identity(m);
	m = calculateWorldMatrix(pCurrentObject); glm::mat4(1.0f);



	//uniform mat4 matModel;		// Model or World 
	//uniform mat4 matView; 		// View or camera
	//uniform mat4 matProj;


	glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(m));
	//glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
	//glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));

	// Calcualte the inverse transpose of the model matrix and pass that...
	// Stripping away scaling and translation, leaving only rotation
	// Because the normal is only a direction, really


	glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(m));
	glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));


	// Find the location of the uniform variable newColour

	glUniform3f(newColour_location,
				pCurrentObject->objectColour.r,
				pCurrentObject->objectColour.g,
				pCurrentObject->objectColour.b);

	//uniform float newColourRed;
	//uniform float newColourGreen;
	//uniform float newColourBlue;
	//GLint newColourRed_UL = glGetUniformLocation(shaderProgID, "newColourRed");
	//GLint newColourGreen_UL = glGetUniformLocation(shaderProgID, "newColourGreen");
	//GLint newColourBlue_UL = glGetUniformLocation(shaderProgID, "newColourBlue");

	//glUniform1f(newColourRed_UL, pCurrentObject->objectColourRGBA.r);
	//glUniform1f(newColourGreen_UL, pCurrentObject->objectColourRGBA.g);
	//glUniform1f(newColourBlue_UL, pCurrentObject->objectColourRGBA.b);
	//GLint lighPosition_UL = glGetUniformLocation(shaderProgID, "lightPosition");
	//glUniform3f(lighPosition_UL, sexyLightLocation.x,
	//			sexyLightLocation.y, sexyLightLocation.z);

	glUniform4f(diffuseColour_UL,
				pCurrentObject->objectColour.r,
				pCurrentObject->objectColour.g,
				pCurrentObject->objectColour.b,
				pCurrentObject->objectColour.a);	// 

	glUniform4f(specularColour_UL,
				1.0f,	// R
				1.0f,	// G
				1.0f,	// B
				1000.0f);	// Specular "power" (how shinny the object is)
							// 1.0 to really big (10000.0f)


	//uniform vec4 debugColour;
	//uniform bool bDoNotLight;

	if (pCurrentObject->isWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES
		glUniform4f(debugColour_UL,
					pCurrentObject->debugColour.r,
					pCurrentObject->debugColour.g,
					pCurrentObject->debugColour.b,
					pCurrentObject->debugColour.a);
		glUniform1f(bDoNotLight_UL, (float)GL_TRUE);
	}
	else
	{	// Regular object (lit and not wireframe)
		glUniform1f(bDoNotLight_UL, (float)GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
	}
	//glPointSize(15.0f);

	if (pCurrentObject->disableDepthBufferTest)
	{
		glDisable(GL_DEPTH_TEST);					// DEPTH Test OFF
	}
	else
	{
		glEnable(GL_DEPTH_TEST);						// Turn ON depth test
	}

	if (pCurrentObject->disableDepthBufferWrite)
	{
		glDisable(GL_DEPTH);						// DON'T Write to depth buffer
	}
	else
	{
		glEnable(GL_DEPTH);								// Write to depth buffer
	}


	//		glDrawArrays(GL_TRIANGLES, 0, 2844);
	//		glDrawArrays(GL_TRIANGLES, 0, numberOfVertsOnGPU);

	ModelDrawInfo drawInfo;
	//if (pTheVAOManager->FindDrawInfoByModelName("bunny", drawInfo))
	if (pVAOManager->FindDrawInfoByModelName(pCurrentObject->meshName, drawInfo))
	{
		glBindVertexArray(drawInfo.VAO_ID);
		glDrawElements(GL_TRIANGLES,
					   drawInfo.numberOfIndices,
					   GL_UNSIGNED_INT,
					   0);
		glBindVertexArray(0);
	}

	return;
} // DrawObject;
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


// This is JUST the transformation lines from the DrawObject call
glm::mat4 calculateWorldMatrix(GameObject* pCurrentObject)
{

	glm::mat4 matWorld = glm::mat4(1.0f);


	// ******* TRANSLATION TRANSFORM *********
	glm::mat4 matTrans
		= glm::translate(glm::mat4(1.0f),
						 glm::vec3(pCurrentObject->position.x,
								   pCurrentObject->position.y,
								   pCurrentObject->position.z));
	matWorld = matWorld * matTrans;
	// ******* TRANSLATION TRANSFORM *********



	// ******* ROTATION TRANSFORM *********
	//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotation.z,					// Angle 
									glm::vec3(0.0f, 0.0f, 1.0f));
	matWorld = matWorld * rotateZ;

	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotation.y,	//(float)glfwGetTime(),					// Angle 
									glm::vec3(0.0f, 1.0f, 0.0f));
	matWorld = matWorld * rotateY;

	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotation.x,	// (float)glfwGetTime(),					// Angle 
									glm::vec3(1.0f, 0.0f, 0.0f));
	matWorld = matWorld * rotateX;
	// ******* ROTATION TRANSFORM *********



	// ******* SCALE TRANSFORM *********
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
								 glm::vec3(pCurrentObject->scale.x,
										   pCurrentObject->scale.y,
										   pCurrentObject->scale.z));
	matWorld = matWorld * scale;
	// ******* SCALE TRANSFORM *********


	return matWorld;
}
