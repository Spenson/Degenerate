#include "FileReaders.h"
#include <tinyxml2/tinyxml2.h>
#include <iostream>


glm::vec3 GetXYZ(tinyxml2::XMLElement* node)
{
	return glm::vec3(
		node->FindAttribute("x")->FloatValue(),
		node->FindAttribute("y")->FloatValue(),
		node->FindAttribute("z")->FloatValue()
	);
}
glm::vec3 GetXYZW(tinyxml2::XMLElement* node)
{
	return glm::vec4(
		node->FindAttribute("x")->FloatValue(),
		node->FindAttribute("y")->FloatValue(),
		node->FindAttribute("z")->FloatValue(),
		node->FindAttribute("w")->FloatValue()
	);
}
glm::vec3 GetRGB(tinyxml2::XMLElement* node)
{
	return glm::vec3(
		node->FindAttribute("r")->FloatValue(),
		node->FindAttribute("g")->FloatValue(),
		node->FindAttribute("b")->FloatValue()
	);
}
glm::vec4 GetRGBA(tinyxml2::XMLElement* node)
{
	return glm::vec4(
		node->FindAttribute("r")->FloatValue(),
		node->FindAttribute("g")->FloatValue(),
		node->FindAttribute("b")->FloatValue(),
		node->FindAttribute("a")->FloatValue()
	);
}

void SetXYZ(tinyxml2::XMLNode* node, glm::vec3 vals)
{
	((tinyxml2::XMLElement*)node)->SetAttribute("x", vals.x);
	((tinyxml2::XMLElement*)node)->SetAttribute("y", vals.y);
	((tinyxml2::XMLElement*)node)->SetAttribute("z", vals.z);
}
void SetRGB(tinyxml2::XMLNode* node, glm::vec3 vals)
{
	((tinyxml2::XMLElement*)node)->SetAttribute("r", vals.x);
	((tinyxml2::XMLElement*)node)->SetAttribute("g", vals.y);
	((tinyxml2::XMLElement*)node)->SetAttribute("b", vals.z);
}
void SetXYZW(tinyxml2::XMLNode* node, glm::vec4 vals)
{
	((tinyxml2::XMLElement*)node)->SetAttribute("x", vals.x);
	((tinyxml2::XMLElement*)node)->SetAttribute("y", vals.y);
	((tinyxml2::XMLElement*)node)->SetAttribute("z", vals.z);
	((tinyxml2::XMLElement*)node)->SetAttribute("w", vals.w);
}
void SetRGBA(tinyxml2::XMLNode* node, glm::vec4 vals)
{
	((tinyxml2::XMLElement*)node)->SetAttribute("r", vals.r);
	((tinyxml2::XMLElement*)node)->SetAttribute("g", vals.g);
	((tinyxml2::XMLElement*)node)->SetAttribute("b", vals.b);
	((tinyxml2::XMLElement*)node)->SetAttribute("a", vals.a);
}


void LoadMeshesFromXMLFile(std::string File, std::string MeshDir, std::map<std::string, cMesh>& mapMeshes, cModelLoader* modelLoader)
{
	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(File.c_str());
	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("MESHES");

	tinyxml2::XMLElement* meshElement = root->FirstChildElement("Mesh");
	std::string currentName;
	for (;;)
	{
		currentName = meshElement->FirstChildElement("Name")->GetText();

		if (!mapMeshes.count(currentName))
		{
			if (modelLoader->LoadPlyModel(MeshDir + meshElement->FirstChildElement("File")->GetText(), mapMeshes[currentName]))
				std::cout << "Loaded mesh: " << meshElement->FirstChildElement("Name")->GetText() << std::endl;
			else
				std::cout << "Didn't load mesh: " << meshElement->FirstChildElement("Name")->GetText() << std::endl;
		}

		if (meshElement == root->LastChildElement())
			break;
		meshElement = meshElement->NextSiblingElement();
	}
}

