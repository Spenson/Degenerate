#include "GLCommon.h"

#include "globals.h"

#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
// glm::translate, glm::rotate, glm::scale, glm::perspective
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

//#include "cLowPassFilter.h"
//#include "DebugRenderer/cDebugRenderer.h"

// Used to visualize the attenuation of the lights...
#include "LightHelper.h"

// Keyboard, error, mouse, etc. are now here
#include "GFLW_callbacks.h"
#include "LightManager.h"

#include "FileReaders.h"


void DrawObject(glm::mat4 m, GameObject* pCurrentObject, GLint shaderProgID, VAOManager* pVAOManager);
glm::mat4 calculateWorldMatrix(GameObject* pCurrentObject);
bool bLightDebugSheresOn = true;



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

	window = glfwCreateWindow(1280, 720, "Simple example", NULL, NULL);
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

	//if (!pTheModelLoader->LoadPlyModel("../assets/models/bun_zipper_XYZ_n.ply", mMeshes["bunnyMesh"]))
	//{
	//	std::cout << "Didn't find the file" << std::endl;
	//}

	//pTheModelLoader->LoadPlyModel("../assets/models/Large_Physics_Bunny_XYZ_N.ply", mMeshes["largeBunnyMesh"]);
	//pTheModelLoader->LoadPlyModel("../assets/models/Sky_Pirate_Combined_xyz_n.ply", mMeshes["pirateMesh"]);
	//pTheModelLoader->LoadPlyModel("../assets/models/Terrain_XYZ_n.ply", mMeshes["terrainMesh"]);
	////	pTheModelLoader->LoadPlyModel("assets/models/BigFlatTerrain_XYZ_n.ply", mapMeshes["terrainMesh"]);
	//pTheModelLoader->LoadPlyModel("../assets/models/Cube_1_Unit_from_origin_XYZ_n.ply", mMeshes["cubeMesh"]);
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


	// Will be moved placed around the scene
	GameObject* pDebugSphere = new GameObject();
	pDebugSphere->meshName = "sphere";
	pDebugSphere->friendlyName = "debug_sphere";
	pDebugSphere->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pDebugSphere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pDebugSphere->scale = 0.1f;
	//	pDebugSphere->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	pDebugSphere->isWireframe = true;
	pDebugSphere->inverseMass = 0.0f;			// Sphere won't move




	//veGameObjects.push_back(pirate);			// veGameObjects[0]
	//veGameObjects.push_back(bunny);		
	//veGameObjects.push_back(bunny2);
//	veGameObjects.push_back(terrain);

	//mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);


	glEnable(GL_DEPTH);			// Write to the depth buffer
	glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing

	//float shipVelocityZ = 1.0f;
	//float shipAccelz = 1000.0f;


	cPhysics* pPhsyics = new cPhysics();

	//cLowPassFilter avgDeltaTimeThingy;


	LightHelper* pLightHelper = new LightHelper();

	// Get the initial time
	double lastTime = glfwGetTime();



	// TODO: LIGHT MANAGER AND LOOPS (50 Lights all off till turned on)

	//GLint L_0_position = glGetUniformLocation(shaderProgID, "theLights[0].position");
	//GLint L_0_diffuse = glGetUniformLocation(shaderProgID, "theLights[0].diffuse");
	//GLint L_0_specular = glGetUniformLocation(shaderProgID, "theLights[0].specular");
	//GLint L_0_atten = glGetUniformLocation(shaderProgID, "theLights[0].atten");
	//GLint L_0_direction = glGetUniformLocation(shaderProgID, "theLights[0].direction");
	//GLint L_0_param1 = glGetUniformLocation(shaderProgID, "theLights[0].param1");
	//GLint L_0_param2 = glGetUniformLocation(shaderProgID, "theLights[0].param2");

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

	ReadLightsFromFile("../assets/config/Lights.xml", templights);

	lightMan.GenerateLights(templights);
	lightMan.InitilizeLightUinformLocations(shaderProgID, "theLights", lightMan.GetLightCount(), lighterrors);
	//Light* sexyLight = lightMan.GetLight(0);



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

		//avgDeltaTimeThingy.addValue(deltaTime);


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



		// ********************************************************
		// Move the pirate in the direction it's pointing in...

		// Vec4 = mat4x4 * vec4				vertFinal = matModel * vertStart;

		GameObject* pPirate = pFindObjectByFriendlyName("PirateShip");

		//glm::mat4 matRotY = glm::rotate(glm::mat4(1.0f),
		//								pPirate->HACK_AngleAroundYAxis,	//(float)glfwGetTime(),					// Angle 
		//								glm::vec3(0.0f, 1.0f, 0.0f));

		// Assume the ship is at 0,0,0
		glm::vec4 frontOfShip = glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);	// pointing to the "front" of the ship

		// Vec4 = mat4x4 * vec4				vertFinal = matModel * vertStart;
		//glm::vec4 frontOfShipInWorld = matRotY * frontOfShip;

		// this value would be the velocity, ifyou wanted the phsyics update do to it
		//glm::vec3 newSpeedOfShipIN_THE_DIRECTION_WE_WANT_TO_GO
		//	= frontOfShipInWorld * pPirate->HACK_speed;
		//
		//// Draw a line showing where we are going...
		//pDebugRenderer->addLine(pPirate->positionXYZ,
		//						pPirate->positionXYZ + (glm::vec3(frontOfShipInWorld) * pPirate->HACK_speed * 5.0f),
		//						glm::vec3(1.0f, 0.0f, 0.0f), 0.5f);

		// Draw a line showing how fast we are going...

		// Update the pirate ship
		//pPirate->positionXYZ += newSpeedOfShipIN_THE_DIRECTION_WE_WANT_TO_GO;


		//pDebugRenderer->addTriangle( pPirate->positionXYZ, 
		//							 glm::vec3(0.0f,0.0f,0.0f), 
		//							 glm::vec3(0.0f, 10.0f, 0.0f), 
		//							 glm::vec3(0.0f,1.0f,0.0f) );

		//pDebugRenderer->addLine( pPirate->positionXYZ, 
		//						 glm::vec3(0.0f, 10.0f, 0.0f), 
		//						 glm::vec3(0.0f,1.0f,0.0f),
		//						 2.0f );
		// ********************************************************


