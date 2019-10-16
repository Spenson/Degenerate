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

void insertAttributes(tinyxml2::XMLNode* node, glm::vec3 vals, bool isRGB = 0)
{
	if (isRGB)
	{
		((tinyxml2::XMLElement*)node)->SetAttribute("r", vals.x);
		((tinyxml2::XMLElement*)node)->SetAttribute("g", vals.y);
		((tinyxml2::XMLElement*)node)->SetAttribute("b", vals.z);
	}
	else
	{
		((tinyxml2::XMLElement*)node)->SetAttribute("x", vals.x);
		((tinyxml2::XMLElement*)node)->SetAttribute("y", vals.y);
		((tinyxml2::XMLElement*)node)->SetAttribute("z", vals.z);

	}
}

void insertAttributes(tinyxml2::XMLNode* node, glm::vec4 vals)
{
	((tinyxml2::XMLElement*)node)->SetAttribute("r", vals.r);
	((tinyxml2::XMLElement*)node)->SetAttribute("g", vals.g);
	((tinyxml2::XMLElement*)node)->SetAttribute("b", vals.b);
	((tinyxml2::XMLElement*)node)->SetAttribute("a", vals.a);
}


void ReadGameObjectsFromFile(std::string File, std::vector<GameObject*>& vecGameObjects, bool clearExistingObjects)
{
	if (clearExistingObjects)
	{
		for (unsigned index = 0; index < vecGameObjects.size(); index++)
			delete vecGameObjects[index];

		vecGameObjects.clear();
	}

	GameObject* object;
	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(File.c_str());
	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("GAMEOBJECTS");

	tinyxml2::XMLElement* objectElement = root->FirstChildElement("GameObject");
	//for (tinyxml2::XMLElement* element = root->FirstChildElement("GameObject"); element != root->LastChildElement(); element = element->NextSiblingElement())
	for (;;)
	{
		object = new GameObject();
		object->meshName = objectElement->FirstChildElement("MeshName")->GetText();
		object->friendlyName = objectElement->FirstChildElement("FriendlyName")->GetText();

		object->positionXYZ = GetXYZ(objectElement->FirstChildElement("Position"));
		object->rotationXYZ = GetXYZ(objectElement->FirstChildElement("Rotation"));

		object->scale = objectElement->FirstChildElement("Scale")->FindAttribute("f")->FloatValue();

		object->objectColourRGBA = GetRGBA(objectElement->FirstChildElement("Colour"));
		object->diffuseColour = GetRGBA(objectElement->FirstChildElement("DiffuseColour"));
		object->specularColour = GetRGBA(objectElement->FirstChildElement("SpecularColour"));
		object->ambientToDiffuseRatio = objectElement->FirstChildElement("AmbientDiffuseRatio")->FindAttribute("f")->FloatValue();
		object->debugColour = GetRGBA(objectElement->FirstChildElement("DebugColour"));


		object->velocity = GetXYZ(objectElement->FirstChildElement("Velocity"));
		object->accel = GetXYZ(objectElement->FirstChildElement("Acceleration"));
		object->inverseMass = objectElement->FirstChildElement("InverseMass")->FindAttribute("f")->FloatValue();

		object->physicsShapeType = (ShapeTypes)objectElement->FirstChildElement("PhysicsShapeType")->FindAttribute("type")->IntValue();
		object->AABB_min = GetXYZ(objectElement->FirstChildElement("AABB")->FirstChildElement("max"));
		object->AABB_max = GetXYZ(objectElement->FirstChildElement("AABB")->FirstChildElement("min"));
		object->SPHERE_radius = objectElement->FirstChildElement("Radius")->FindAttribute("f")->FloatValue();

		object->isWireframe = objectElement->FirstChildElement("Wireframe")->FindAttribute("b")->BoolValue();
		object->isVisible = objectElement->FirstChildElement("Visible")->FindAttribute("b")->BoolValue();
		object->disableDepthBufferTest = objectElement->FirstChildElement("DisableDepthTest")->FindAttribute("b")->BoolValue();
		object->disableDepthBufferWrite = objectElement->FirstChildElement("DisableDepthWrite")->FindAttribute("b")->BoolValue();

		vecGameObjects.push_back(object);

		if (objectElement == root->LastChildElement())
			break;
		objectElement = objectElement->NextSiblingElement();
	}
}