void LoadTexturesFromFile(std::string File, cBasicTextureManager* TextureManager)
{
	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(File.c_str());
	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("TEXTURES");

	std::string errorString = "";

	tinyxml2::XMLElement* textureGroupElement = root->FirstChildElement("TextureGroup");
	for (;;)
	{
		//TextureManager->SetBasePath(textureGroupElement->FirstChildElement("Dir")->Value());
		tinyxml2::XMLElement* node = textureGroupElement->FirstChildElement();
		for (;;)
		{
			//std::cout << node->Name() << std::endl;
			if (strcmp(node->Name(), "File") == 0)
			{
				
				if (::g_pTextureManager->Create2DTextureFromBMPFile(node->GetText(), true))
					std::cout << "Loaded texture: " << node->GetText() << std::endl;
				else
					std::cout << "Didn't load texture: " << node->GetText() << std::endl;
			}

			else if (strcmp(node->Name(), "Cube") == 0)
			{
				if (::g_pTextureManager->CreateCubeTextureFromBMPFiles(node->FirstChildElement("Name")->GetText(),
																	   node->FirstChildElement("Right")->GetText(), node->FirstChildElement("Left")->GetText(),
																	   node->FirstChildElement("Up")->GetText(), node->FirstChildElement("Down")->GetText(),
																	   node->FirstChildElement("Front")->GetText(), node->FirstChildElement("Back")->GetText(),
																	   true, errorString))
				{
					std::cout << "Loaded cube map: " << node->FirstChildElement("Name")->GetText() << std::endl;
				}
				else
					std::cout << "Didn't load cube map: " << node->FirstChildElement("Name")->GetText() << "\n\t" << errorString << std::endl;
			}

			else if (strcmp(node->Name(), "Dir") == 0 || strcmp(node->Name(), "Directory") == 0)
			{
				TextureManager->SetBasePath(node->GetText());
				std::cout << "Set Texture Path: " << node->GetText() << std::endl;
			}


			if (node == textureGroupElement->LastChildElement())
				break;
			node = node->NextSiblingElement();
		}

		if (textureGroupElement == root->LastChildElement())
			break;
		textureGroupElement = textureGroupElement->NextSiblingElement();

	}
}


