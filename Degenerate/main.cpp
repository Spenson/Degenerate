#include "globals.h"

#include <iostream>

#include "UserInputs/GFLW_callbacks.h"
#include "Camera/cFlyCamera.h"
#include "Camera/ThirdPersonCamera.h"
#include "DebugRenderer/cDebugRenderer.h"
#include "ModelStuff/cModelLoader.h"
#include "VAOManager/cVAOManager.h"
#include "SimpleShaderStuff/UniformManager.h"
#include "ParticalEffects/cParticleEmitter.h"
#include "Physics/cPhysics.h"
#include "LowPassFilter/cLowPassFilter.h"
#include "Lighting/cLightHelper.h"
#include "SimpleShaderStuff/Rendering.h"

#include "LoadingStuff/LoadScene.h"
#include "Physics/SubdivideWorld.h"

#include <glm/gtc/type_ptr.hpp>

#include <sstream>



cFlyCamera* g_pFlyCamera = NULL;
cBasicTextureManager* g_pTextureManager = NULL;

bool bLightDebugSheresOn = false;

extern cGameObject* g_pDebugSphere;
extern cGameObject* g_pDebugCube;

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










	//TODO: Move if needed
	cDebugRenderer* pDebugRenderer = new cDebugRenderer();
	pDebugRenderer->initialize();


	cModelLoader* pTheModelLoader = new cModelLoader();	// Heap

	cVAOManager* pTheVAOManager = new cVAOManager();

	UniformManager::Init();

	// Texture stuff
	::g_pTextureManager = new cBasicTextureManager();

	cLightHelper* pLightHelper = new cLightHelper();

	std::string lighterrors;
	::g_pLightManager = new LightManager();
	::g_pLightManager->InitilizeLightUinformLocations(UniformManager::shaderProgID, "theLights", 50, lighterrors);

	//TODO: Rewrite Loading Model stuff
	TestLoad(pTheVAOManager, pTheModelLoader, UniformManager::shaderProgID, pDebugRenderer, ::g_vec_pGameObjects, ::g_pLightManager, ::g_pTextureManager);






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



	//: Switch to my camera

	//::g_pFlyCamera = new cFlyCamera();
	//::g_pFlyCamera->eye = glm::vec3(0.0f, 80.0, -80.0);


	glEnable(GL_DEPTH);			// Write to the depth buffer
	glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing


	cPhysics* pPhsyics = new cPhysics();
	pPhsyics->setGravity(glm::vec3(0.0f));

	cLowPassFilter avgDeltaTimeThingy;


	double lastTime = glfwGetTime();

	cGameObject* collisionShpere = new cGameObject();
	//collisionShpere->diffuseColour = glm::vec4(0.8f, 0.2f, 0.2f, 0.5f);
	collisionShpere->debugColour = glm::vec4(0.8f, 0.2f, 0.2f, 1.0f);
	collisionShpere->doNotLight = true;
	//collisionShpere->specularColour = glm::vec4(0.0f);
	collisionShpere->meshName = "sphere_lowres";
	collisionShpere->friendlyName = "collision";
	//collisionShpere->positionXYZ = closestPoint;
	collisionShpere->scale = 0.5f;
	collisionShpere->useDiffuse = true;


	ThirdPersonCamera tpc;
	tpc.SetPlayerObject(pFindObjectByFriendlyName("Ship"));
	tpc.SetPositionRelitiveToObject(glm::vec3(0.0f, 10.0f, -50.0f));
	tpc.SetTargetRelitiveToObject(glm::vec3(0.0f, 10.0f, 0.0f));


	for (cGameObject* object : ::g_vec_pGameObjects)
	{
		object->setDebugRenderer(pDebugRenderer);
	}

	std::vector<glm::vec3> todraw;
	while (!glfwWindowShouldClose(window))
	{

		////spin light for testing new light rotation
		//lights[0]->Rotation = glm::vec3(temp,0.0f,0.0f);
		//temp += 1.0f;


		for (size_t index = 0; index != (::g_vec_pGameObjects.size() - 1); index++)
		{
			glm::vec3 ObjA = ::g_vec_pGameObjects[index]->positionXYZ;
			glm::vec3 ObjB = ::g_vec_pGameObjects[index + 1]->positionXYZ;

			//if (glm::distance(ObjA, ::g_pFlyCamera->eye) < glm::distance(ObjB, ::g_pFlyCamera->eye))
			//if (glm::distance(ObjA, ::g_pFreeCamera->GetPosition()) < glm::distance(ObjB, ::g_pFreeCamera->GetPosition()))
			if (glm::distance(ObjA, tpc.Position()) < glm::distance(ObjB, tpc.Position()))
			{
				// Out of order, so swap the positions...
				//cGameObject* pTemp = ::g_vec_pGameObjects[index];
				//::g_vec_pGameObjects[index] = ::g_vec_pGameObjects[index + 1];
				//::g_vec_pGameObjects[index + 1] = pTemp;
				std::swap(::g_vec_pGameObjects[index], ::g_vec_pGameObjects[index + 1]);
			}
		}// for (unsigned int index


		//Frame Time
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		lastTime = currentTime;
		const double SOME_HUGE_TIME = 0.1;	// 100 ms;
		if (deltaTime > SOME_HUGE_TIME)
			deltaTime = SOME_HUGE_TIME;

		avgDeltaTimeThingy.addValue(deltaTime);





		//Frame Rate in title bar
		std::stringstream ssTitle;
		ssTitle << "Degenerate | " << 1.0 / avgDeltaTimeThingy.getAverage() << " (" << 1.0 / deltaTime << " | " << deltaTime << ")" 
			<< " Pos: (" << pFindObjectByFriendlyName("Ship")->positionXYZ.x << ", " 
			<< pFindObjectByFriendlyName("Ship")->positionXYZ.y << ", " 
			<< pFindObjectByFriendlyName("Ship")->positionXYZ.z << ")";
		glfwSetWindowTitle(window, ssTitle.str().c_str());









		ProcessAsyncKeys(window);
		ProcessAsyncMouse(window);

		glUseProgram(UniformManager::shaderProgID);

		float ratio;
		int width, height;
		glm::mat4 p, v;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		p = glm::perspective(0.6f, ratio, 0.5f, 10000.0f);
		v = glm::mat4(1.0f);
		//v = glm::lookAt(::g_pFlyCamera->eye, ::g_pFlyCamera->getAtInWorldSpace(), ::g_pFlyCamera->getUpVector());
		//v = glm::lookAt(::g_pFreeCamera->GetPosition(), ::g_pFreeCamera->GetTarget(), ::g_pFreeCamera->GetUpVector());
		v = glm::lookAt(tpc.Position(), tpc.Target(), tpc.UpVector());

		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		g_pLightManager->PassLightsToShader();


		//glUniform4f(UniformManager::eyeLocation_UL, ::g_pFreeCamera->GetPosition().x, ::g_pFreeCamera->GetPosition().y, ::g_pFreeCamera->GetPosition().z, 1.0f);
		glUniform4f(UniformManager::eyeLocation_UL, tpc.Position().x, tpc.Position().y, tpc.Position().z, 1.0f);

		glUniformMatrix4fv(UniformManager::matView_UL, 1, GL_FALSE, glm::value_ptr(v));
		glUniformMatrix4fv(UniformManager::matProj_UL, 1, GL_FALSE, glm::value_ptr(p));



		cGameObject* pSkyBox = pFindObjectByFriendlyName("skybox");
		//pSkyBox->positionXYZ = ::g_pFreeCamera->GetPosition();// ::g_pFlyCamera->eye;
		pSkyBox->positionXYZ = tpc.Position();

		DrawObject(glm::mat4(1.0f), pSkyBox, UniformManager::shaderProgID, pTheVAOManager);

		for (int index = 0; index != ::g_vec_pGameObjects.size(); index++)
		{
			cGameObject* pCurrentObject = ::g_vec_pGameObjects[index];
			if (pCurrentObject->friendlyName == "skybox")
				continue;

			glm::mat4 matModel = glm::mat4(1.0f);	// Identity matrix

			DrawObject(matModel, pCurrentObject, UniformManager::shaderProgID, pTheVAOManager);

		}//for (int index = 0; index != ::g_vec_pGameObjects.size(); index++)




		//pFindObjectByFriendlyName("Ship")->positionXYZ.x += 0.51f;
		cGameObject* pObject = pFindObjectByFriendlyName("Ship");

		std::vector<glm::vec3> points = pObject->vecPhysTestPoints;
		glm::mat4 shipMat = calculateWorldMatrix(pObject, glm::mat4(1.0));
		for (size_t i = 0; i < points.size(); i++)
		{
			glm::vec3 point = glm::vec3(shipMat * glm::vec4(points[i], 1.0f));

			/*	::g_pDebugSphere->scale = 0.5f;
				::g_pDebugSphere->isWireframe = true;
				::g_pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
				::g_pDebugSphere->positionXYZ = point;
				DrawObject(glm::mat4(1.0f), ::g_pDebugSphere, UniformManager::shaderProgID, pTheVAOManager);*/



			if (WorldRegion::mapRegions.find(WorldRegion::GenerateID(point)) != WorldRegion::mapRegions.end())
			{
				WorldRegion* wr = WorldRegion::mapRegions[WorldRegion::GenerateID(point)];

				if (!wr->vecTriangles.empty())
				{
					//REGION HAS TRIANGLES DRAW CUBE
					::g_pDebugCube->positionXYZ = wr->center;
					::g_pDebugCube->scale = WorldRegion::HalfLength();
					::g_pDebugCube->isWireframe = true;
					::g_pDebugCube->isVisible = true;
					glm::mat4 matModel = glm::mat4(1.0f);
					DrawObject(matModel, ::g_pDebugCube, UniformManager::shaderProgID, pTheVAOManager);


				/*	glm::vec3 closestPoint = glm::vec3(0.0f);
					size_t closestIdx = -1;
					float closestDist = FLT_MAX;
					UnraveiledTriangle* tri = nullptr;// = new UnraveiledTriangle();//WorldRegion::AllTriangles[0];


					for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)
					{
						UnraveiledTriangle* currentTri = WorldRegion::AllTriangles[*i];
						glm::vec3 curClosestPoint = pPhsyics->ClosestPtPointTriangle(point, currentTri->a, currentTri->b, currentTri->c);

						if (glm::dot(glm::normalize(pObject->positionXYZ - closestPoint), glm::normalize((currentTri->an + currentTri->bn + currentTri->cn) / 3.0f)) <= 0.0f)
							continue;

						if (glm::distance(curClosestPoint, point) < closestDist)
						{
							closestDist = glm::distance(curClosestPoint, point);
							closestPoint = curClosestPoint;
							closestIdx = *i;
							tri = currentTri;
						} // if (glm::distance(curClosestPoint, point) < closestDist)
					} // for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)

					if (closestIdx == -1)
					{
						for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)
						{
							UnraveiledTriangle* currentTri = WorldRegion::AllTriangles[*i];
							glm::vec3 curClosestPoint = pPhsyics->ClosestPtPointTriangle(point, currentTri->a, currentTri->b, currentTri->c);

							if (glm::distance(curClosestPoint, point) < closestDist)
							{
								closestDist = glm::distance(curClosestPoint, point);
								closestPoint = curClosestPoint;
								closestIdx = *i;
								tri = currentTri;
							} // if (glm::distance(curClosestPoint, point) < closestDist)
						} // for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)
					}

					//tri = WorldRegion::AllTriangles[closestIdx];
					//TODO: calc face normal
					glm::vec3 norm = glm::normalize((tri->an + tri->bn + tri->cn) / 3.0f);

					/*::g_pDebugSphere->scale = 0.5f;
					::g_pDebugSphere->isWireframe = true;
					::g_pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
					::g_pDebugSphere->positionXYZ = closestPoint;
					DrawObject(glm::mat4(1.0f), ::g_pDebugSphere, UniformManager::shaderProgID, pTheVAOManager);

					pDebugRenderer->addLine(closestPoint, (closestPoint + (norm * 10.0f)), glm::vec3(1.0f));


					if (glm::dot(glm::normalize(point - closestPoint), norm) <= 0.0f)
					{
						//if (glm::dot(glm::normalize(pObject->positionXYZ - closestPoint), norm) <= 0.0f) // your center is behind closest tri / are right inside an object
						//{
						//	// Loop through and find proper triangle
						//	for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)
						//	{
						//		UnraveiledTriangle* currentTri = WorldRegion::AllTriangles[*i];
						//		glm::vec3 curClosestPoint = pPhsyics->ClosestPtPointTriangle(point, currentTri->a, currentTri->b, currentTri->c);


						//		//glm::vec3 norm = glm::normalize((currentTri->an + currentTri->bn + currentTri->cn) / 3.0f);
						//		// Is center behind triangle
						//		if (glm::dot(glm::normalize(pObject->positionXYZ - closestPoint), glm::normalize((currentTri->an + currentTri->bn + currentTri->cn) / 3.0f)) <= 0.0f)
						//			continue;
						//		//tri = WorldRegion::AllTriangles[*i];
						//		//glm::vec3 curClosestPoint = pPhsyics->ClosestPtPointTriangle(point, tri->a, tri->b, tri->c);

						//		if (glm::distance(curClosestPoint, point) < closestDist)
						//		{
						//			closestDist = glm::distance(curClosestPoint, point);
						//			closestPoint = curClosestPoint;
						//			closestIdx = *i;
						//			tri = currentTri;
						//		} // if (glm::distance(curClosestPoint, point) < closestDist)
						//	} // for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)
						//} // if (closestIdx == -1)

						cGameObject* collisionShpere = new cGameObject();
						collisionShpere->diffuseColour = glm::vec4(0.8f, 0.2f, 0.2f, 0.5f);
						collisionShpere->specularColour = glm::vec4(0.0f);
						collisionShpere->meshName = "sphere_lowres";
						collisionShpere->friendlyName = "collision";
						collisionShpere->positionXYZ = closestPoint;
						collisionShpere->scale = 0.5f;
						collisionShpere->useDiffuse = true;

						::g_vec_pGameObjects.push_back(collisionShpere);

						pObject->positionXYZ += norm * glm::distance(point, closestPoint);
						pObject->velocity = glm::vec3(0.0f);
						//break;
					}

					*/

				} // if (!wr->vecTriangles.empty())
			} // if (WorldRegion::mapRegions.find(WorldRegion::GenerateID(point)) != WorldRegion::mapRegions.end())
		} // for (size_t i = 0; i < points.size(); i++)






		double averageDeltaTime = avgDeltaTimeThingy.getAverage();

		// TODO: Update to include Angular Velocity
		pPhsyics->IntegrationStep(::g_vec_pGameObjects, deltaTime);//(float)averageDeltaTime);


		
		pPhsyics->TestForCollisions(::g_vec_pGameObjects, todraw);






		for (size_t i = 0; i < todraw.size(); i++)
		{
			collisionShpere->positionXYZ = todraw[i];
			DrawObject(glm::mat4(1.0f), collisionShpere, UniformManager::shaderProgID, pTheVAOManager);
		}











		// TODO: Add Back in (Possibly in separate methond)

		if (bLightDebugSheresOn)
		{
			{// Draw where the light is at
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = g_pLightManager->GetLastLight()->Position;
				::g_pDebugSphere->scale = 0.5f;
				::g_pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   UniformManager::shaderProgID, pTheVAOManager);
			}

			// Draw spheres to represent the attenuation...
			{   // Draw a sphere at 1% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = g_pLightManager->GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.01f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					g_pLightManager->GetLastLight()->ConstAtten,
					g_pLightManager->GetLastLight()->LinearAtten,
					g_pLightManager->GetLastLight()->QuadraticAtten);
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   UniformManager::shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 25% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = g_pLightManager->GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.25f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					g_pLightManager->GetLastLight()->ConstAtten,
					g_pLightManager->GetLastLight()->LinearAtten,
					g_pLightManager->GetLastLight()->QuadraticAtten);
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   UniformManager::shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 50% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = g_pLightManager->GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.50f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					g_pLightManager->GetLastLight()->ConstAtten,
					g_pLightManager->GetLastLight()->LinearAtten,
					g_pLightManager->GetLastLight()->QuadraticAtten);
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   UniformManager::shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 75% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = g_pLightManager->GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.75f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					g_pLightManager->GetLastLight()->ConstAtten,
					g_pLightManager->GetLastLight()->LinearAtten,
					g_pLightManager->GetLastLight()->QuadraticAtten);
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   UniformManager::shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 95% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				::g_pDebugSphere->positionXYZ = g_pLightManager->GetLastLight()->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.95f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					g_pLightManager->GetLastLight()->ConstAtten,
					g_pLightManager->GetLastLight()->LinearAtten,
					g_pLightManager->GetLastLight()->QuadraticAtten);
				::g_pDebugSphere->scale = sphereSize;
				::g_pDebugSphere->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
				::g_pDebugSphere->isWireframe = true;
				DrawObject(matModel, ::g_pDebugSphere,
						   UniformManager::shaderProgID, pTheVAOManager);
			}
		}// if (bLightDebugSheresOn) 

		pMyPartcles->location = glm::vec3(0.0f);

		pMyPartcles->Step(static_cast<float>(deltaTime));



		// TODO:Partical Effect
		//std::vector<cParticle*> vecParticles;
		//pMyPartcles->getParticles(vecParticles);
		//for (std::vector<cParticle*>::iterator itPart = vecParticles.begin();
		//	 itPart != vecParticles.end(); itPart++)
		//{
		//	// This is a little odd, because of the iterator syntax
		//	//pDebugSphere->positionXYZ = (*itPart)->location;
		//	//DrawObject(matModel, pDebugSphere,
		//	//		   shaderProgID, pTheVAOManager);

		//	glm::mat4 matModel = glm::mat4(1.0f);

		//	pBunny->positionXYZ = (*itPart)->location;
		//	DrawObject(matModel, pBunny,
		//			   shaderProgID, pTheVAOManager);
		//}


		pDebugRenderer->RenderDebugObjects(v, p, 0.01f);



		glfwSwapBuffers(window);
		glfwPollEvents();


	}
	glfwDestroyWindow(window);
	glfwTerminate();

	delete pTheModelLoader;
	delete ::g_pFlyCamera;


	exit(EXIT_SUCCESS);
}



// Here because didn't know where else to put it and needed for the draw call
glm::mat4 calculateWorldMatrix(cGameObject* pCurrentObject, glm::mat4 matWorld)
{
	// ******* TRANSLATION TRANSFORM *********
	glm::mat4 matTrans
		= glm::translate(glm::mat4(1.0f),
						 glm::vec3(pCurrentObject->positionXYZ.x,
								   pCurrentObject->positionXYZ.y,
								   pCurrentObject->positionXYZ.z));
	matWorld = matWorld * matTrans;
	// ******* TRANSLATION TRANSFORM *********




	//// ******* ROTATION TRANSFORM *********
	glm::mat4 matRotation = glm::mat4(pCurrentObject->getQOrientation());
	matWorld = matWorld * matRotation;
	// ******* ROTATION TRANSFORM *********




	// ******* SCALE TRANSFORM *********
	// TODO: change to vec3 scale
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
								 glm::vec3(pCurrentObject->scale,
										   pCurrentObject->scale,
										   pCurrentObject->scale));
	matWorld = matWorld * scale;
	// ******* SCALE TRANSFORM *********


	return matWorld;
}