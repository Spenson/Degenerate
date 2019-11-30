#include "LoadScene.h"
#include "../LoadingStuff/FileReaders.h"
#include "../Physics/SubdivideWorld.h"



cGameObject* g_pDebugSphere;
cGameObject* g_pDebugCube;

// TODO: remove
//cGameObject* pShpere;
//cMesh lowrescubeMesh;
//cGameObject* pHiResCube;
//cMesh singleTriangleMesh;

//cMesh spaceStationMesh;

//sModelDrawInfo largeBunnyDrawInfo;



#include <iostream>
#include <vector>

void TestLoad(cVAOManager* pTheVAOManager, cModelLoader* pTheModelLoader, GLuint shaderProgID,
			  iDebugRenderer* pDebugRenderer, std::vector<cGameObject*>& vec_pGameObjects,
			  LightManager* pLightManager, cBasicTextureManager* pTextureManager)
{

	std::map<std::string, cMesh> mapMeshes;

	LoadMeshesFromXMLFile("assets/config/Meshes.xml", "assets/models/", mapMeshes, pTheModelLoader);

	// Basic Default Meshes
	//CUBE
	if (!pTheModelLoader->LoadPlyModel("assets/models/cube.ply", mapMeshes["cube"]))
		std::cout << "Didn't load mesh: cube" << std::endl;
	else
		std::cout << "Loaded mesh: cube" << std::endl;

	//INVERTED SPHERE HI-RES
	if (!pTheModelLoader->LoadPlyModel("assets/models/inverted_sphere_hires.ply", mapMeshes["inverted_sphere_hires"]))
		std::cout << "Didn't load mesh: inverted_sphere_hires" << std::endl;
	else
		std::cout << "Loaded mesh: inverted_sphere_hires" << std::endl;

	//INVERTED SPHERE LOW-RES
	if (!pTheModelLoader->LoadPlyModel("assets/models/inverted_sphere_lowres.ply", mapMeshes["inverted_sphere_lowres"]))
		std::cout << "Didn't load mesh: inverted_sphere_lowres" << std::endl;
	else
		std::cout << "Loaded mesh: inverted_sphere_lowres" << std::endl;

	//SPHERE LOW-RES
	if (!pTheModelLoader->LoadPlyModel("assets/models/sphere_hires.ply", mapMeshes["sphere_hires"]))
		std::cout << "Didn't load mesh: sphere_hires" << std::endl;
	else
		std::cout << "Loaded mesh: sphere_hires" << std::endl;

	//SPHERE LOW-RES
	if (!pTheModelLoader->LoadPlyModel("assets/models/sphere_lowres.ply", mapMeshes["sphere_lowres"]))
		std::cout << "Didn't load mesh: sphere_lowres" << std::endl;
	else
		std::cout << "Loaded mesh: sphere_lowres" << std::endl;



	/*std::vector<drTri> debugCube;

	for (size_t i = 0; i < mapMeshes["cube"].vecTriangles.size(); i++)
	{
		glm::vec3 a, b, c;
		a = glm::vec3(mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_1].x,
					  mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_1].y,
					  mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_1].z);

		b = glm::vec3(mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_2].x,
					  mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_2].y,
					  mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_2].z);
		c = glm::vec3(mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_3].x,
					  mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_3].y,
					  mapMeshes["cube"].vecVertices[mapMeshes["cube"].vecTriangles[i].vert_index_3].z);

		debugCube.push_back(drTri(a,b,c));
	}

	pDebugRenderer->loadDebugMesh("cube", debugCube);*/



		std::map<std::string, sModelDrawInfo> drawInfo;

	for (std::map<std::string, cMesh>::iterator iter = mapMeshes.begin(); iter != mapMeshes.end(); iter++)
	{
		if (!pTheVAOManager->LoadModelIntoVAO(iter->first, iter->second, drawInfo[iter->first], shaderProgID))
		{
			std::cout << "Error loading Mesh into VAO: " << iter->first << std::endl;
		}
		else
		{
			std::cout << "Loaded Mesh into VAO: " << iter->first << std::endl;
		}
	}






	LoadTexturesFromFile("assets/config/Textures.xml", pTextureManager);

	pTextureManager->SetBasePath("assets/textures/");
	// Load default texture
	if (!pTextureManager->Create2DTextureFromBMPFile("gridtexture.bmp", true))
	{
		std::cout << "Didn't load texture: gridtexture.bmp" << std::endl;
	}
	else
	{
		std::cout << "Loaded texture: gridtexture.bmp" << std::endl;
	}






	LoadGameObjectsFromXMLFile("assets/config/GameObjects.xml", vec_pGameObjects);

	//TODO: Load basic Rquired Models

	::g_pDebugSphere = new cGameObject();
	::g_pDebugSphere->meshName = "sphere_lowres";
	::g_pDebugSphere->friendlyName = "debug_sphere";
	::g_pDebugSphere->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	::g_pDebugSphere->setOrientation(glm::vec3(90.0f, 0.0f, 0.0f)); // easier on the eyes
	::g_pDebugSphere->scale = 0.1f;
	::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	::g_pDebugSphere->isWireframe = true;
	::g_pDebugSphere->inverseMass = 0.0f;

	cGameObject* pSkyBoxSphere = new cGameObject();
	pSkyBoxSphere->meshName = "sphere_hires";
	pSkyBoxSphere->friendlyName = "skybox";
	pSkyBoxSphere->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	pSkyBoxSphere->scale = 5.0f;
	pSkyBoxSphere->textureRatio[0] = 1.0f;
	pSkyBoxSphere->physicsShapeType = UNKNOWN;
	pSkyBoxSphere->inverseMass = 0.0f;
	pSkyBoxSphere->disableDepthBufferTest = true;
	pSkyBoxSphere->disableDepthBufferWrite = true;


	::g_pDebugCube = new cGameObject();
	::g_pDebugCube->meshName = "cube";
	::g_pDebugCube->friendlyName = "debug_cube";
	::g_pDebugCube->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
	::g_pDebugCube->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
	::g_pDebugCube->scale = 1.0f;
	::g_pDebugCube->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	::g_pDebugCube->isWireframe = true;
	::g_pDebugCube->inverseMass = 0.0f;

	vec_pGameObjects.push_back(pSkyBoxSphere);


	WorldRegion::init(&mapMeshes["Babbage"], 20.0f);




	LoadLightsFromXMLFile("assets/config/Lights.xml", pLightManager);



	pFindObjectByFriendlyName("Ship")->isImposter = true;




	//// *************************************************************************
//// FOR THE PATTERNS AND FRAMEWORKS MID-TERM
//if (pTheModelLoader->LoadPlyModel("assets/models/Example_Arena_xyz_n_uv.ply", g_ArenaMesh))
//{
//	std::cout << "Loaded the arena mesh" << std::endl;
//}
//sModelDrawInfo arenaDrawIndo;
//pTheVAOManager->LoadModelIntoVAO("Arena",
//								 g_ArenaMesh,
//								 arenaDrawIndo,
//								 shaderProgID);

//cGameObject* pArena = new cGameObject();			// HEAP
//pArena->meshName = "Arena";
//pArena->friendlyName = "Arena";
//pArena->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//pArena->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//pArena->scale = 1.0f;	//***** SCALE = 1.0f *****/
//pArena->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//pArena->physicsShapeType = MESH;
////pST->isWireframe = true;
////pST->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
//pArena->inverseMass = 0.0f;	// Ignored during update

//vec_pGameObjects.push_back(pArena);
//// *************************************************************************
//
//	cMesh viperMesh;		// This is stack based
//	if (pTheModelLoader->LoadPlyModel("assets/models/Viper_MkVII_xyz_n_(garbabe_UV).ply", viperMesh))
//	{
//		std::cout << "Loaded the viper" << std::endl;
//	}
//
//	sModelDrawInfo drawInfoViper;
//	pTheVAOManager->LoadModelIntoVAO("viper",
//									 viperMesh,
//									 drawInfoViper,
//									 shaderProgID);
//
//
//	{
//		cGameObject* pViper = new cGameObject();
//		pViper->meshName = "viper";
//		pViper->friendlyName = "viper_player";	// Friendly name
//		pViper->positionXYZ = glm::vec3(0.0f, 20.0f, 0.0f);
//		//	pPirate->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//		pViper->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//		pViper->scale = 1.0f;
//		pViper->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//		pViper->inverseMass = 0.0f;
//		pViper->textures[0] = "Pizza.bmp";
//		pViper->textureRatio[0] = 1.0f;
//		pViper->isWireframe = true;
//		pViper->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//		// Add a debug renderer to this object
//		pViper->setDebugRenderer(pDebugRenderer);
//	}
//
//	cMesh bunnyMesh;		// This is stack based
////	if ( ! pTheModelLoader->LoadPlyModel("assets/models/Sky_Pirate_Combined_xyz.ply", bunnyMesh) )
////	if ( ! pTheModelLoader->LoadPlyModel("assets/models/bun_zipper_res4_XYZ_N.ply", bunnyMesh) )
////	if (!pTheModelLoader->LoadPlyModel("assets/models/bun_zipper_XYZ_n.ply", bunnyMesh))
////	if (!pTheModelLoader->LoadPlyModel("assets/models/Utah_Teapot_xyz_n_uv.ply", bunnyMesh))
//	if (!pTheModelLoader->LoadPlyModel("assets/models/bun_zipper_res2_XYZ_n_UV.ply", bunnyMesh))
//	{
//		std::cout << "Didn't find the file" << std::endl;
//	}
//
//	cMesh largeBunnyMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/Large_Physics_Bunny_XYZ_N_UV.ply", largeBunnyMesh);
//
//	cMesh cannonMesh;
//	if (pTheModelLoader->LoadPlyModel("assets/models/cannon_combined_xyz_n_uv.ply", cannonMesh))
//	{
//		std::cout << "Cannon mesh is loaded. " << std::endl;
//	}
//
//	//cMesh starDestroyerMesh;
//	//if (pTheModelLoader->LoadPlyModel("assets/models/Stardestroyer_CompleteModel_LayersJoinedx1000_xyz_n_uv (decimate 95 percent).ply", starDestroyerMesh))
//	//{
//	//	std::cout << "Star Destroyer is loaded" << std::endl;
//	//}
//
//	cMesh pirateMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/Sky_Pirate_Combined_xyz_n_uv.ply", pirateMesh);
//
//	cMesh flatTerrain;
//	pTheModelLoader->LoadPlyModel("assets/models/Flat_Terrain_XYZ_n_uv.ply", flatTerrain);
//
//	cMesh terrainMesh;
//	if (!pTheModelLoader->LoadPlyModel("assets/models/Terrain_XYZ_n_uv.ply", terrainMesh))
//	{
//		std::cout << "Didn't load terrain" << std::endl;
//	}
//	//pTheModelLoader->LoadPlyModel("assets/models/BigFlatTerrain_XYZ_n.ply", terrainMesh);
//
////	cMesh cubeMesh;
////	pTheModelLoader->LoadPlyModel("assets/models/Cube_1_Unit_from_origin_XYZ_n.ply", cubeMesh);
//
//	cMesh sphereMesh;
//	pTheModelLoader->LoadPlyModel("assets/models/Sphere_Radius_1_XYZ_n_uv.ply", sphereMesh);
//
//	// Example for mesh vs model you are testing in the physics engine
////	cMesh hirescubeMesh;
////	pTheModelLoader->LoadPlyModel("assets/models/cube_Low_Hi_xyz_n.ply", hirescubeMesh);
////	//cMesh lowrescubeMesh;
////	pTheModelLoader->LoadPlyModel("assets/models/cube_Low_Res_xyz_n.ply", lowrescubeMesh);
//
//	//cMesh spaceStationMesh;
//	//pTheModelLoader->LoadPlyModel("assets/models/Entire_Babbage_Space_Station_xyz_n_uv(trivial).ply", spaceStationMesh);
//
//	//cMesh singleTriangleMesh;
////	pTheModelLoader->LoadPlyModel("assets/models/Single_Triangle_XYZ_n_(XZ_Plane_facing_+ve_Y).ply", singleTriangleMesh);
//
//
//	// Create the AABBs for the space station
//	//CalcAABBsForMeshModel(spaceStationMesh);
//
//
//	// Note, the "filename" here is really the "model name" 
//	//  that we can look up later (i.e. it doesn't have to be the file name)
//	sModelDrawInfo drawInfo;
//	pTheVAOManager->LoadModelIntoVAO("bunny",
//									 bunnyMesh,
//									 drawInfo,
//									 shaderProgID);
//
//	sModelDrawInfo drawInfoFlatTerrain;
//	pTheVAOManager->LoadModelIntoVAO("flat_terrain",
//									 flatTerrain,
//									 drawInfoFlatTerrain,
//									 shaderProgID);
//
//	sModelDrawInfo cannonDrawInfo;
//	pTheVAOManager->LoadModelIntoVAO("cannon",
//									 cannonMesh,
//									 cannonDrawInfo,
//									 shaderProgID);
//
//	//sModelDrawInfo STdrawInfo;
//	//pTheVAOManager->LoadModelIntoVAO("StarDestroyer",
//	//								 starDestroyerMesh,
//	//								 STdrawInfo,
//	//								 shaderProgID);
//
//	sModelDrawInfo drawInfoPirate;
//	pTheVAOManager->LoadModelIntoVAO("pirate",
//									 pirateMesh,
//									 drawInfoPirate,
//									 shaderProgID);
//
//	sModelDrawInfo drawInfoTerrain;
//	pTheVAOManager->LoadModelIntoVAO("terrain",
//									 terrainMesh,
//									 drawInfoTerrain,
//									 shaderProgID);
//
//	//sModelDrawInfo cubeMeshInfo;
//	//pTheVAOManager->LoadModelIntoVAO("cube",
//	//								 cubeMesh,			// Cube mesh info
//	//								 cubeMeshInfo,
//	//								 shaderProgID);
//
//	sModelDrawInfo sphereMeshInfo;
//	pTheVAOManager->LoadModelIntoVAO("sphere",
//									 sphereMesh,		// Sphere mesh info
//									 sphereMeshInfo,
//									 shaderProgID);
//
//	// Here's the one for the bunny
////	sModelDrawInfo largeBunnyDrawInfo;
//	pTheVAOManager->LoadModelIntoVAO("large_bunny",
//									 largeBunnyMesh,		// Sphere mesh info
//									 largeBunnyDrawInfo,
//									 shaderProgID);
//
//
//	//sModelDrawInfo hirescubeDrawInfo;
//	//pTheVAOManager->LoadModelIntoVAO("hi_res_cube",
//	//								 hirescubeMesh,			// The one we draw
//	//								 hirescubeDrawInfo,
//	//								 shaderProgID);
//	//sModelDrawInfo lowrescubeDrawInfo;
//	//pTheVAOManager->LoadModelIntoVAO("low_res_cube",
//	//								 lowrescubeMesh,		// the one we test in the physics engine
//	//								 lowrescubeDrawInfo,
//	//								 shaderProgID);
//
//	//sModelDrawInfo spaceStationDrawInfo;
//	//pTheVAOManager->LoadModelIntoVAO("space_station",
//	//								 spaceStationMesh,		// the one we test in the physics engine
//	//								 spaceStationDrawInfo,
//	//								 shaderProgID);
//
//	//sModelDrawInfo singleTriangleDrawInfo;
//	//pTheVAOManager->LoadModelIntoVAO("single_triangle",
//	//								 singleTriangleMesh,		// the one we test in the physics engine
//	//								 singleTriangleDrawInfo,
//	//								 shaderProgID);
//
//
//	// At this point, the model is loaded into the GPU
//
//
//	//// Load up my "scene" 
//	//std::vector<cGameObject*> vec_pGameObjects;
//	{
//		cGameObject* pFlatTerrain = new cGameObject();
//		pFlatTerrain->meshName = "flat_terrain";
//		pFlatTerrain->friendlyName = "flat_terrain";	// Friendly name
//		pFlatTerrain->positionXYZ = glm::vec3(0.0f, -150.0f, 0.0f);
//		//	pPirate->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//		pFlatTerrain->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//		pFlatTerrain->scale = 1.0f;
//		pFlatTerrain->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//		pFlatTerrain->inverseMass = 0.0f;
//		pFlatTerrain->isWireframe = true;
//		pFlatTerrain->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//		//pFlatTerrain->textures[0] = "IslandHeightMap.bmp";
//		//pFlatTerrain->textureRatio[0] = 1.0f;
//		// Add a debug renderer to this object
//		pFlatTerrain->setDebugRenderer(pDebugRenderer);
//
//		vec_pGameObjects.push_back(pFlatTerrain);
//	}
//
//
//
//	cGameObject* pPirate = new cGameObject();
//	pPirate->meshName = "pirate";
//	pPirate->friendlyName = "PirateShip";	// Friendly name
//	pPirate->positionXYZ = glm::vec3(-30.0f, 20.0f, 10.0f);
//	//	pPirate->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pPirate->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pPirate->scale = 1.0f;
//	pPirate->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	pPirate->inverseMass = 0.0f;
//	//pPirate->HACK_AngleAroundYAxis = 0.0f;
//	//pPirate->HACK_speed = 0.0f;
//	// Add a debug renderer to this object
//	pPirate->setDebugRenderer(pDebugRenderer);
//
//	//AddCannonsToPirateShip(pPirate, pDebugRenderer);
//
//	//
//	cGameObject* pBunny = new cGameObject();
//	pBunny->meshName = "bunny";
//	pBunny->friendlyName = "Bugs";	// Famous bunny
//	pBunny->positionXYZ = glm::vec3(50.0f, 20.0f, -2.0f);		// -4 on z
//	//pBunny->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pBunny->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pBunny->scale = 250.0f;
//	pBunny->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
//	pBunny->inverseMass = 0.0f;
//	//
//		//cGameObject bunny2;
//		//bunny2.meshName = "bunny";
//		//bunny2.positionXYZ = glm::vec3(0.0f,0.0f,0.0f);
//		//bunny2.rotationXYZ = glm::vec3(0.0f,1.0f,0.0f);
//		//bunny2.scale = 3.5f;
//		//bunny2.objectColourRGBA = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
//	//
//		//cGameObject terrain;
//		//terrain.meshName = "terrain";
//		//terrain.positionXYZ = glm::vec3(0.0f,-10.0f,0.0f);
//		//terrain.rotationXYZ = glm::vec3(0.0f,0.0f,0.0f);
//		//terrain.scale = 0.5f;
//		//terrain.objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//
//		// Sphere and cube
//	pShpere = new cGameObject();
//
//	//cGameObject A; 
//	//cGameObject B;
//	//A = B;
//
//
//	pShpere->meshName = "sphere";
//	pShpere->friendlyName = "Sphere#1";	// We use to search 
//	pShpere->positionXYZ = glm::vec3(0.0f, 30.0, 0.0f);
//	//pShpere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pShpere->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pShpere->scale = 1.0f;
//	pShpere->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	// Set the sphere's initial velocity, etc.
//	pShpere->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//	pShpere->accel = glm::vec3(0.0f, 0.0f, 0.0f);
//	pShpere->physicsShapeType = SPHERE;
//	pShpere->PhysicsSphere = 1.0f;
//	pShpere->inverseMass = 1.0f;
//	//	pShpere->inverseMass = 0.0f;			// Sphere won't move
//
//
//
//	cGameObject* pCube = new cGameObject();			// HEAP
//	pCube->meshName = "cube";
//	pCube->positionXYZ = glm::vec3(0.0f, -1.0f, 0.0f);
//	//pCube->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pCube->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pCube->scale = 1.0f;
//	//pCube->objectColourRGBA = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	pCube->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	pCube->isWireframe = true;
//	// Set the sphere's initial velocity, etc.
//	//sphere.velocity = glm::vec3(0.0f,0.0f,0.0f);
//	//sphere.accel = glm::vec3(0.0f,0.0f,0.0f);
//	pCube->inverseMass = 0.0f;	// Ignored during update
//
//
//	cGameObject* pTerrain = new cGameObject();			// HEAP
//	pTerrain->meshName = "terrain";
//	pTerrain->friendlyName = "TheGround";
//	pTerrain->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	//pTerrain->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pTerrain->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pTerrain->scale = 1.0f;
//	pTerrain->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	pTerrain->physicsShapeType = MESH;
//	//pTerrain->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	//pTerrain->isWireframe = true;
//	pTerrain->inverseMass = 0.0f;	// Ignored during update
//	pTerrain->isVisible = false;
//
//	cGameObject* pLargeBunny = new cGameObject();			// HEAP
//	pLargeBunny->meshName = "large_bunny";
//	pLargeBunny->friendlyName = "largeBunny";
//	pLargeBunny->positionXYZ = glm::vec3(30.0f, 0.0f, 0.0f);
//	//pLargeBunny->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pLargeBunny->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pLargeBunny->scale = 5.0f;	//***** SCALE = 1.0f *****/
//	pLargeBunny->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	pLargeBunny->physicsShapeType = MESH;
//	// pLargeBunny->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//	// pLargeBunny->doNotLight = true;
//	pLargeBunny->inverseMass = 0.0f;	// Ignored during update
//
//
//	// Same orientation and position for BOTH the high resolution AND low resultion objects
//	glm::vec3 cubesPosition = glm::vec3(0.0f, -50.0f, 0.0f);
//	glm::vec3 cubesRotation = glm::vec3(glm::radians(15.0f), 0.0f, glm::radians(35.0f));
//
//
//	pHiResCube = new cGameObject();			// HEAP
//	pHiResCube->meshName = "hi_res_cube";
//	pHiResCube->friendlyName = "hi_cube";
//	pHiResCube->positionXYZ = cubesPosition;
//	//pHiResCube->rotationXYZ = cubesRotation;
//	pHiResCube->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pHiResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
//	pHiResCube->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	pHiResCube->physicsShapeType = MESH;
//	//pHiResCube->isWireframe = true;
//	//pHiResCube->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);		// Yellow
//	pHiResCube->inverseMass = 0.0f;	// Ignored during update
//
//	cGameObject* pLowResCube = new cGameObject();			// HEAP
//	pLowResCube->meshName = "low_res_cube";
//	pLowResCube->friendlyName = "low_cube";
//	pLowResCube->positionXYZ = cubesPosition;
//	//pLowResCube->rotationXYZ = cubesRotation;
//	pLowResCube->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pLowResCube->scale = 1.0f;	//***** SCALE = 1.0f *****/
//	pLowResCube->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	pLowResCube->physicsShapeType = MESH;
//	pLowResCube->isWireframe = true;
//	pLowResCube->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
//	pLowResCube->inverseMass = 0.0f;	// Ignored during update
//
//	cGameObject* pSpaceStation = new cGameObject();			// HEAP
//	pSpaceStation->meshName = "space_station";
//	pSpaceStation->friendlyName = "space station";
//	pSpaceStation->positionXYZ = glm::vec3(100.0f, 0.0f, 0.0f);
//	//pSpaceStation->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pSpaceStation->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pSpaceStation->scale = 1.0f;	//***** SCALE = 1.0f *****/
//	pSpaceStation->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	//pSpaceStation->physicsShapeType = MESH;
//	//pSpaceStation->isWireframe = true;
//	pSpaceStation->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
//	pSpaceStation->inverseMass = 0.0f;	// Ignored during update
//
//	cGameObject* pSingleTriangle = new cGameObject();			// HEAP
//	pSingleTriangle->meshName = "single_triangle";
//	pSingleTriangle->friendlyName = "single triangle";
//	pSingleTriangle->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	//pSingleTriangle->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pSingleTriangle->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pSingleTriangle->scale = 1.0f;	//***** SCALE = 1.0f *****/
//	pSingleTriangle->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	pSingleTriangle->physicsShapeType = MESH;
//	//pSingleTriangle->isWireframe = true;
//	//pSingleTriangle->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
//	pSingleTriangle->inverseMass = 0.0f;	// Ignored during update
//
//
//	cGameObject* pST = new cGameObject();			// HEAP
//	pST->meshName = "StarDestroyer";
//	pST->friendlyName = "StarDestroyer";
//	pST->positionXYZ = glm::vec3(500.0f, -250.0f, 0.0f);
//	//pST->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pST->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	pST->scale = 1.0f;	//***** SCALE = 1.0f *****/
//	pST->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//	pST->physicsShapeType = MESH;
//	pST->textures[0] = "Pizza.bmp";
//	pST->textureRatio[0] = 1.0f;
//	//pST->isWireframe = true;
//	//pST->debugColour = glm::vec4(1.0f, 1.0f, 0.5f, 1.0f);		// Yellow
//	pST->inverseMass = 0.0f;	// Ignored during update
//
//	pST->vecPhysTestPoints.push_back(glm::vec3(0.0f, -200.0f, 804.0f));		// Front
//	pST->vecPhysTestPoints.push_back(glm::vec3(0.0f, 267.0f, -700.0f));		// Top
//	pST->vecPhysTestPoints.push_back(glm::vec3(-532.0f, -200.0f, -804.0f));	// Left
//	pST->vecPhysTestPoints.push_back(glm::vec3(532.0f, -200.0f, -804.0f));		// Right
//
//
//	// "SkyBox"
//	cGameObject* pSkyBoxSphere = new cGameObject();
//	pSkyBoxSphere->meshName = "sphere";
//	pSkyBoxSphere->friendlyName = "skybox";
//	pSkyBoxSphere->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	pSkyBoxSphere->scale = 10000.0f;		// 1.0 to 10,000,000
//	//pSkyBoxSphere->isWireframe = true;
//	//pSkyBoxSphere->debugColour = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
//	pSkyBoxSphere->textures[0] = "Pizza.bmp";
//	pSkyBoxSphere->textureRatio[0] = 1.0f;
//	pSkyBoxSphere->physicsShapeType = SPHERE;
//	pSkyBoxSphere->inverseMass = 0.0f;
//
//
//	vec_pGameObjects.push_back(pSkyBoxSphere);
//
//	vec_pGameObjects.push_back(pST);
//
//	vec_pGameObjects.push_back(pShpere);
//	vec_pGameObjects.push_back(pCube);
//	vec_pGameObjects.push_back(pTerrain);
//	vec_pGameObjects.push_back(pPirate);
//	vec_pGameObjects.push_back(pBunny);
//	vec_pGameObjects.push_back(pLargeBunny);
//	//	vec_pGameObjects.push_back(pSpaceStation);
//	vec_pGameObjects.push_back(pSingleTriangle);
//
//	vec_pGameObjects.push_back(pHiResCube);
//	vec_pGameObjects.push_back(pLowResCube);
//
//
//	for (float x = -300.0f; x <= +300.0f; x += 50.0f)
//	{
//		for (float y = -300.0f; y <= +300.0f; y += 50.0f)
//		{
//			for (float z = 0.0f; z <= +600.0f; z += 50.0f)
//			{
//				cGameObject* pLargeBunny = new cGameObject();			// HEAP
//				pLargeBunny->meshName = "large_bunny";
//				pLargeBunny->friendlyName = "largeBunny";
//				pLargeBunny->positionXYZ = glm::vec3(x, y, z);
//				//pLargeBunny->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//				pLargeBunny->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//				pLargeBunny->scale = 1.0f;	//***** SCALE = 1.0f *****/
//				pLargeBunny->objectColourRGBA = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
//				pLargeBunny->physicsShapeType = MESH;
//				//pLargeBunny->debugColour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
//				//pLargeBunny->isWireframe = true;
//				pLargeBunny->inverseMass = 0.0f;	// Ignored during update
//
//				pLargeBunny->textures[0] = "pebbles-beach-textures.bmp";
//				pLargeBunny->textureRatio[0] = 1.0f;
//
//				pLargeBunny->diffuseColour.a = 0.5f;
//
//				pLargeBunny->isVisible = false;
//
//				vec_pGameObjects.push_back(pLargeBunny);
//			}
//		}
//	}
//
//	vec_pGameObjects[12]->textures[0] = "Pizza.bmp";
//	vec_pGameObjects[12]->textures[1] = "pebbles-beach-textures.bmp";
//	vec_pGameObjects[12]->textureRatio[0] = 0.5f;
//	vec_pGameObjects[12]->textureRatio[1] = 0.5f;
//
//	vec_pGameObjects[13]->textures[0] = "pebbles-beach-textures.bmp";
//	vec_pGameObjects[13]->textures[1] = "PowerPlant.bmp";
//	vec_pGameObjects[13]->textureRatio[0] = 0.5f;
//	vec_pGameObjects[13]->textureRatio[1] = 0.5f;
//
//	vec_pGameObjects[14]->textures[0] = "PowerPlant.bmp";
//	vec_pGameObjects[14]->textureRatio[0] = 1.0f;
//
//	vec_pGameObjects[15]->textures[0] = "AlienBluray_512x512.bmp";
//	vec_pGameObjects[15]->textureRatio[0] = 1.0f;
//
//	vec_pGameObjects[16]->textures[0] = "EmmaWatson.bmp";
//	vec_pGameObjects[16]->friendlyName = "Emma";
//	vec_pGameObjects[16]->textureRatio[0] = 1.0f;
//
//	vec_pGameObjects[17]->textures[0] = "Grass.bmp";
//	vec_pGameObjects[17]->textureRatio[0] = 1.0f;
//
//	vec_pGameObjects[18]->textures[0] = "Pizza.bmp";
//	vec_pGameObjects[18]->textureRatio[0] = 1.0f;
//
//
//
//
//
//
//	//::g_map_GameObjectsByFriendlyName[pShpere2->friendlyName] = pShpere;
//	//::g_map_GameObjectsByFriendlyName[pTerrain->friendlyName] = pTerrain;
//	//::g_map_GameObjectsByFriendlyName[pPirate->friendlyName] = pPirate;
//	//::g_map_GameObjectsByFriendlyName[pBunny->friendlyName] = pBunny;
//
//
//	// Will be moved placed around the scene
//	::g_pDebugSphere = new cGameObject();
//	::g_pDebugSphere->meshName = "sphere";
//	::g_pDebugSphere->friendlyName = "debug_sphere";
//	::g_pDebugSphere->positionXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	//::g_pDebugSphere->rotationXYZ = glm::vec3(0.0f, 0.0f, 0.0f);
//	::g_pDebugSphere->setOrientation(glm::vec3(0.0f, 0.0f, 0.0f));
//	::g_pDebugSphere->scale = 0.1f;
//	//	::g_pDebugSphere->objectColourRGBA = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
//	::g_pDebugSphere->debugColour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
//	::g_pDebugSphere->isWireframe = true;
//	::g_pDebugSphere->inverseMass = 0.0f;			// Sphere won't move

	return;

}

