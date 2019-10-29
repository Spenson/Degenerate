#include "cPhysics.h"
#include <map>
#include <iostream>
#include "globals.h"

extern std::map<std::string, Mesh> mMeshes;

cPhysics::cPhysics()
{
	// This is a typical Earth gravity value. 
	// note that this doesn't mean that the simulation will "look good", though... 
//	this->m_Gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	this->m_Gravity = glm::vec3(0.0f, 0.0f, 0.0f);
	return;
}


void cPhysics::setGravity(glm::vec3 newGravityValue)
{
	this->m_Gravity = newGravityValue;
	return;
}

glm::vec3 cPhysics::getGravity(void)
{
	return this->m_Gravity;
}


void cPhysics::IntegrationStep(std::vector<GameObject*>& vec_pGameObjects, float deltaTime)
{


	for (unsigned int index = 0;
		 index != vec_pGameObjects.size(); index++)
	{
		// Get a pointer to the current object (makes the code a little clearer)
		GameObject* pCurObj = vec_pGameObjects[index];

		if (pCurObj->inverseMass != 0.0f)
		{

			// Forward Explicit Euler Inetegration
			//NewVelocty += Velocity + ( Ax * DeltaTime )

			// 
			pCurObj->accel = this->m_Gravity;


			pCurObj->velocity.x += pCurObj->accel.x * deltaTime;
			pCurObj->velocity.y += pCurObj->accel.y * deltaTime;
			pCurObj->velocity.z += pCurObj->accel.z * deltaTime;
			//		// Or you can do this...
			//		CurObj.velocity += CurObj.accel * deltaTime;

					//NewPosition = Posistion + ( Vx * DeltaTime )

			pCurObj->position.x += pCurObj->velocity.x * deltaTime;
			pCurObj->position.y += pCurObj->velocity.y * deltaTime;
			pCurObj->position.z += pCurObj->velocity.z * deltaTime;


		}
	}//for (unsigned int index = 0;

	return;
}



// Returns all the triangles and the closest points
void cPhysics::GetClosestTriangleToPoint(Point pointXYZ, Mesh& mesh, glm::vec3& closestPoint, sPhysicsTriangle& closestTriangle)
{

	// Assume the closest distance is REALLY far away
	float closestDistanceSoFar = FLT_MAX;

	for (unsigned int triIndex = 0;
		 triIndex != mesh.vecTriangles.size();
		 triIndex++)
	{
		TriangleIndex& curTriangle = mesh.vecTriangles[triIndex];

		// Get the vertices of the triangle
		VertexPosNormTex triVert1 = mesh.vecVertices[curTriangle.a];
		VertexPosNormTex triVert2 = mesh.vecVertices[curTriangle.b];
		VertexPosNormTex triVert3 = mesh.vecVertices[curTriangle.c];

		Point triVertPoint1;
		triVertPoint1.x = triVert1.pos.x;
		triVertPoint1.y = triVert1.pos.y;
		triVertPoint1.z = triVert1.pos.z;

		Point triVertPoint2;
		triVertPoint2.x = triVert2.pos.x;
		triVertPoint2.y = triVert2.pos.y;
		triVertPoint2.z = triVert2.pos.z;

		Point triVertPoint3;
		triVertPoint3.x = triVert3.pos.x;
		triVertPoint3.y = triVert3.pos.y;
		triVertPoint3.z = triVert3.pos.z;

		glm::vec3 curClosetPoint = ClosestPtPointTriangle(pointXYZ,
														  triVertPoint1, triVertPoint2, triVertPoint3);

		// Is this the closest so far?
		float distanceNow = glm::distance(curClosetPoint, pointXYZ);

		// is this closer than the closest distance
		if (distanceNow <= closestDistanceSoFar)
		{
			closestDistanceSoFar = distanceNow;

			closestPoint = curClosetPoint;

			// Copy the triangle information over, as well
			closestTriangle.verts[0].x = triVert1.pos.x;
			closestTriangle.verts[0].y = triVert1.pos.y;
			closestTriangle.verts[0].z = triVert1.pos.z;
			closestTriangle.verts[1].x = triVert2.pos.x;
			closestTriangle.verts[1].y = triVert2.pos.y;
			closestTriangle.verts[1].z = triVert2.pos.z;
			closestTriangle.verts[2].x = triVert3.pos.x;
			closestTriangle.verts[2].y = triVert3.pos.y;
			closestTriangle.verts[2].z = triVert3.pos.z;

			// TODO: Copy the normal, too	
			// Quick is to average the normal of all 3 vertices
			glm::vec3 triVert1Norm = glm::vec3(triVert1.norm.x, triVert1.norm.y, triVert1.norm.z);
			glm::vec3 triVert2Norm = glm::vec3(triVert2.norm.x, triVert2.norm.y, triVert2.norm.z);
			glm::vec3 triVert3Norm = glm::vec3(triVert3.norm.x, triVert3.norm.y, triVert3.norm.z);

			// Average of the vertex normals... 
			closestTriangle.normal = (triVert1Norm + triVert2Norm + triVert3Norm) / 3.0f;
		}

	}//for (unsigned int triIndex = 0;

	return;
}