//	// Point the spot light at the bunny
//	GameObject* pBunny = pFindObjectByFriendlyName("Bugs");
//	GameObject* pPirate = pFindObjectByFriendlyName("PirateShip");
//
//	sexyLightPosition = pPirate->positionXYZ;
//
//	// Vector from the bunny to the ship is:
//	// Bunny_Position - ShipPosition;
//	glm::vec3 bunnyToShip = pBunny->positionXYZ - pPirate->positionXYZ;
//	// Normalize the vector (unit or 1.0f length)
//	sexyLightSpotDirection = glm::normalize(bunnyToShip);


		//// Spot light
		//glUniform4f(L_0_direction, 
		//			sexyLightSpotDirection.x,		// 0
		//			sexyLightSpotDirection.y,		// -1
		//			sexyLightSpotDirection.z,		// 0
		//			1.0f );	

		//glUniform4f(L_0_param1,
		//			1.0f /*SPOT light*/, 
		//			sexyLightSpotInnerAngle,		// 15
		//			sexyLightSpotOuterAngle,		// 30
		//			1.0f );


		//glUniform4f(L_0_param1,
		//			2.0f /*DIRECTIONAL light*/, 
		//			sexyLightSpotInnerAngle,		// 15
		//			sexyLightSpotOuterAngle,		// 30
		//			1.0f );


		//glUniform4f(L_0_param2, 1.0f /*Light is on*/, 0.0f, 0.0f, 1.0f);

		// Also set the position of my "eye" (the camera)
		//uniform vec4 eyeLocation;

		glUniform4f(eyeLocation_UL,
					CameraManager::GetCameraInstance()->GetPosition().x, 
					CameraManager::GetCameraInstance()->GetPosition().y, 
					CameraManager::GetCameraInstance()->GetPosition().z, 1.0f);


		std::stringstream ssTitle;
		ssTitle
			<< lightMan.GetLight(0)->Position.x << ", "
			<< lightMan.GetLight(0)->Position.y << ", "
			<< lightMan.GetLight(0)->Position.z
			<< "Atten: "
			<< lightMan.GetLight(0)->ConstAtten << " : "
			<< lightMan.GetLight(0)->LinearAtten << " : "
			<< lightMan.GetLight(0)->QuadraticAtten;
		glfwSetWindowTitle(window, ssTitle.str().c_str());


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
		//double averageDeltaTime = avgDeltaTimeThingy.getAverage();
		//pPhsyics->IntegrationStep(::g_vec_pGameObjects, (float)averageDeltaTime);

		// Let's draw all the closest points to the sphere
		// on the terrain mesh....
		// 
		// For each triangle in the terrain mesh:
		// - Run ClosestPointToTriangle
		// - Place the debug sphere "there"
		// - Draw it.

		//**********************************************************
		//**********************************************************
		glm::vec3 closestPoint = glm::vec3(0.0f, 0.0f, 0.0f);
		cPhysics::sPhysicsTriangle closestTriangle;

		//pPhsyics->GetClosestTriangleToPoint(pShpere->positionXYZ, mMeshes["largeBunnyMesh"], closestPoint, closestTriangle);

		// Highlight the triangle that I'm closest to
		//pDebugRenderer->addTriangle(closestTriangle.verts[0],
		//							closestTriangle.verts[1],
		//							closestTriangle.verts[2],
		//							glm::vec3(1.0f, 0.0f, 0.0f));

		// Highlight the triangle that I'm closest to
		// To draw the normal, calculate the average of the 3 vertices, 
		// then draw that average + the normal (the normal starts at the 0,0,0 OF THE TRIANGLE)
		glm::vec3 centreOfTriangle = (closestTriangle.verts[0] +
									  closestTriangle.verts[1] +
									  closestTriangle.verts[2]) / 3.0f;		// Average

		glm::vec3 normalInWorld = centreOfTriangle + (closestTriangle.normal * 20.0f);	// Normal x 10 length

		//pDebugRenderer->addLine(centreOfTriangle,
		//						normalInWorld,
		//						glm::vec3(1.0f, 1.0f, 0.0f));

		// Are we hitting the triangle? 
		//float distance = glm::length(pShpere->positionXYZ - closestPoint);