// separated to use recursively for child nodes
cGameObject* LoadGameObjectNode(tinyxml2::XMLElement* objectElement)
{
	cGameObject* object = new cGameObject();
	std::cout << objectElement->FirstChildElement("MeshName")->GetText() << std::endl;
	if (objectElement->FirstChildElement("MeshName"))
		object->meshName = objectElement->FirstChildElement("MeshName")->GetText();

	if (objectElement->FirstChildElement("FriendlyName"))
		object->friendlyName = objectElement->FirstChildElement("FriendlyName")->GetText();

	if (objectElement->FirstChildElement("Position"))
		object->positionXYZ = GetXYZ(objectElement->FirstChildElement("Position"));

	if (objectElement->FirstChildElement("Velocity"))
		object->velocity = GetXYZ(objectElement->FirstChildElement("Velocity"));

	if (objectElement->FirstChildElement("Acceleration"))
		object->accel = GetXYZ(objectElement->FirstChildElement("Acceleration"));


	if (objectElement->FirstChildElement("Scale"))
		object->scale = objectElement->FirstChildElement("Scale")->FindAttribute("f")->FloatValue(); //GetXYZ(objectElement->FirstChildElement("Scale"));


	if (objectElement->FirstChildElement("InverseMass"))
		object->inverseMass = objectElement->FirstChildElement("InverseMass")->FindAttribute("f")->FloatValue();

	if (objectElement->FirstChildElement("PhysicsShapeType"))
		object->physicsShapeType = (eShapeTypes)objectElement->FirstChildElement("PhysicsShapeType")->FindAttribute("type")->IntValue();



	if (objectElement->FirstChildElement("AABB"))
	{
		object->AABB_min = GetXYZ(objectElement->FirstChildElement("AABB")->FirstChildElement("max"));
		object->AABB_max = GetXYZ(objectElement->FirstChildElement("AABB")->FirstChildElement("min"));
	}

	if (objectElement->FirstChildElement("Radius"))
		object->PhysicsSphere = objectElement->FirstChildElement("Radius")->FindAttribute("f")->FloatValue();

	if (objectElement->FirstChildElement("TestPoints"))
	{
		tinyxml2::XMLElement* pointsElement = objectElement->FirstChildElement("TestPoints")->FirstChildElement();

		for (;;)
		{
			object->vecPhysTestPoints.push_back(GetXYZ(pointsElement));


			if (pointsElement == objectElement->FirstChildElement("TestPoints")->LastChildElement())
				break;
			pointsElement = pointsElement->NextSiblingElement();
		}
	}

	if (objectElement->FirstChildElement("ObjectColour"))
		object->objectColourRGBA = GetRGBA(objectElement->FirstChildElement("ObjectColour"));

	if (objectElement->FirstChildElement("DiffuseColour"))
		object->diffuseColour = GetRGBA(objectElement->FirstChildElement("DiffuseColour"));

	if (objectElement->FirstChildElement("SpecularColour"))
		object->specularColour = GetRGBA(objectElement->FirstChildElement("SpecularColour"));

	if (objectElement->FirstChildElement("DebugColour"))
		object->debugColour = GetRGBA(objectElement->FirstChildElement("DebugColour"));



	if (objectElement->FirstChildElement("Textures"))
	{
		tinyxml2::XMLElement* textureElement = objectElement->FirstChildElement("Textures")->FirstChildElement();

		for (;;)
		{
			object->textures[textureElement->FindAttribute("index")->IntValue()] = textureElement->FindAttribute("name")->Value();
			object->textureRatio[textureElement->FindAttribute("index")->IntValue()] = textureElement->FindAttribute("ratio")->FloatValue();


			if (textureElement == objectElement->FirstChildElement("Textures")->LastChildElement())
				break;
			textureElement = textureElement->NextSiblingElement();
		}
	}

	if (objectElement->FirstChildElement("DoNotLight"))
		object->isWireframe = objectElement->FirstChildElement("DoNotLight")->FindAttribute("b")->BoolValue();

	if (objectElement->FirstChildElement("IsImposter"))
		object->isImposter = objectElement->FirstChildElement("IsImposter")->FindAttribute("b")->BoolValue();

	if (objectElement->FirstChildElement("UseDiffuse"))
		object->useDiffuse = objectElement->FirstChildElement("UseDiffuse")->FindAttribute("b")->BoolValue();

	if (objectElement->FirstChildElement("Wireframe"))
		object->isWireframe = objectElement->FirstChildElement("Wireframe")->FindAttribute("b")->BoolValue();

	if (objectElement->FirstChildElement("Visible"))
		object->isVisible = objectElement->FirstChildElement("Visible")->FindAttribute("b")->BoolValue();

	if (objectElement->FirstChildElement("DisableDepthTest"))
		object->disableDepthBufferTest = objectElement->FirstChildElement("DisableDepthTest")->FindAttribute("b")->BoolValue();

	if (objectElement->FirstChildElement("DisableDepthWrite"))
		object->disableDepthBufferWrite = objectElement->FirstChildElement("DisableDepthWrite")->FindAttribute("b")->BoolValue();

	if (objectElement->FirstChildElement("Rotation"))
		object->setOrientation(GetXYZ(objectElement->FirstChildElement("Rotation")));


	if (objectElement->FirstChildElement("ChildObjects"))
	{
		tinyxml2::XMLElement* childObjectElement = objectElement->FirstChildElement("ChildObjects")->FirstChildElement();
		for (;;)
		{
			object->vec_pChildObjects.push_back(LoadGameObjectNode(childObjectElement));

			if (childObjectElement == objectElement->FirstChildElement("ChildObjects")->LastChildElement())
				break;
			childObjectElement = childObjectElement->NextSiblingElement();
		}
	}


	return object;
}

void LoadGameObjectsFromXMLFile(std::string File, std::vector<cGameObject*>& vecGameObjects, bool clearExistingObjects)
{
	if (clearExistingObjects)
	{
		for (unsigned index = 0; index < vecGameObjects.size(); index++)
			delete vecGameObjects[index];

		vecGameObjects.clear();
	}

	//cGameObject* object;
	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(File.c_str());
	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("GAMEOBJECTS");

	tinyxml2::XMLElement* objectElement = root->FirstChildElement("GameObject");
	//for (tinyxml2::XMLElement* element = root->FirstChildElement("GameObject"); element != root->LastChildElement(); element = element->NextSiblingElement())
	for (;;)
	{
		vecGameObjects.push_back(LoadGameObjectNode(objectElement));

		if (objectElement == root->LastChildElement())
			break;
		objectElement = objectElement->NextSiblingElement();

	}

}