// Will return the closest triangles that are within the range "distanceRange".
// This can be used as a "closest triangles to sphere"
void cPhysics::GetClosestTrianglesToSphere(GameObject& testSphere, float distanceRange, Mesh& mesh, std::vector<sPhysicsTriangle>& vecClosestTriangles)
{



}

unsigned expCount = 0;
// Test each object with every other object
void cPhysics::TestForCollisions(std::vector<GameObject*>& vec_pGameObjects)
{
	// This will store all the collisions in this frame

	std::vector<sCollisionInfo> vecCollisions;

	for (unsigned int outerLoopIndex = 0;
		 outerLoopIndex != vec_pGameObjects.size(); outerLoopIndex++)
	{
		GameObject* pA = vec_pGameObjects[outerLoopIndex];
		pA->previousPosition = pA->position;
		for (unsigned int innerLoopIndex = 0;
			 innerLoopIndex != vec_pGameObjects.size(); innerLoopIndex++)
		{
			sCollisionInfo collisionInfo;
			GameObject* pB = vec_pGameObjects[innerLoopIndex];



			// Note that if you don't respond to the 
			// collision here, then you will get the same
			// result twice (Object "A" with "B" and later, 
			//   object "B" with "A" - but it's the same collison

			// Compare the two objects:
			// Either a sphere-sphere or sphere-mesh
			// An I testing the object with itself? 
			//if (pA == pB)
			if (pA->getUniqueID() == pB->getUniqueID())
			{
				// It's the same object
				// Do nothing
			}
			else if (pA->physicsShapeType == SPHERE && pB->physicsShapeType == SPHERE)
			{
				if (DoSphereSphereCollisionTest(pA, pB, collisionInfo))
				{
					vecCollisions.push_back(collisionInfo);
				}
			}
			else if (pA->physicsShapeType == SPHERE && pB->physicsShapeType == MESH)
			{
				if (DoShphereMeshCollisionTest(pA, pB, collisionInfo))
				{
					vecCollisions.push_back(collisionInfo);
				}
			}


		}//for (unsigned int innerLoopIndex = 0;

		//if (!vecCollisions.empty())
		//	mapCollisions[vec_pGameObjects[outerLoopIndex]->friendlyName] = vecCollisions;

	}//for (unsigned int outerLoopIndex = 0;

	for (size_t index = 0; index < vecCollisions.size(); index++)
	{
	}
	for (size_t index = 0; index < vecCollisions.size(); index++)
	{
		vecCollisions[index].pObject1->previousPosition = vecCollisions[index].pObject1->previousPosition + vecCollisions[index].adjustmentVector;
		for (size_t idx = 0; idx < vecCollisions.size(); idx++)
		{
			if (vecCollisions[index].pObject1 == vecCollisions[idx].pObject2)
			{
				vecCollisions[idx].pObject2 = NULL;
			}
		}
		if (vecCollisions[index].pObject2 != NULL)
		{
			if (vecCollisions[index].pObject1->physicsShapeType == SPHERE && vecCollisions[index].pObject2->physicsShapeType == SPHERE)
			{
				sphereCollisionResponse(vecCollisions[index]);
			}
			if (vecCollisions[index].pObject1->physicsShapeType == SPHERE && vecCollisions[index].pObject2->physicsShapeType == MESH)
			{
				sphereMeshCollisionResponse(vecCollisions[index]);
			}

			{
				GameObject* explosion = new GameObject();
				explosion->friendlyName = "explosion" + std::to_string(expCount);
				explosion->meshName = "sphere";
				explosion->position = vecCollisions[index].closestPoint;
				explosion->velocity = glm::vec3(0.0f);
				explosion->scale = glm::vec3(40.0f);
				explosion->physicsShapeType = UNKNOWN;
				explosion->objectColour = glm::vec4(0.9f, 0.1f, 0.1f, 1.0f);
				explosion->specularColour = glm::vec4(1.0f, 1.0f, 0.7f, 0.001f);
				explosion->inverseMass = 1.0f;
				explosion->isWireframe = 0;
				explosion->isVisible = 1;
				explosion->disableDepthBufferTest = 0;
				explosion->disableDepthBufferWrite = 0;
				vec_pGameObjects.push_back(explosion);
				expCount++;
			}
		}
	}


}