//		if (distance <= pShpere->SPHERE_radius)
//		{
//			// If you want, move the sphere back to where it just penetrated...
//			// So that it will collide exactly where it's supposed to. 
//			// But, that's not a big problem.
//
//
//			// Is in contact with the triangle... 
//			// Calculate the response vector off the triangle. 
//			glm::vec3 velocityVector = glm::normalize(pShpere->velocity);
//
//			// closestTriangle.normal
//			glm::vec3 reflectionVec = glm::reflect(velocityVector, closestTriangle.normal);
//			reflectionVec = glm::normalize(reflectionVec);
//
//			// Stop the sphere and draw the two vectors...
////			pShpere->inverseMass = 0.0f;	// Stopped
//
//			glm::vec3 velVecX20 = velocityVector * 10.0f;
//			//pDebugRenderer->addLine(closestPoint, velVecX20,
//			//						glm::vec3(1.0f, 0.0f, 0.0f), 30.0f /*seconds*/);
//
//			glm::vec3 reflectionVecX20 = reflectionVec * 10.0f;
//			//pDebugRenderer->addLine(closestPoint, reflectionVecX20,
//			//						glm::vec3(0.0f, 1.0f, 1.0f), 30.0f /*seconds*/);
//
//			// Change the direction of the ball (the bounce off the triangle)
//
//			// Get lenght of the velocity vector
//			float speed = glm::length(pShpere->velocity);
//
//			pShpere->velocity = reflectionVec * speed;
//
//		}




		bool DidBallCollideWithGround = false;
		//HACK_BounceOffSomePlanes(pShpere, DidBallCollideWithGround);

		// A more general 
		pPhsyics->TestForCollisions(::g_vec_pGameObjects);





		//**********************************************************
		//**********************************************************




