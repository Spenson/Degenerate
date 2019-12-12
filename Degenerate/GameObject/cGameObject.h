#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>		// The quaternion class
#include <string>

// NOTE: We are including the INTERFACE, not the actual renderer
#include "../DebugRenderer/iDebugRenderer.h"


enum eShapeTypes
{
	UNKNOWN,
	AABB,	
	SPHERE,		
	CAPSULE,
	PLANE,
	MESH,	
	POINTSET
};

class cGameObject
{
public:
	cGameObject();

	//points to draw
	std::string meshName;	


	unsigned int friendlyIDNumber;
	std::string friendlyName;

	//Position/Movement
	glm::vec3  positionXYZ;
	glm::vec3 velocity;
	glm::vec3 accel;
	void MoveInRelativeDirection(glm::vec3 relativeDirection);

	float scale;
	
	// Collision
	float inverseMass;
	eShapeTypes physicsShapeType;
	glm::vec3 AABB_min, AABB_max;
	float PhysicsSphere;
	std::vector<glm::vec3> vecPhysTestPoints;

	//Colour/ Texture
	glm::vec4  objectColourRGBA;

	// Default will set to 1.0f
	//float alphaTransparency;		// Switched to the a on diffuse
	glm::vec4 debugColour;			// Wireframe Colour

	// Likely want this now:
	glm::vec4 diffuseColour;		
	glm::vec4 specularColour;		// Highlight Colour (added to light? TODO: Check that)
	
	static const int NUMBEROFTEXTURES = 4;
	std::string textures[NUMBEROFTEXTURES];
	float textureRatio[NUMBEROFTEXTURES];

	std::string heightMap;


	// Debug/testing
	bool useDiffuse;
	bool isImposter;
	bool doNotLight;
	bool isWireframe;
	bool isVisible;
	bool disableDepthBufferTest;
	bool disableDepthBufferWrite;


	// Add child m_pGO to the this mesh
	std::vector<cGameObject*> vec_pChildObjects;

private:
	glm::quat m_qRotation;		// Orientation as a quaternion
	glm::quat m_qAngularVelocity;
public:
	glm::quat getQOrientation(void);
	glm::quat getQAngularVelocity(void);

	// Overwrite the orientation
	void setOrientation(glm::vec3 EulerAngleDegreesXYZ);
	void setAngularVelocity(glm::vec3 EulerAngleDegreesXYZ);
	void setOrientation(glm::quat qAngle);
	// Updates the existing angle
	void updateOrientation(glm::vec3 EulerAngleDegreesXYZ);
	void updateOrientation(glm::quat qAngle);
	glm::vec3 getEulerAngle(void);


	unsigned int getUniqueID(void);

	void setDebugRenderer(iDebugRenderer* pDebugRenderer);

	iDebugRenderer* m_pDebugRenderer;
private:
	static unsigned int next_uniqueID;
	unsigned int m_uniqueID;

};

cGameObject* pFindObjectByFriendlyName(std::string name);