glm::vec3 projectUonV(const glm::vec3& u, const glm::vec3& v)
{
	glm::vec3 r;
	r = v * (glm::dot(u, v) / glm::dot(v, v));
	return r;
}

bool cPhysics::DoSphereSphereCollisionTest(GameObject* pA, GameObject* pB,
										   sCollisionInfo& collisionInfo)
{
	// TODO: 
	// Run the sphere-sphere collision test
	// If collided, load the collisionInfo struct and return true
	// else return false;
	float seperation = glm::distance(pA->position, pB->position);
	float combineRadius = pA->SPHERE_radius + pB->SPHERE_radius;
	if (seperation <= combineRadius)
	{
		collisionInfo.pObject1 = pA;
		collisionInfo.pObject2 = pB;

		glm::vec3 midline = pA->position - pB->position;

		collisionInfo.closestPoint = pA->position + (midline * 0.5f);
		collisionInfo.penetrationDistance = (combineRadius - seperation);
		collisionInfo.directionOfApproach = glm::normalize(pA->velocity);
		collisionInfo.adjustmentVector = (-collisionInfo.directionOfApproach) * collisionInfo.penetrationDistance;
		collisionInfo.reflectionNormal = glm::normalize(midline);

		return true;
	}
	return false;
}


bool cPhysics::DoShphereMeshCollisionTest(GameObject* pA, GameObject* pB,
										  sCollisionInfo& collisionInfo)
{
	//break if their is no possiblily of hitting
	//rigged "broad phase"
	if (pA->position.z > 1000 ||
		pA->position.z < -8000 ||
		pA->position.x >  3000 ||
		pA->position.x < -3000 ||
		pA->position.y >  3000 ||
		pA->position.y < -3000)
		return false;



	// TODO: Do the sphere-Mesh collision test
	// If collided, load the collisionInfo struct and return true
	//  else return false
	Point closestPoint = glm::vec3(0.0f, 0.0f, 0.0f);
	sPhysicsTriangle closestTriangle;

	Mesh transformedMesh;
	CalculateTransformedMesh(mMeshes[pB->meshName], pB->matWorld, transformedMesh);

	GetClosestTriangleToPoint(pA->position, transformedMesh, closestPoint, closestTriangle);



	float distance = glm::length(pA->position - closestPoint);
	if (distance <= pA->SPHERE_radius)
	{

		collisionInfo.pObject1 = pA;
		collisionInfo.pObject2 = pB;

		collisionInfo.closestPoint = closestPoint;
		glm::vec3 vecSphereToClosestPoint = closestPoint - pA->position;
		float centreToContractDistance = glm::length(vecSphereToClosestPoint);
		collisionInfo.penetrationDistance = (pA->SPHERE_radius - centreToContractDistance);
		collisionInfo.directionOfApproach = glm::normalize(pA->velocity);
		collisionInfo.adjustmentVector = glm::normalize(closestTriangle.normal) * collisionInfo.penetrationDistance;

		collisionInfo.reflectionNormal = closestTriangle.normal;
		//glm::vec3 velocityVector = glm::normalize(pA->velocity);

		// closestTriangle.normal
		//glm::vec3 reflectionVec = glm::reflect(velocityVector, glm::normalize(closestTriangle.normal));
		//reflectionVec = glm::normalize(reflectionVec);

		// Get lenght of the velocity vector



		//float speed = glm::length(pA->velocity);

		//collisionInfo.bounceVelocity = glm::vec3(reflectionVec.x, reflectionVec.y * 0.3, reflectionVec.z) * speed;


		return true;
	}
	return false;
}


// Takes a mesh in "model space" and converts it into "world space"
void cPhysics::CalculateTransformedMesh(Mesh& originalMesh, glm::mat4 matWorld,
										Mesh& mesh_transformedInWorld)
{
	// Make a copy of the mesh...

	mesh_transformedInWorld = originalMesh;

	// Using the same thing that happens in the shader, 
	// we transform the vertices of the mesh by the world matrix

	// From the vertex shader:
	// fVertWorldLocation = matModel * vec4(vertPosition.xyz, 1.0);


	for (std::vector<VertexPosNormTex>::iterator itVert = mesh_transformedInWorld.vecVertices.begin();
		 itVert != mesh_transformedInWorld.vecVertices.end(); itVert++)
	{
		glm::vec4 vertex = glm::vec4(itVert->pos.x, itVert->pos.y, itVert->pos.z, 1.0f);


		// boom goes the dynamite
		// https://www.youtube.com/watch?v=W45DRy7M1no
		glm::vec4 vertexWorldTransformed = matWorld * vertex;

		// Update 
		itVert->pos.x = vertexWorldTransformed.x;
		itVert->pos.y = vertexWorldTransformed.y;
		itVert->pos.z = vertexWorldTransformed.z;


		// CALCAULTE THE NORMALS for the this mesh, too (for the response)
		// for the normal, do the inverse transpose of the world matrix
		glm::mat4 matWorld_Inv_Transp = glm::inverse(glm::transpose(matWorld));


		glm::vec4 normal = glm::vec4(itVert->norm.x, itVert->norm.y, itVert->norm.z, 1.0f);

		// boom goes the dynamite
		// https://www.youtube.com/watch?v=W45DRy7M1no
		glm::vec4 normalWorldTransformed = matWorld_Inv_Transp * normal;


		//normal = glm::normalize(normal);
		// Update 
		itVert->norm.x = normalWorldTransformed.x;
		itVert->norm.y = normalWorldTransformed.y;
		itVert->norm.z = normalWorldTransformed.z;
	}

	return;
}

