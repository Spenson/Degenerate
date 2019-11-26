#include "GameObject.h"

GameObject::GameObject()
{
	this->scale = glm::vec3(0.0f, 0.0f, 0.0f);
	this->isVisible = true;

	this->isWireframe = false;
	this->debugColour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
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

void GameObject::setDebugRenderer(iDebugRenderer* pDebugRenderer)
{
	this->m_pDebugRenderer = pDebugRenderer;
	return;
}


// this variable is static, so common to all objects.
// When the object is created, the unique ID is set, and 
//	the next unique ID is incremented
//static 
unsigned int GameObject::next_uniqueID = 1000;	// Starting at 1000, just because



//glm::quat m_qRotation;		// Orientation as a quaternion
glm::quat GameObject::getQOrientation(void)
{
	return this->rotation;
}

// Overwrite the orientation
void GameObject::setOrientation(glm::vec3 EulerAngleDegreesXYZ)
{
	// c'tor of the glm quaternion converts Euler 
	//	to quaternion representation. 
	glm::vec3 EulerAngleRadians;
	EulerAngleRadians.x = glm::radians(EulerAngleDegreesXYZ.x);
	EulerAngleRadians.y = glm::radians(EulerAngleDegreesXYZ.y);
	EulerAngleRadians.z = glm::radians(EulerAngleDegreesXYZ.z);

	this->rotation = glm::quat(EulerAngleRadians);
}

void GameObject::setOrientation(glm::quat qAngle)
{
	this->rotation = qAngle;
}

// Updates the existing angle
void GameObject::updateOrientation(glm::vec3 EulerAngleDegreesXYZ)
{
	// Create a quaternion of this angle...
	glm::vec3 EulerAngleRadians;
	EulerAngleRadians.x = glm::radians(EulerAngleDegreesXYZ.x);
	EulerAngleRadians.y = glm::radians(EulerAngleDegreesXYZ.y);
	EulerAngleRadians.z = glm::radians(EulerAngleDegreesXYZ.z);

	glm::quat angleChange = glm::quat(EulerAngleRadians);

	// ...apply it to the exiting rotation
	this->rotation *= angleChange;
}

void GameObject::updateOrientation(glm::quat qAngleChange)
{
	this->rotation *= qAngleChange;
}

glm::vec3 GameObject::getEulerAngle(void)
{
	// In glm::gtx (a bunch of helpful things there)
	glm::vec3 EulerAngle = glm::eulerAngles(this->rotation);

	return EulerAngle;
}


// Move it based on the "Front" of the object. 
// ASSUMPTION is the "FRONT" is +ve Z. 
// LEFT is +ve Z
// UP is +vs Y
// NOTE: This will depend on the orientation of your model (in mesh lab)
void GameObject::MoveInRelativeDirection(glm::vec3 relativeDirection)
{
	// The "forward" vector is +ve Z
	// (the 4th number is because we need a vec4 later)
	glm::vec4 forwardDirObject = glm::vec4(relativeDirection, 1.0f);

	glm::mat4 matModel = glm::mat4(1.0f);	// Identity

	// Roation
	// Constructor for the GLM mat4x4 can take a quaternion
	glm::mat4 matRotation = glm::mat4(this->getQOrientation());
	matModel *= matRotation;
	// *******************

	// Like in the vertex shader, I mulitly the test points
	// by the model matrix (MUST be a VEC4 because it's a 4x4 matrix)
	glm::vec4 forwardInWorldSpace = matModel * forwardDirObject;


	// Add this to the position of the object
	this->position += glm::vec3(forwardInWorldSpace);

	return;
}
