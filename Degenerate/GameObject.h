#pragma once

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <string>

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
	std::string meshName;			//"Pirate"

	// Values that we can assign and then look for them
	unsigned int friendlyIDNumber;
	std::string friendlyName;

	glm::vec3 previousPosition;

	glm::vec3  position;
	glm::vec3  rotation;
	glm::vec3  scale;

	glm::mat4 matWorld;

	glm::vec4  objectColour;

	// Likely want this now:
	glm::vec4 diffuseColour;		// Colour of the object
	glm::vec4 specularColour;		// Colour of the HIGHLIGHT + Shininess
									// RGB - colour
									// 4th value (a or w) is the "power"
									// 1.0 to 10,000.0f 
	float ambientToDiffuseRatio;


	// Add some physics things
	glm::vec3 velocity;
	glm::vec3 accel;

	float inverseMass;	// 0.0f = Doesn't move

	ShapeTypes physicsShapeType;
	// 
	glm::vec3 AABB_min, AABB_max;
	float SPHERE_radius;

	// Won't be lit, and is wireframe
	bool isWireframe;
	glm::vec4 debugColour;

	bool isVisible;

	bool disableDepthBufferTest;
	bool disableDepthBufferWrite;

	unsigned int getUniqueID(void);

	//void setDebugRenderer(iDebugRenderer* pDebugRenderer);

private:
	// this variable is static, so common to all objects.
	// When the object is created, the unique ID is set, and 
	//	the next unique ID is incremented
	static unsigned int next_uniqueID;
	unsigned int m_uniqueID;

	//iDebugRenderer* m_pDebugRenderer;
};