void cPhysics::ProcessCollisions(void)
{
	//if (!mapCollisions.empty())
	//{
	//	glm::vec3 adjustment;
	//	glm::vec3 velocity;
	//	for (std::map<std::string, std::vector<sCollisionInfo>>::iterator mapit = mapCollisions.begin(); mapit != mapCollisions.end(); mapit++)
	//	{
	//		adjustment = glm::vec3(0.0f);
	//		velocity = glm::vec3(0.0f);

	//		for (std::vector<sCollisionInfo>::iterator vecit = mapit->second.begin(); vecit != mapit->second.end(); vecit++)
	//		{
	//			adjustment += vecit->adjustmentVector;
	//			//velocity += vecit->bounceVelocity;
	//		}
	//		adjustment /= mapit->second.size();
	//		velocity /= mapit->second.size();

	//		pFindObjectByFriendlyName(mapit->first)->position += adjustment;

	//		pFindObjectByFriendlyName(mapit->first)->velocity = velocity;
	//	}
	//	mapCollisions.clear();
	//}

}


//will make explosion no damage
void cPhysics::sphereCollisionResponse(sCollisionInfo& collisionInfo)
{
	GameObject* a = collisionInfo.pObject1;
	GameObject* b = collisionInfo.pObject2;

	a->velocity = glm::vec3(0.0f);
	b->velocity = glm::vec3(0.0f);

	a->position = glm::vec3(25000, 25000, 25000);
	b->position = glm::vec3(25000, 25000, 25000);
	//glm::vec3 U1x, U1y, U2x, U2y, V1x, V1y, V2x, V2y;

	//float m1, m2, x1, x2;
	//glm::vec3 v1temp, v1, v2, v1x, v2x, v1y, v2y, x(a->position - b->position);

	//glm::normalize(x);
	//v1 = a->velocity;
	//x1 = dot(x, v1);
	//v1x = x * x1;
	//v1y = v1 - v1x;
	//m1 = 1.0f; //mass of 1

	//x = x * -1.0f;
	//v2 = b->velocity;
	//x2 = dot(x, v2);
	//v2x = x * x2;
	//v2y = v2 - v2x;
	//m2 = 1.0f; //mass of 1

	////set the position of the spheres to their previous non contact positions to unstick them.
	//a->position = a->previousPosition;
	//b->position = b->previousPosition;
	//a->velocity = glm::vec3(v1x * (m1 - m2) / (m1 + m2) + v2x * (2 * m2) / (m1 + m2) + v1y) / 4.0f;
	//b->velocity = glm::vec3(v1x * (2 * m1) / (m1 + m2) + v2x * (m2 - m1) / (m1 + m2) + v2y) / 4.0f;
}

//will make explosion and damage
void cPhysics::sphereMeshCollisionResponse(sCollisionInfo& collisionInfo)
{
	GameObject* a = collisionInfo.pObject1;
	GameObject* b = collisionInfo.pObject2;
	a->friendlyName = "damage";
	a->velocity = glm::vec3(0.0f);
	a->physicsShapeType = UNKNOWN;
	a->position = collisionInfo.closestPoint;
	a->meshName = "sphere";
	a->scale = glm::vec3(40);
	a->objectColour = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
	a->specularColour = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);


	//glm::vec3 velocityVector = glm::normalize(a->velocity);

	////closestTriangle.normal
	//glm::vec3 reflectionVec = glm::reflect(velocityVector, glm::normalize(collisionInfo.reflectionNormal));
	//reflectionVec = glm::normalize(reflectionVec);

	//// Get lenght of the velocity vector



	//float speed = glm::length(a->velocity);
	//a->position = a->previousPosition;
	//a->velocity = glm::vec3(reflectionVec.x, reflectionVec.y, reflectionVec.z) * speed;

}