void WriteGameObjectsToFile(std::string File, std::vector<GameObject*> vecGameObjects)
{
	GameObject* object;
	tinyxml2::XMLDocument new_xml_doc;
	tinyxml2::XMLNode* newRoot = new_xml_doc.InsertFirstChild(new_xml_doc.NewElement("GAMEOBJECT"));

	for (unsigned index = 0; index < vecGameObjects.size(); index++)
	{
		object = vecGameObjects[index];

		tinyxml2::XMLElement* newObjectElement = new_xml_doc.NewElement("GameObject");

		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("MeshName")))->SetText(object->meshName.c_str());
		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("FriendlyName")))->SetText(object->friendlyName.c_str());

		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("Position")), object->positionXYZ);
		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("Rotation")), object->rotationXYZ);

		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("Scale")))->SetAttribute("f", object->scale);

		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("Colour")), object->objectColourRGBA);
		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("DiffuseColour")), object->diffuseColour);
		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("SpecularColour")), object->specularColour);
		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("DebugColour")), object->debugColour);

		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("AmbientDiffuseRatio")))->SetAttribute("f", object->ambientToDiffuseRatio);

		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("Velocity")), object->velocity);
		insertAttributes(newObjectElement->InsertEndChild(new_xml_doc.NewElement("Acceleration")), object->accel);

		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("InverseMass")))->SetAttribute("f", object->inverseMass);

		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("PhysicsShapeType")))->SetAttribute("type", object->physicsShapeType);

		tinyxml2::XMLElement* AABBNode = (tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("AABB"));
		insertAttributes(AABBNode->InsertEndChild(new_xml_doc.NewElement("max")), object->AABB_max);
		insertAttributes(AABBNode->InsertEndChild(new_xml_doc.NewElement("min")), object->AABB_min);

		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("Radius")))->SetAttribute("f", object->SPHERE_radius);

		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("Wireframe")))->SetAttribute("b", object->isWireframe);
		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("Visible")))->SetAttribute("b", object->isVisible);
		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("DisableDepthTest")))->SetAttribute("b", object->disableDepthBufferTest);
		((tinyxml2::XMLElement*)newObjectElement->InsertEndChild(new_xml_doc.NewElement("DisableDepthWrite")))->SetAttribute("b", object->disableDepthBufferWrite);

		(tinyxml2::XMLElement*)newRoot->InsertEndChild(newObjectElement);
	}
	new_xml_doc.SaveFile(File.c_str());
}

void ReadLightsFromFile(std::string File, std::vector<Light*>& lights, bool clearExistingLights)
{
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

		light->Position = GetXYZ(lightElement->FirstChildElement("Position"));
		light->Direction = GetXYZ(lightElement->FirstChildElement("Direction"));
		light->Diffuse = GetRGB(lightElement->FirstChildElement("Diffuse"));

		light->ConstAtten = lightElement->FirstChildElement("ConstAtten")->FindAttribute("f")->FloatValue();
		light->LinearAtten = lightElement->FirstChildElement("LinearAtten")->FindAttribute("f")->FloatValue();
		light->QuadraticAtten = lightElement->FirstChildElement("QuadraticAtten")->FindAttribute("f")->FloatValue();
		light->CutOffDistance = lightElement->FirstChildElement("CutOffDistance")->FindAttribute("f")->FloatValue();

		light->lightType = (Light::LightType) lightElement->FirstChildElement("LightType")->FindAttribute("type")->IntValue();

		light->SpotInnerAngle = lightElement->FirstChildElement("SpotInnerAngle")->FindAttribute("f")->FloatValue();
		light->SpotOuterAngle = lightElement->FirstChildElement("SpotOuterAngle")->FindAttribute("f")->FloatValue();
		light->isLightOn = lightElement->FirstChildElement("IsLightOn")->FindAttribute("b")->BoolValue();

		lights.push_back(light);

		if (lightElement == root->LastChildElement())
			break;
		lightElement = lightElement->NextSiblingElement();
	}
}

void WriteLightsToFile(std::string File, std::vector<Light*> vecLights)
{
	Light* light;
	tinyxml2::XMLDocument new_xml_doc;
	tinyxml2::XMLNode* newRoot = new_xml_doc.InsertFirstChild(new_xml_doc.NewElement("LIGHTS"));

	for (unsigned index = 0; index < vecLights.size(); index++)
	{
		light = vecLights[index];

		tinyxml2::XMLElement* newLightElement = new_xml_doc.NewElement("Light");

		insertAttributes(newLightElement->InsertEndChild(new_xml_doc.NewElement("Position")), light->Position);
		insertAttributes(newLightElement->InsertEndChild(new_xml_doc.NewElement("Direction")), light->Direction);
		insertAttributes(newLightElement->InsertEndChild(new_xml_doc.NewElement("Diffuse")), light->Diffuse, true);

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

void ReadMeshesFromFile(std::string File, std::string MeshDir, std::map<std::string, Mesh>& mapMeshes, ModelLoader* modelLoader)
{
	tinyxml2::XMLDocument xml_doc;
	tinyxml2::XMLError eResult = xml_doc.LoadFile(File.c_str());
	tinyxml2::XMLNode* root = xml_doc.FirstChildElement("MESHES");

	tinyxml2::XMLElement* meshElement = root->FirstChildElement("Mesh");
	std::string currentName;
	for (;;)
	{
		currentName = meshElement->FirstChildElement("Name")->GetText();
		if(! mapMeshes.count(currentName))
			if (!modelLoader->LoadPlyModel(MeshDir + meshElement->FirstChildElement("File")->GetText(), mapMeshes[currentName]))
			{
				std::cout << "Didn't find the file" << std::endl;
			}

		if (meshElement == root->LastChildElement())
			break;
		meshElement = meshElement->NextSiblingElement();
	}

}