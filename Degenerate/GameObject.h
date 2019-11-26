#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/quaternion.hpp>

#include <string>

// NOTE: We are including the INTERFACE, not the actual renderer
#include "DebugRenderer/iDebugRenderer.h"

enum ShapeTypes
{
	AABB,					// min and max corners 
	SPHERE,					// Radius
	CAPSULE,
	PLANE,
	MESH,		// Triangle test
	UNKNOWN
};

class GameObject
{
public:
	GameObject();
	
	// Used to draw this mesh
	std::string meshName;
	// Values that we can assign and then look for them
	unsigned int friendlyIDNumber;
	std::string friendlyName;

	glm::vec3 previousPosition;
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 accel;

	glm::vec3 scale;
	glm::mat4 matWorld;

	// Likely want this now:
	glm::vec4 diffuseColour;		// Colour of the object
	glm::vec4 specularColour;		// Colour of the HIGHLIGHT + Shininess
	glm::vec4 debugColour;			// RGB - colour
	glm::vec4 objectColour;			// 4th value (a or w) is the "power"
									// 1.0 to 10,000.0f 

	float inverseMass;	// 0.0f = Doesn't move
	std::vector<glm::vec3> vecPhysTestPoints;

	ShapeTypes physicsShapeType;
	// 
	glm::vec3 AABB_min, AABB_max;
	float SPHERE_radius;

	bool isWireframe;
	bool isVisible;
	bool disableDepthBufferTest;
	bool disableDepthBufferWrite;

	static const int NUMBEROFTEXTURES = 4;
	std::string textures[NUMBEROFTEXTURES];
	float textureRatio[NUMBEROFTEXTURES];

	// Add child object to the this mesh
	std::vector<GameObject*> vec_pChildObjects;

private:
	glm::quat rotation;
public:
	glm::quat getQOrientation(void);

	// Overwrite the orientation
	void setOrientation(glm::vec3 EulerAngleDegreesXYZ);
	void setOrientation(glm::quat qAngle);
	// Updates the existing angle
	void updateOrientation(glm::vec3 EulerAngleDegreesXYZ);
	void updateOrientation(glm::quat qAngle);
	glm::vec3 getEulerAngle(void);

	// Add some physics things
	// NOTE: This will depend on the orientation of your model (in mesh lab)
	void MoveInRelativeDirection(glm::vec3 relativeDirection);

	unsigned int getUniqueID(void);
	void setDebugRenderer(iDebugRenderer* pDebugRenderer);

private:
	// this variable is static, so common to all objects.
	// When the object is created, the unique ID is set, and 
	//	the next unique ID is incremented
	static unsigned int next_uniqueID;
	unsigned int m_uniqueID;

	iDebugRenderer* m_pDebugRenderer;
};