// separated to use recursively for child nodes
tinyxml2::XMLElement* SaveGameObjectNode(cGameObject* object, tinyxml2::XMLDocument& doc) // XMLDocument must be by ref (&)
{
	tinyxml2::XMLElement* newObjectElement = doc.NewElement("GameObject");

	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("MeshName")))->SetText(object->meshName.c_str());
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("FriendlyName")))->SetText(object->friendlyName.c_str());

	SetXYZ(newObjectElement->InsertEndChild(doc.NewElement("Position")), object->positionXYZ);
	SetXYZ(newObjectElement->InsertEndChild(doc.NewElement("Velocity")), object->velocity);
	SetXYZ(newObjectElement->InsertEndChild(doc.NewElement("Acceleration")), object->accel);


	//SetXYZ(newObjectElement->InsertEndChild(doc.NewElement("Scale")), object->scale);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("Scale")))->SetAttribute("f", object->scale);

	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("InverseMass")))->SetAttribute("f", object->inverseMass);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("PhysicsShapeType")))->SetAttribute("type", object->physicsShapeType);
	tinyxml2::XMLElement* AABBNode = (tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("AABB"));
	SetXYZ(AABBNode->InsertEndChild(doc.NewElement("max")), object->AABB_max);
	SetXYZ(AABBNode->InsertEndChild(doc.NewElement("min")), object->AABB_min);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("Radius")))->SetAttribute("f", object->PhysicsSphere);

	//todo: as if statment vecPhysTestPoints;
	if (!object->vecPhysTestPoints.empty())
	{
		tinyxml2::XMLElement* TestPointsNode = (tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("TestPoints"));

		for (size_t i = 0; i < object->vecPhysTestPoints.size(); i++)
		{
			SetXYZ(TestPointsNode->InsertEndChild(doc.NewElement("point")), object->vecPhysTestPoints[i]);
		}
	}



	SetRGBA(newObjectElement->InsertEndChild(doc.NewElement("ObjectColour")), object->objectColourRGBA);
	SetRGBA(newObjectElement->InsertEndChild(doc.NewElement("DiffuseColour")), object->diffuseColour);
	SetRGBA(newObjectElement->InsertEndChild(doc.NewElement("SpecularColour")), object->specularColour);
	SetRGBA(newObjectElement->InsertEndChild(doc.NewElement("DebugColour")), object->debugColour);


	//todo: textures textureRatio
	tinyxml2::XMLElement* TexturesNode = (tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("Textures"));
	tinyxml2::XMLElement* tempTextureNode;
	for (size_t i = 0; i < object->NUMBEROFTEXTURES; i++)
	{
		tempTextureNode = (tinyxml2::XMLElement*)TexturesNode->InsertEndChild(doc.NewElement("texture"));
		((tinyxml2::XMLElement*)tempTextureNode)->SetAttribute("index", i);
		((tinyxml2::XMLElement*)tempTextureNode)->SetAttribute("name", object->textures[i].c_str());
		((tinyxml2::XMLElement*)tempTextureNode)->SetAttribute("ratio", object->textureRatio[i]);
	}

	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("DoNotLight")))->SetAttribute("b", object->doNotLight);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("IsImposter")))->SetAttribute("b", object->isImposter);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("UseDiffuse")))->SetAttribute("b", object->useDiffuse);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("Wireframe")))->SetAttribute("b", object->isWireframe);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("Visible")))->SetAttribute("b", object->isVisible);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("DisableDepthTest")))->SetAttribute("b", object->disableDepthBufferTest);
	((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("DisableDepthWrite")))->SetAttribute("b", object->disableDepthBufferWrite);

	SetXYZ(newObjectElement->InsertEndChild(doc.NewElement("Rotation")), object->getEulerAngle());



	//todo: recursive chile objects
	if (!object->vec_pChildObjects.empty())
	{
		tinyxml2::XMLElement* childObjectNode = (tinyxml2::XMLElement*)newObjectElement->InsertEndChild(doc.NewElement("ChildObjects"));

		for (size_t i = 0; i < object->vec_pChildObjects.size(); i++)
		{
			childObjectNode->InsertEndChild(SaveGameObjectNode(object->vec_pChildObjects[i], doc));
		}
	}


	return newObjectElement;
}

