#include "FileReaders.h"
#include "Light.h"
#include "GameObject.h"
#include <tinyxml2/tinyxml2.h>



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

void insertAttributes(tinyxml2::XMLNode* node, glm::vec3 vals)
{
	((tinyxml2::XMLElement*)node)->SetAttribute("x", vals.x);
	((tinyxml2::XMLElement*)node)->SetAttribute("y", vals.y);
	((tinyxml2::XMLElement*)node)->SetAttribute("z", vals.z);
}

void insertAttributes(tinyxml2::XMLNode* node, glm::vec4 vals)
{
	((tinyxml2::XMLElement*)node)->SetAttribute("r", vals.r);
	((tinyxml2::XMLElement*)node)->SetAttribute("g", vals.g);
	((tinyxml2::XMLElement*)node)->SetAttribute("b", vals.b);
	((tinyxml2::XMLElement*)node)->SetAttribute("a", vals.a);
}


void ReadGameObjectsFromFile(std::string File, std::vector<GameObject*>& vecGameObjects, bool clearExistingObjects = 1)
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

	tinyxml2::XMLElement* element = root->FirstChildElement("GameObject");
	//for (tinyxml2::XMLElement* element = root->FirstChildElement("GameObject"); element != root->LastChildElement(); element = element->NextSiblingElement())
	for (;;)
	{
		object = new GameObject();
		object->meshName = element->FirstChildElement("MeshName")->GetText();
		object->friendlyName = element->FirstChildElement("FriendlyName")->GetText();

		object->positionXYZ = GetXYZ(element->FirstChildElement("Position"));
		object->rotationXYZ = GetXYZ(element->FirstChildElement("Rotation"));

		object->scale = element->FirstChildElement("Scale")->FindAttribute("f")->FloatValue();

		object->objectColourRGBA = GetRGBA(element->FirstChildElement("Colour"));
		object->diffuseColour = GetRGBA(element->FirstChildElement("DiffuseColour"));
		object->specularColour = GetRGBA(element->FirstChildElement("SpecularColour"));
		object->ambientToDiffuseRatio = element->FirstChildElement("AmbientDiffuseRatio")->FindAttribute("f")->FloatValue();
		object->debugColour = GetRGBA(element->FirstChildElement("DebugColour"));


		object->velocity = GetXYZ(element->FirstChildElement("Velocity"));
		object->accel = GetXYZ(element->FirstChildElement("Acceleration"));
		object->inverseMass = element->FirstChildElement("InverseMass")->FindAttribute("f")->FloatValue();

		object->physicsShapeType = (ShapeTypes)element->FirstChildElement("PhysicsShapeType")->FindAttribute("type")->IntValue();
		object->AABB_min = GetXYZ(element->FirstChildElement("AABB")->FirstChildElement("max"));
		object->AABB_max = GetXYZ(element->FirstChildElement("AABB")->FirstChildElement("min"));
		object->SPHERE_radius = element->FirstChildElement("Radius")->FindAttribute("f")->FloatValue();

		object->isWireframe = element->FirstChildElement("Wireframe")->FindAttribute("b")->BoolValue();
		object->isVisible = element->FirstChildElement("Visible")->FindAttribute("b")->BoolValue();
		object->disableDepthBufferTest = element->FirstChildElement("DisableDepthTest")->FindAttribute("b")->BoolValue();
		object->disableDepthBufferWrite = element->FirstChildElement("DisableDepthWrite")->FindAttribute("b")->BoolValue();

		vecGameObjects.push_back(object);

		if (element == root->LastChildElement())
			break;
		element = element->NextSiblingElement();
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

		tinyxml2::XMLElement* newElement = new_xml_doc.NewElement("GameObject");

		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("MeshName")))->SetText(object->meshName.c_str());
		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("FriendlyName")))->SetText(object->friendlyName.c_str());

		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("Position")), object->positionXYZ);
		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("Rotation")), object->rotationXYZ);

		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("Scale")))->SetAttribute("f", object->scale);

		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("Colour")), object->objectColourRGBA);
		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("DiffuseColour")), object->diffuseColour);
		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("SpecularColour")), object->specularColour);
		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("DebugColour")), object->debugColour);

		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("AmbientDiffuseRatio")))->SetAttribute("f", object->ambientToDiffuseRatio);

		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("Velocity")), object->velocity);
		insertAttributes(newElement->InsertEndChild(new_xml_doc.NewElement("Acceleration")), object->accel);

		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("InverseMass")))->SetAttribute("f", object->inverseMass);

		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("PhysicsShapeType")))->SetAttribute("type", object->physicsShapeType);

		tinyxml2::XMLElement* AABBNode = (tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("AABB"));
		insertAttributes(AABBNode->InsertEndChild(new_xml_doc.NewElement("max")), object->AABB_max);
		insertAttributes(AABBNode->InsertEndChild(new_xml_doc.NewElement("min")), object->AABB_min);

		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("Radius")))->SetAttribute("f", object->SPHERE_radius);

		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("Wireframe")))->SetAttribute("b", object->isWireframe);
		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("Visible")))->SetAttribute("b", object->isVisible);
		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("DisableDepthTest")))->SetAttribute("b", object->disableDepthBufferTest);
		((tinyxml2::XMLElement*)newElement->InsertEndChild(new_xml_doc.NewElement("DisableDepthWrite")))->SetAttribute("b", object->disableDepthBufferWrite);

		(tinyxml2::XMLElement*)newRoot->InsertEndChild(newElement);
	}
	new_xml_doc.SaveFile(File.c_str());
}

void ReadLightsFromFile(std::string File, std::vector<Light*>& lights, bool clearExistingLights = 1)
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

	tinyxml2::XMLElement* element = root->FirstChildElement("Light");
	for (;;)
	{
		light = new Light();

		light->Position = GetXYZ(element->FirstChildElement("Position"));
		light->Direction = GetXYZ(element->FirstChildElement("Direction"));
		light->Diffuse = GetRGB(element->FirstChildElement("Diffuse"));

		light->ConstAtten = element->FirstChildElement("ConstAtten")->FindAttribute("f")->FloatValue();
		light->LinearAtten = element->FirstChildElement("LinearAtten")->FindAttribute("f")->FloatValue();
		light->QuadraticAtten = element->FirstChildElement("QuadraticAtten")->FindAttribute("f")->FloatValue();
		light->CutOffDistance = element->FirstChildElement("CutOffDistance")->FindAttribute("f")->FloatValue();

		light->lightType = (Light::LightType) element->FirstChildElement("LightType")->FindAttribute("type")->IntValue();

		light->SpotInnerAngle = element->FirstChildElement("SpotInnerAngle")->FindAttribute("f")->FloatValue();
		light->SpotOuterAngle = element->FirstChildElement("SpotOuterAngle")->FindAttribute("f")->FloatValue();
		light->isLightOn = element->FirstChildElement("IsLightOn")->FindAttribute("b")->BoolValue();

		lights.push_back(light);

		if (element == root->LastChildElement())
			break;
		element = element->NextSiblingElement();
	}
