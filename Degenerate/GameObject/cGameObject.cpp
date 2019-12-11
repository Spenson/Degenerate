#include "cGameObject.h"
#include <glm/gtx/quaternion.hpp>
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp>

std::vector<cGameObject*> g_vec_pGameObjects;


cGameObject* pFindObjectByFriendlyName(std::string name)
{
	// Do a linear search 
	for (unsigned int index = 0;
		 index != g_vec_pGameObjects.size(); index++)
	{
		if (::g_vec_pGameObjects[index]->friendlyName == name)
		{
			// Found it!!
			return ::g_vec_pGameObjects[index];
		}//if (::g_vec_pGameObjects[index]

		// Also look for the child objects
		for (unsigned int indexChild = 0;
			 indexChild != ::g_vec_pGameObjects[index]->vec_pChildObjects.size(); indexChild++)
		{
			if (::g_vec_pGameObjects[index]->vec_pChildObjects[indexChild]->friendlyName == name)
			{
				// Found it!!
				return ::g_vec_pGameObjects[index]->vec_pChildObjects[indexChild];
			}//if (::g_vec_pGameObjects[index]

		}//for (unsigned int index = 0;


	}//for (unsigned int index = 0;
	// Didn't find it
	return NULL;
}





cGameObject::cGameObject()
{
	// Set the unique ID
	// Take the value of the static int, 
	//  set this to the instance variable
	this->m_uniqueID = cGameObject::next_uniqueID;
	// Then increment the static variable
	cGameObject::next_uniqueID++;


	this->positionXYZ = glm::vec3(0.0f);
	this->velocity = glm::vec3(0.0f);
	this->accel = glm::vec3(0.0f);

	this->scale = 0.0f;

	this->inverseMass = 0.0f;	// Infinite mass
	this->physicsShapeType = UNKNOWN;
	this->PhysicsSphere = scale;

	this->objectColourRGBA = glm::vec4(1.0f);
	this->debugColour = glm::vec4(1.0f);
	this->diffuseColour = glm::vec4(1.0f);
	this->specularColour = glm::vec4(1.0f, 1.0f, 1.0f, 1000.0f);

	this->textures[0] = "gridtexture.bmp";
	this->textureRatio[0] = 1.0f;
	this->textureRatio[1] = 0.0f;
	this->textureRatio[2] = 0.0f;
	this->textureRatio[3] = 0.0f;

	this->useDiffuse = false;
	this->isImposter = false;
	this->isWireframe = false;
	this->doNotLight = false;
	this->isVisible = true;
	this->disableDepthBufferTest = false;
	this->disableDepthBufferWrite = false;

	// Rotation of 0 degrees.
	this->m_qRotation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
	this->m_qAngularVelocity = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));

	this->m_pDebugRenderer = NULL;

	return;
}


unsigned int cGameObject::getUniqueID(void)
{
	return this->m_uniqueID;
}

void cGameObject::setDebugRenderer(iDebugRenderer* pDebugRenderer)
{
	this->m_pDebugRenderer = pDebugRenderer;
	return;
}


// this variable is static, so common to all objects.
// When the m_pGO is created, the unique ID is set, and 
//	the next unique ID is incremented
//static 
unsigned int cGameObject::next_uniqueID = 1000;	// Starting at 1000, just because





//glm::quat m_qRotation;		// Orientation as a quaternion
glm::quat cGameObject::getQOrientation(void)
{
	return this->m_qRotation;
}

// Overwrite the orientation
void cGameObject::setOrientation(glm::vec3 EulerAngleDegreesXYZ)
{
	// c'tor of the glm quaternion converts Euler 
	//	to quaternion representation. 
	glm::vec3 EulerAngleRadians;
	//EulerAngleRadians.x = glm::radians(EulerAngleDegreesXYZ.x);
	//EulerAngleRadians.y = glm::radians(EulerAngleDegreesXYZ.y);
	//EulerAngleRadians.z = glm::radians(EulerAngleDegreesXYZ.z); 
	
	EulerAngleRadians = glm::radians(EulerAngleDegreesXYZ);

	this->m_qRotation = glm::quat(EulerAngleRadians);
}


//glm::quat m_qRotation;		// Orientation as a quaternion
glm::quat cGameObject::getQAngularVelocity(void)
{
	return this->m_qAngularVelocity;
}

// Overwrite the orientation
void cGameObject::setAngularVelocity(glm::vec3 EulerAngleDegreesXYZ)
{
	// c'tor of the glm quaternion converts Euler 
	//	to quaternion representation. 
	glm::vec3 EulerAngleRadians;
	//EulerAngleRadians.x = glm::radians(EulerAngleDegreesXYZ.x);
	//EulerAngleRadians.y = glm::radians(EulerAngleDegreesXYZ.y);
	//EulerAngleRadians.z = glm::radians(EulerAngleDegreesXYZ.z);
	
	EulerAngleRadians = glm::radians(EulerAngleDegreesXYZ);

	this->m_qAngularVelocity = glm::quat(EulerAngleRadians);
}



void cGameObject::setOrientation(glm::quat qAngle)
{
	this->m_qRotation = qAngle;
}

// Updates the existing angle
void cGameObject::updateOrientation(glm::vec3 EulerAngleDegreesXYZ)
{
	// Create a quaternion of this angle...
	glm::vec3 EulerAngleRadians;
	EulerAngleRadians.x = glm::radians(EulerAngleDegreesXYZ.x);
	EulerAngleRadians.y = glm::radians(EulerAngleDegreesXYZ.y);
	EulerAngleRadians.z = glm::radians(EulerAngleDegreesXYZ.z);

	glm::quat angleChange = glm::quat(EulerAngleRadians);

	// ...apply it to the exiting rotation
	this->m_qRotation *= angleChange;
}

void cGameObject::updateOrientation(glm::quat qAngleChange)
{
	this->m_qRotation *= qAngleChange;
}

glm::vec3 cGameObject::getEulerAngle(void)
{
	// In glm::gtx (a bunch of helpful things there)
	glm::vec3 EulerAngle = glm::eulerAngles(this->m_qRotation);

	return EulerAngle;
}


// Move it based on the "Front" of the m_pGO. 
// ASSUMPTION is the "FRONT" is +ve Z. 
// LEFT is +ve Z
// UP is +vs Y
// NOTE: This will depend on the orientation of your model (in mesh lab)
void cGameObject::MoveInRelativeDirection(glm::vec3 relativeDirection)
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


	// Add this to the position of the m_pGO
	this->positionXYZ += glm::vec3(forwardInWorldSpace);

	return;
}