void SaveGameObjectsToXMLFile(std::string File, std::vector<cGameObject*> vecGameObjects)
{
	cGameObject* object;
	tinyxml2::XMLDocument new_xml_doc;
	tinyxml2::XMLNode* newRoot = new_xml_doc.InsertFirstChild(new_xml_doc.NewElement("GAMEOBJECTS"));

	for (unsigned index = 0; index < vecGameObjects.size(); index++)
	{
		object = vecGameObjects[index];

		(tinyxml2::XMLElement*)newRoot->InsertEndChild(SaveGameObjectNode(object, new_xml_doc));
	}
	new_xml_doc.SaveFile(File.c_str());
}


void LoadLightsFromXMLFile(std::string File, LightManager* g_pLightManager, bool clearExistingLights)
{
	std::vector<Light*> lights;

	if (clearExistingLights)
	{
		for (unsigned index = 0; index < lights.size(); index++)
			delete lights[index];

		lights.clear();
	}

	Light* light;
	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(File.c_str());
	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("LIGHTS");

	tinyxml2::XMLElement* lightElement = root->FirstChildElement("Light");
	for (;;)
	{
		light = new Light();

		if (lightElement->FirstChildElement("Rotation"))
			light->Direction = GetXYZ(lightElement->FirstChildElement("Rotation"));
		if (lightElement->FirstChildElement("Direction"))
			light->Direction = GetXYZ(lightElement->FirstChildElement("Direction"));
		if (lightElement->FirstChildElement("Position"))
			light->Position = GetXYZ(lightElement->FirstChildElement("Position"));
		if (lightElement->FirstChildElement("Diffuse"))
			light->Diffuse = GetRGB(lightElement->FirstChildElement("Diffuse"));
		if (lightElement->FirstChildElement("Specular"))
			light->Diffuse = GetRGBA(lightElement->FirstChildElement("Specular"));

		if (lightElement->FirstChildElement("ConstAtten"))
			light->ConstAtten = lightElement->FirstChildElement("ConstAtten")->FindAttribute("f")->FloatValue();
		if (lightElement->FirstChildElement("LinearAtten"))
			light->LinearAtten = lightElement->FirstChildElement("LinearAtten")->FindAttribute("f")->FloatValue();
		if (lightElement->FirstChildElement("QuadraticAtten"))
			light->QuadraticAtten = lightElement->FirstChildElement("QuadraticAtten")->FindAttribute("f")->FloatValue();

		//light->CutOffDistance = FLT_MAX; // will be FLT_Max 99% of the time 
		if (lightElement->FirstChildElement("CutOffDistance"))
			lightElement->FirstChildElement("CutOffDistance")->FindAttribute("f")->FloatValue();

		if (lightElement->FirstChildElement("LightType"))
			light->lightType = (Light::LightType) lightElement->FirstChildElement("LightType")->FindAttribute("type")->IntValue();

		if (lightElement->FirstChildElement("SpotInnerAngle"))
			light->SpotInnerAngle = lightElement->FirstChildElement("SpotInnerAngle")->FindAttribute("f")->FloatValue();
		if (lightElement->FirstChildElement("SpotOuterAngle"))
			light->SpotOuterAngle = lightElement->FirstChildElement("SpotOuterAngle")->FindAttribute("f")->FloatValue();

		if (lightElement->FirstChildElement("IsLightOn"))
			light->isLightOn = lightElement->FirstChildElement("IsLightOn")->FindAttribute("b")->BoolValue();

		lights.push_back(light);

		if (lightElement == root->LastChildElement())
			break;
		lightElement = lightElement->NextSiblingElement();
	}

	g_pLightManager->GenerateLights(lights);
}

