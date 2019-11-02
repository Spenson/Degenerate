#include "GameObject.h"

GameObject::GameObject()
{
	this->scale = glm::vec3(0.0f, 0.0f, 0.0f);
	this->isVisible = true;

	this->isWireframe = false;
	this->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	this->accel = glm::vec3(0.0f, 0.0f, 0.0f);
	this->inverseMass = 0.0f;	// Infinite mass
	this->physicsShapeType = UNKNOWN;

	// Set the unique ID
	// Take the value of the static int, 
	//  set this to the instance variable
	this->m_uniqueID = GameObject::next_uniqueID;
	// Then increment the static variable
	GameObject::next_uniqueID++;

	this->disableDepthBufferTest = false;
	this->disableDepthBufferWrite = false;

	//this->m_pDebugRenderer = NULL;

	return;
}


unsigned int GameObject::getUniqueID(void)
{
	return this->m_uniqueID;
}

//void GameObject::setDebugRenderer(iDebugRenderer* pDebugRenderer)
//{
//	this->m_pDebugRenderer = pDebugRenderer;
//	return;
//}


// this variable is static, so common to all objects.
// When the object is created, the unique ID is set, and 
//	the next unique ID is incremented
//static 
unsigned int GameObject::next_uniqueID = 1000;	// Starting at 1000, just because
