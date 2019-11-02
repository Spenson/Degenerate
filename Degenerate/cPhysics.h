#ifndef _cPhysics_HG_
#define _cPhysics_HG_

#include "GameObject.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <map>

class cPhysics
{
public:
	cPhysics();

	// Alias to a type "existing type" "new type name"
	typedef glm::vec3 Point;
	typedef glm::vec3 Vector;

	struct Sphere
	{
		glm::vec3 c;
		float r;
	};	

	struct sPhysicsTriangle
	{
		glm::vec3 verts[3];
		glm::vec3 normal;
	};

	struct sCollisionInfo
	{
		glm::vec3 closestPoint;
		glm::vec3 directionOfApproach;
		float penetrationDistance;
		glm::vec3 adjustmentVector;
		glm::vec3 reflectionNormal;
		//glm::vec3 bounceVelocity;
		GameObject* pObject1;		// Shpere
		GameObject* pObject2;		// Sphere or Triangle
	};
	
	// This "moves" the objects based on the inegration step
	void IntegrationStep( std::vector<GameObject*>& vec_pGameObjects,
					      float deltaTime );

	void TestForCollisions( std::vector<GameObject*>& vec_pGameObjects );

	// Returns all the triangles and the closest points
	void GetClosestTriangleToPoint( Point pointXYZ, Mesh &mesh, glm::vec3 &closestPoint, sPhysicsTriangle &closestTriangle );

	// Will return the closest triangles that are within the range "distanceRange".
	// This can be used as a "closest triangles to sphere"
	void GetClosestTrianglesToSphere( GameObject &testSphere, float distanceRange, Mesh &mesh, std::vector<sPhysicsTriangle> &vecClosestTriangles );


	// Taken from Ericson's book:
	Point ClosestPtPointTriangle(Point p, Point a, Point b, Point c);
	int TestSphereTriangle(Sphere s, Point a, Point b, Point c, Point& p);

	void ProcessCollisions(void);

	void setGravity( glm::vec3 newGravityValue );
	glm::vec3 getGravity(void);


	void sphereCollisionResponse(sCollisionInfo& collisionInfo);
	void sphereMeshCollisionResponse(sCollisionInfo& collisionInfo);




private:

	// Does collision test and returns collision information
	// Returns true if collision, and will load collisionInfo struct
	bool DoSphereSphereCollisionTest( GameObject* pA, GameObject *pB, 
									  sCollisionInfo &collisionInfo );
	bool DoShphereMeshCollisionTest( GameObject* pA, GameObject* pB,
									 sCollisionInfo &collisionInfo );
	void CalculateTransformedMesh(Mesh& originalMesh, glm::mat4 matWorld,
							 Mesh& mesh_transformedInWorld);
	std::map<std::string, std::vector<sCollisionInfo>> mapCollisions;

	glm::vec3  m_Gravity;

};

#endif