void SaveLightsToXMLFile(std::string File, LightManager* g_pLightManager)
{
	std::vector<Light*> vecLights;

	for (unsigned i = 0; i < g_pLightManager->GetLightCount(); i++)
	{
		vecLights.push_back(g_pLightManager->GetLight(i));
	}

	Light* light;
	tinyxml2::XMLDocument new_xml_doc;
	tinyxml2::XMLNode* newRoot = new_xml_doc.InsertFirstChild(new_xml_doc.NewElement("LIGHTS"));

	for (unsigned index = 0; index < vecLights.size(); index++)
	{
		light = vecLights[index];

		tinyxml2::XMLElement* newLightElement = new_xml_doc.NewElement("Light");

		SetXYZ(newLightElement->InsertEndChild(new_xml_doc.NewElement("Rotation")), light->Rotation);
		SetXYZ(newLightElement->InsertEndChild(new_xml_doc.NewElement("Direction")), light->Direction);
		SetXYZ(newLightElement->InsertEndChild(new_xml_doc.NewElement("Position")), light->Position);
		SetRGB(newLightElement->InsertEndChild(new_xml_doc.NewElement("Diffuse")), light->Diffuse);
		SetRGBA(newLightElement->InsertEndChild(new_xml_doc.NewElement("Specular")), light->Specular);

		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("ConstAtten")))->SetAttribute("f", light->ConstAtten);
		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("LinearAtten")))->SetAttribute("f", light->LinearAtten);
		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("QuadraticAtten")))->SetAttribute("f", light->QuadraticAtten);
		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("CutOffDistance")))->SetAttribute("f", light->CutOffDistance);

		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("LightType")))->SetAttribute("type", light->lightType);

		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("SpotInnerAngle")))->SetAttribute("f", light->SpotInnerAngle);
		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("SpotOuterAngle")))->SetAttribute("f", light->SpotOuterAngle);

		((tinyxml2::XMLElement*)newLightElement->InsertEndChild(new_xml_doc.NewElement("IsLightOn")))->SetAttribute("b", light->isLightOn);

		(tinyxml2::XMLElement*)newRoot->InsertEndChild(newLightElement);
	}
	new_xml_doc.SaveFile(File.c_str());
}




void LoadCamera(std::string File, FreeCameraManager* Camera)
{
	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(File.c_str());
	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("CAMERA");
	tinyxml2::XMLElement* cameraElement = root->FirstChildElement("Camera");

	Camera->Pitch(-(Camera->Pitch()));
	Camera->Yaw(-(Camera->Yaw()));

	Camera->Pitch(cameraElement->FirstChildElement("Pitch")->FindAttribute("f")->FloatValue());
	Camera->Yaw(cameraElement->FirstChildElement("Yaw")->FindAttribute("f")->FloatValue());
	Camera->SetPosition(GetXYZ(cameraElement->FirstChildElement("Position")));

	Camera->Target(GetXYZ(cameraElement->FirstChildElement("Target")));

	Camera->LockTarget(cameraElement->FirstChildElement("LockTarget")->FindAttribute("b")->BoolValue());

}

void SaveCamera(std::string File, FreeCameraManager* Camera)
{
	tinyxml2::XMLDocument new_xml_doc;
	tinyxml2::XMLNode* newRoot = new_xml_doc.InsertFirstChild(new_xml_doc.NewElement("CAMERA"));
	tinyxml2::XMLElement* cameraElement = new_xml_doc.NewElement("Camera");


	SetXYZ(cameraElement->InsertEndChild(new_xml_doc.NewElement("Position")), Camera->GetPosition());

	((tinyxml2::XMLElement*)cameraElement->InsertEndChild(new_xml_doc.NewElement("Pitch")))->SetAttribute("f", Camera->Pitch());
	((tinyxml2::XMLElement*)cameraElement->InsertEndChild(new_xml_doc.NewElement("Yaw")))->SetAttribute("f", Camera->Yaw());

	SetXYZ(cameraElement->InsertEndChild(new_xml_doc.NewElement("Target")), Camera->Target());

	((tinyxml2::XMLElement*)cameraElement->InsertEndChild(new_xml_doc.NewElement("LockTarget")))->SetAttribute("b", Camera->LockTarget());

	(tinyxml2::XMLElement*)newRoot->InsertEndChild(cameraElement);

	new_xml_doc.SaveFile(File.c_str());
}