//		float closestDistanceSoFar = FLT_MAX;
//		glm::vec3 closetPoint = glm::vec3(0.0f,0.0f,0.0f);
//		sPlyTriangle closetTriangle;
//
//		for (unsigned int triIndex = 0;
//			 triIndex != mapMeshes["terrainMesh"].vecTriangles.size();
//			 triIndex++)
//		{
//			sPlyTriangle& curTriangle = mapMeshes["terrainMesh"].vecTriangles[triIndex];
//
//			// Get the vertices of the triangle
//			sPlyVertexXYZ_N triVert1 = mapMeshes["terrainMesh"].vecVertices[curTriangle.vert_index_1];
//			sPlyVertexXYZ_N triVert2 = mapMeshes["terrainMesh"].vecVertices[curTriangle.vert_index_2];
//			sPlyVertexXYZ_N triVert3 = mapMeshes["terrainMesh"].vecVertices[curTriangle.vert_index_3];
//
//			Point triVertPoint1;
//			triVertPoint1.x = triVert1.x;
//			triVertPoint1.y = triVert1.y;
//			triVertPoint1.z = triVert1.z;
//
//			Point triVertPoint2;
//			triVertPoint2.x = triVert2.x;
//			triVertPoint2.y = triVert2.y;
//			triVertPoint2.z = triVert2.z;
//
//			Point triVertPoint3;
//			triVertPoint3.x = triVert3.x;
//			triVertPoint3.y = triVert3.y;
//			triVertPoint3.z = triVert3.z;
//
//			glm::vec3 curClosetPoint = ClosestPtPointTriangle( 
//				pShpere->positionXYZ, 
//				triVertPoint1, triVertPoint2, triVertPoint3 );
//			
//			// Is this the closest so far?
//			float distanceNow = glm::distance(curClosetPoint, pShpere->positionXYZ);
//
//			// is this closer than the closest distance
//			if ( distanceNow <= closestDistanceSoFar )
//			{
//				closestDistanceSoFar = distanceNow;
//				closetPoint = curClosetPoint;
//			}
//
//			//glm::mat4 matModel = glm::mat4(1.0f);
//			//pDebugSphere->positionXYZ = closetPoint;
//			//DrawObject(matModel, pDebugSphere, 
//			//			   shaderProgID, pTheVAOManager);
//
//
//		}//for (unsigned int triIndex = 0;

		//{// Draw closest point
		//	glm::mat4 matModel = glm::mat4(1.0f);
		//	pDebugSphere->positionXYZ = closestPoint;
		//	pDebugSphere->scale = 1.0f;
		//	pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
		//	pDebugSphere->isWireframe = true;
		//	DrawObject(matModel, pDebugSphere,
		//			   shaderProgID, pTheVAOManager);
		//}


		// How far did we penetrate the surface?
		//glm::vec3 CentreToClosestPoint = pShpere->positionXYZ - closestPoint;

		// Direction that ball is going is normalized velocity
		//glm::vec3 directionBall = glm::normalize(pShpere->velocity);	// 1.0f

		// Calcualte direction to move it back the way it came from
		//glm::vec3 oppositeDirection = -directionBall;				// 1.0f

		//float distanceToClosestPoint = glm::length(CentreToClosestPoint);

		//pDebugRenderer->addLine(pShpere->positionXYZ,
		//						closestPoint,
		//						glm::vec3(0.0f, 1.0f, 0.0f),
		//						1.0f);




		//		// HACK
		//		if (DidBallCollideWithGround)
		//		{ 
		//			float sphereRadius = 1.0f;
		//			float distanceToMoveBack = sphereRadius - distanceToClosestPoint;
		//
		//			glm::vec3 adjustmentVector = oppositeDirection * distanceToMoveBack;
		//
		//			// Let's move the sphere that amount...
		//			pShpere->positionXYZ += adjustmentVector;
		//
		//
		//			// NOW, I can calculate the correct response vector... 
		//
		////			pShpere->velocity = glm::reflect(pShpere->velocity, triangleNormal)
		//		}


		//std::cout
		//	<< pShpere->velocity.x << ", "
		//	<< pShpere->velocity.y << ", "
		//	<< pShpere->velocity.z << "   dist = "
		//	<< distanceToClosestPoint << std::endl;

		//howMuchToMoveItBack = 1.0 - lenthOfThatVector




		if (bLightDebugSheresOn)
		{
			{// Draw where the light is at
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->positionXYZ = lightMan.GetLight(0)->Position;
				pDebugSphere->scale = 0.5f;
				pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}

			// Draw spheres to represent the attenuation...
			{   // Draw a sphere at 1% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->positionXYZ = lightMan.GetLight(0)->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.01f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLight(0)->ConstAtten,
					lightMan.GetLight(0)->LinearAtten,
					lightMan.GetLight(0)->QuadraticAtten);
				pDebugSphere->scale = sphereSize;
				pDebugSphere->debugColour = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 25% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->positionXYZ = lightMan.GetLight(0)->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.25f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLight(0)->ConstAtten,
					lightMan.GetLight(0)->LinearAtten,
					lightMan.GetLight(0)->QuadraticAtten);
				pDebugSphere->scale = sphereSize;
				pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 50% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->positionXYZ = lightMan.GetLight(0)->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.50f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLight(0)->ConstAtten,
					lightMan.GetLight(0)->LinearAtten,
					lightMan.GetLight(0)->QuadraticAtten);
				pDebugSphere->scale = sphereSize;
				pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 75% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->positionXYZ = lightMan.GetLight(0)->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.75f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLight(0)->ConstAtten,
					lightMan.GetLight(0)->LinearAtten,
					lightMan.GetLight(0)->QuadraticAtten);
				pDebugSphere->scale = sphereSize;
				pDebugSphere->debugColour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
				pDebugSphere->isWireframe = true;
				DrawObject(matModel, pDebugSphere,
						   shaderProgID, pTheVAOManager);
			}
			{   // Draw a sphere at 95% brightness
				glm::mat4 matModel = glm::mat4(1.0f);
				pDebugSphere->positionXYZ = lightMan.GetLight(0)->Position;
				float sphereSize = pLightHelper->calcApproxDistFromAtten(
					0.95f,		// 1% brightness (essentially black)
					0.001f,		// Within 0.1%  
					100000.0f,	// Will quit when it's at this distance
					lightMan.GetLight(0)->ConstAtten,
					lightMan.GetLight(0)->LinearAtten,
					lightMan.GetLight(0)->QuadraticAtten);
				pDebugSphere->scale = sphereSize;
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



	//// ******* TRANSLATION TRANSFORM *********
	//glm::mat4 matTrans
	//	= glm::translate(glm::mat4(1.0f),
	//					 glm::vec3(pCurrentObject->positionXYZ.x,
	//							   pCurrentObject->positionXYZ.y,
	//							   pCurrentObject->positionXYZ.z));
	//m = m * matTrans;
	//// ******* TRANSLATION TRANSFORM *********



	//// ******* ROTATION TRANSFORM *********
	////mat4x4_rotate_Z(m, m, (float) glfwGetTime());
	//glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
	//								pCurrentObject->rotationXYZ.z,					// Angle 
	//								glm::vec3(0.0f, 0.0f, 1.0f));
	//m = m * rotateZ;

	//glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
	//								pCurrentObject->rotationXYZ.y,	//(float)glfwGetTime(),					// Angle 
	//								glm::vec3(0.0f, 1.0f, 0.0f));
	//m = m * rotateY;

	//glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
	//								pCurrentObject->rotationXYZ.x,	// (float)glfwGetTime(),					// Angle 
	//								glm::vec3(1.0f, 0.0f, 0.0f));
	//m = m * rotateX;
	//// ******* ROTATION TRANSFORM *********


	//// ******* SCALE TRANSFORM *********
	//glm::mat4 scale = glm::scale(glm::mat4(1.0f),
	//							 glm::vec3(pCurrentObject->scale,
	//									   pCurrentObject->scale,
	//									   pCurrentObject->scale));
	//m = m * scale;
	//// ******* SCALE TRANSFORM *********



	//mat4x4_mul(mvp, p, m);
	//mvp = p * v * m;

	// Choose which shader to use
	//glUseProgram(program);
	//glUseProgram(shaderProgID);


	//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) mvp);
	//glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

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
				pCurrentObject->objectColourRGBA.r,
				pCurrentObject->objectColourRGBA.g,
				pCurrentObject->objectColourRGBA.b);

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
				pCurrentObject->objectColourRGBA.r,
				pCurrentObject->objectColourRGBA.g,
				pCurrentObject->objectColourRGBA.b,
				pCurrentObject->objectColourRGBA.a);	// 

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
						 glm::vec3(pCurrentObject->positionXYZ.x,
								   pCurrentObject->positionXYZ.y,
								   pCurrentObject->positionXYZ.z));
	matWorld = matWorld * matTrans;
	// ******* TRANSLATION TRANSFORM *********



	// ******* ROTATION TRANSFORM *********
	//mat4x4_rotate_Z(m, m, (float) glfwGetTime());
	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotationXYZ.z,					// Angle 
									glm::vec3(0.0f, 0.0f, 1.0f));
	matWorld = matWorld * rotateZ;

	glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotationXYZ.y,	//(float)glfwGetTime(),					// Angle 
									glm::vec3(0.0f, 1.0f, 0.0f));
	matWorld = matWorld * rotateY;

	glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f),
									pCurrentObject->rotationXYZ.x,	// (float)glfwGetTime(),					// Angle 
									glm::vec3(1.0f, 0.0f, 0.0f));
	matWorld = matWorld * rotateX;
	// ******* ROTATION TRANSFORM *********



	// ******* SCALE TRANSFORM *********
	glm::mat4 scale = glm::scale(glm::mat4(1.0f),
								 glm::vec3(pCurrentObject->scale,
										   pCurrentObject->scale,
										   pCurrentObject->scale));
	matWorld = matWorld * scale;
	// ******* SCALE TRANSFORM *********


	return matWorld;
}
