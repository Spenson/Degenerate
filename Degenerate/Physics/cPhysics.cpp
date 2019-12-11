#include "cPhysics.h"
#include "SubdivideWorld.h"

cPhysics::cPhysics()
{
	// This is a typical Earth gravity value. 
	// note that this doesn't mean that the simulation will "look good", though... 
//	this->m_Gravity = glm::vec3(0.0f, -9.81f, 0.0f);
	this->m_Gravity = glm::vec3(0.0f, -1.0f, 0.0f);
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

glm::vec3 cPhysics::RK6(glm::vec3 val, glm::vec3 change, float delta)
{
	glm::vec3 step = change / 6.0f;

	glm::vec3 inc1 = val + ((step * 1.0f)* delta);
	glm::vec3 inc2 = val + ((step * 2.0f)* delta);
	glm::vec3 inc3 = val + ((step * 3.0f)* delta);
	glm::vec3 inc4 = val + ((step * 4.0f)* delta);
	glm::vec3 inc5 = val + ((step * 5.0f)* delta);
	glm::vec3 inc6 = val + ((step * 6.0f)* delta);

	return (((1.0f * inc1) + (2.0f * inc2) + (3.0f * inc3) +
		(3.0f * inc4) + (2.0f * inc5) + (1.0f * inc6)
			 ) / 12.0f);
}


void cPhysics::IntegrationStep(std::vector<cGameObject*>& vec_pGameObjects, float deltaTime)
{


	for (unsigned int index = 0;
		 index != vec_pGameObjects.size(); index++)
	{
		// Get a pointer to the current m_pGO (makes the code a little clearer)
		cGameObject* pCurObj = vec_pGameObjects[index];

		if (pCurObj->inverseMass != 0.0f)
		{

			// Forward Explicit Euler Inetegration
			//NewVelocty += Velocity + ( Ax * DeltaTime )

			// These should be different 
			// pCurObj->accel = this->m_Gravity;

			//pCurObj->velocity.x += pCurObj->accel.x * deltaTime;
			//pCurObj->velocity.y += pCurObj->accel.y * deltaTime;
			//pCurObj->velocity.z += pCurObj->accel.z * deltaTime;
			//pCurObj->velocity += pCurObj->accel * deltaTime;
			//		// Or you can do this...
			//		CurObj.velocity += CurObj.accel * deltaTime;
					//NewPosition = Posistion + ( Vx * DeltaTime )
			//glm::quat rotate = pCurObj->getQAngularVelocity();
			//rotate.w *= deltaTime;

						// THIS SHOULD NOT BE BECAUSE YA... VELOCITY IS NOT RELETIVE
			//pCurObj->MoveInRelativeDirection(pCurObj->velocity * deltaTime);
			//pCurObj->positionXYZ += pCurObj->velocity * deltaTime;
			//pCurObj->positionXYZ.x += pCurObj->velocity.x * deltaTime;
			//pCurObj->positionXYZ.y += pCurObj->velocity.y * deltaTime;
			//pCurObj->positionXYZ.z += pCurObj->velocity.z * deltaTime;


			/*rk4
			// Velocity Adjust
			glm::vec3 change = pCurObj->accel / 4.0f;

			glm::vec3 inc1 = pCurObj->accel + (change * 0.0f);
			glm::vec3 inc2 = pCurObj->accel + (change * 1.0f);
			glm::vec3 inc3 = pCurObj->accel + (change * 2.0f);
			glm::vec3 inc4 = pCurObj->accel + (change * 3.0f);

			pCurObj->velocity += ((1.0f * inc1) +
								  (2.0f * inc2) +
								  (2.0f * inc3) +
								  (1.0f * inc4) ) / 6.0f;


			// Position Adjust
			change = pCurObj->velocity / 4.0f;

			inc1 = pCurObj->velocity + (change * 0.0f);
			inc2 = pCurObj->velocity + (change * 1.0f);
			inc3 = pCurObj->velocity + (change * 2.0f);
			inc4 = pCurObj->velocity + (change * 3.0f);

			pCurObj->positionXYZ += ((1.0f * inc1) +
									 (2.0f * inc2) +
									 (2.0f * inc3) +
									 (1.0f * inc4) ) / 6.0f;

			//*/


			///*rk6
			//Gravity

			//glm::vec3 change = this->m_Gravity / 6.0f;

			//glm::vec3 inc1 = this->m_Gravity + (change * 0.0f);
			//glm::vec3 inc2 = this->m_Gravity + (change * 1.0f);
			//glm::vec3 inc3 = this->m_Gravity + (change * 2.0f);
			//glm::vec3 inc4 = this->m_Gravity + (change * 3.0f);
			//glm::vec3 inc5 = this->m_Gravity + (change * 4.0f);
			//glm::vec3 inc6 = this->m_Gravity + (change * 5.0f);

			//pCurObj->velocity += (((1.0f * inc1) + (2.0f * inc2) + (3.0f * inc3) +
			//	(3.0f * inc4) + (2.0f * inc5) + (1.0f * inc6)
			//					   ) / 12.0f) * deltaTime;
			//pCurObj->velocity = RK6(pCurObj->velocity, this->m_Gravity, deltaTime);


			// Velocity Adjust
			//change = pCurObj->accel / 6.0f;

			//inc1 = pCurObj->accel + (change * 0.0f);
			//inc2 = pCurObj->accel + (change * 1.0f);
			//inc3 = pCurObj->accel + (change * 2.0f);
			//inc4 = pCurObj->accel + (change * 3.0f);
			//inc5 = pCurObj->accel + (change * 4.0f);
			//inc6 = pCurObj->accel + (change * 5.0f);

			//pCurObj->velocity += (((1.0f * inc1) + (2.0f * inc2) + (3.0f * inc3) +
			//	(3.0f * inc4) + (2.0f * inc5) + (1.0f * inc6))
			//					  / 12.0f) * deltaTime;
			//pCurObj->velocity += RK6(pCurObj->accel) * deltaTime;
			pCurObj->velocity += (this->m_Gravity + pCurObj->accel) * deltaTime;

			// Position Adjust
			//change = pCurObj->velocity / 6.0f;

			//inc1 = pCurObj->velocity + (change * 0.0f);
			//inc2 = pCurObj->velocity + (change * 1.0f);
			//inc3 = pCurObj->velocity + (change * 2.0f);
			//inc4 = pCurObj->velocity + (change * 3.0f);
			//inc5 = pCurObj->velocity + (change * 4.0f);
			//inc6 = pCurObj->velocity + (change * 5.0f);

			//pCurObj->positionXYZ += (((1.0f * inc1) + (2.0f * inc2) + (3.0f * inc3) +
			//	(3.0f * inc4) + (2.0f * inc5) + (1.0f * inc6))
			//						 / 12.0f) * deltaTime;

			//pCurObj->positionXYZ += RK6(pCurObj->velocity) * deltaTime;
			pCurObj->positionXYZ += pCurObj->velocity * deltaTime;
			//*/


			// *DONE* CHANGE THIS MESS
			// Add Angular Accel??? 
			if (pCurObj->getQAngularVelocity() != glm::quat(glm::vec3(0.0f)))
			{
				glm::quat rotate = glm::slerp(pCurObj->getQOrientation(), pCurObj->getQOrientation() * pCurObj->getQAngularVelocity(), deltaTime);
				pCurObj->setOrientation(rotate);
			}


		}
	}//for (unsigned int index = 0;

	return;
}



// Returns all the triangles and the closest points
void cPhysics::GetClosestTriangleToPoint(Point pointXYZ, cMesh& mesh, glm::vec3& closestPoint, sPhysicsTriangle& closestTriangle)
{

	// Assume the closest distance is REALLY far away
	float closestDistanceSoFar = FLT_MAX;


	for (unsigned int triIndex = 0;
		 triIndex != mesh.vecTriangles.size();
		 triIndex++)
	{
		sPlyTriangle& curTriangle = mesh.vecTriangles[triIndex];

		// Get the vertices of the triangle
		sPlyVertexXYZ_N_UV triVert1 = mesh.vecVertices[curTriangle.vert_index_1];
		sPlyVertexXYZ_N_UV triVert2 = mesh.vecVertices[curTriangle.vert_index_2];
		sPlyVertexXYZ_N_UV triVert3 = mesh.vecVertices[curTriangle.vert_index_3];

		Point triVertPoint1;
		triVertPoint1.x = triVert1.x;
		triVertPoint1.y = triVert1.y;
		triVertPoint1.z = triVert1.z;

		Point triVertPoint2;
		triVertPoint2.x = triVert2.x;
		triVertPoint2.y = triVert2.y;
		triVertPoint2.z = triVert2.z;

		Point triVertPoint3;
		triVertPoint3.x = triVert3.x;
		triVertPoint3.y = triVert3.y;
		triVertPoint3.z = triVert3.z;

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
			closestTriangle.verts[0].x = triVert1.x;
			closestTriangle.verts[0].y = triVert1.y;
			closestTriangle.verts[0].z = triVert1.z;
			closestTriangle.verts[1].x = triVert2.x;
			closestTriangle.verts[1].y = triVert2.y;
			closestTriangle.verts[1].z = triVert2.z;
			closestTriangle.verts[2].x = triVert3.x;
			closestTriangle.verts[2].y = triVert3.y;
			closestTriangle.verts[2].z = triVert3.z;

			// TODO: Copy the normal, too	
			// Quick is to average the normal of all 3 vertices
			glm::vec3 triVert1Norm = glm::vec3(triVert1.nx, triVert1.ny, triVert1.nz);
			glm::vec3 triVert2Norm = glm::vec3(triVert2.nx, triVert2.ny, triVert2.nz);
			glm::vec3 triVert3Norm = glm::vec3(triVert3.nx, triVert3.ny, triVert3.nz);

			// Average of the vertex normals... 
			closestTriangle.normal = (triVert1Norm + triVert2Norm + triVert3Norm) / 3.0f;

		}

	}//for (unsigned int triIndex = 0;

	return;
}


// *********************************************************************************
// FOR THE PATTERNS AND FRAMEWORKS MID-TERM
// 
// This is like the method above, but doesn't test for the y axis, which gives you the 
// TRIANGLE (not the testPoint) that that testPoint is over (or under). 
// 
void cPhysics::GetClosestTriangleToPoint_FRAMEWORKS_AND_PATTERNS(Point pointXYZ, cMesh& mesh, sPhysicsTriangle& closestTriangle)
{
	// Assume the closest distance is REALLY far away
	float closestDistanceSoFar = FLT_MAX;


	for (unsigned int triIndex = 0;
		 triIndex != mesh.vecTriangles.size();
		 triIndex++)
	{
		sPlyTriangle& curTriangle = mesh.vecTriangles[triIndex];

		// Get the vertices of the triangle
		sPlyVertexXYZ_N_UV triVert1 = mesh.vecVertices[curTriangle.vert_index_1];
		sPlyVertexXYZ_N_UV triVert2 = mesh.vecVertices[curTriangle.vert_index_2];
		sPlyVertexXYZ_N_UV triVert3 = mesh.vecVertices[curTriangle.vert_index_3];

		Point triVertPoint1;
		triVertPoint1.x = triVert1.x;
		triVertPoint1.y = triVert1.y;
		triVertPoint1.z = triVert1.z;

		Point triVertPoint2;
		triVertPoint2.x = triVert2.x;
		triVertPoint2.y = triVert2.y;
		triVertPoint2.z = triVert2.z;

		Point triVertPoint3;
		triVertPoint3.x = triVert3.x;
		triVertPoint3.y = triVert3.y;
		triVertPoint3.z = triVert3.z;


		// Now clear the y values for the actual test
		glm::vec3 triVertPoint1_y_is_zero = triVertPoint1;
		glm::vec3 triVertPoint2_y_is_zero = triVertPoint2;
		glm::vec3 triVertPoint3_y_is_zero = triVertPoint3;
		glm::vec3 testPoint_y_is_zero = pointXYZ;


		triVertPoint1_y_is_zero.y = 0.0f;
		triVertPoint2_y_is_zero.y = 0.0f;
		triVertPoint3_y_is_zero.y = 0.0f;
		testPoint_y_is_zero.y = 0.0f;

		glm::vec3 curClosetPoint = ClosestPtPointTriangle(testPoint_y_is_zero,
														  triVertPoint1_y_is_zero, triVertPoint2_y_is_zero, triVertPoint3_y_is_zero);

		// Is this the closest so far?
		float distanceNow = glm::distance(curClosetPoint, pointXYZ);

		// is this closer than the closest distance
		if (distanceNow <= closestDistanceSoFar)
		{
			closestDistanceSoFar = distanceNow;

			// Copy the triangle information...
			closestTriangle.verts[0].x = triVert1.x;
			closestTriangle.verts[0].y = triVert1.y;
			closestTriangle.verts[0].z = triVert1.z;
			closestTriangle.verts[1].x = triVert2.x;
			closestTriangle.verts[1].y = triVert2.y;
			closestTriangle.verts[1].z = triVert2.z;
			closestTriangle.verts[2].x = triVert3.x;
			closestTriangle.verts[2].y = triVert3.y;
			closestTriangle.verts[2].z = triVert3.z;
		}

	}//for (unsigned int triIndex = 0;

	return;



}
// *********************************************************************************



// Will return the closest triangles that are within the range "distanceRange".
// This can be used as a "closest triangles to sphere"
void cPhysics::GetClosestTrianglesToSphere(cGameObject& testSphere, float distanceRange, cMesh& mesh, std::vector<sPhysicsTriangle>& vecClosestTriangles)
{



}


#include "../globals.h"

// Test each m_pGO with every other m_pGO
void cPhysics::TestForCollisions(std::vector<cGameObject*>& vec_pGameObjects, std::vector<glm::vec3>& todraw)
{
	// This will store all the collisions in this frame
	std::vector<sCollisionInfo> vecCollisions;

	sCollisionInfo collisionInfo;

	for (unsigned int outerLoopIndex = 0;
		 outerLoopIndex != vec_pGameObjects.size(); outerLoopIndex++)
	{
		cGameObject* m_pGO = vec_pGameObjects[outerLoopIndex];
		if (m_pGO->physicsShapeType == POINTSET)
		{
			glm::mat4 objMat = calculateWorldMatrix(m_pGO, glm::mat4(1.0));
			for (size_t pointIdx = 0; pointIdx < m_pGO->vecPhysTestPoints.size(); pointIdx++)
			{
				glm::vec3 testPoint = m_pGO->vecPhysTestPoints[pointIdx];
				testPoint = objMat * glm::vec4(testPoint, 1.0f);

				if (WorldRegion::mapRegions.find(WorldRegion::GenerateID(testPoint)) != WorldRegion::mapRegions.end())
				{
					WorldRegion* wr = WorldRegion::mapRegions[WorldRegion::GenerateID(testPoint)];
					for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)
					{
						UnraveiledTriangle* tri = WorldRegion::AllTriangles[*i];
						glm::vec3 collisionPoint = glm::vec3(0.0f);
						float barA = 0, barB = 0, barC = 0;
						if (IntersectLineTriangle(m_pGO->positionXYZ, testPoint, tri->a, tri->b, tri->c,
												  barA, barB, barC, collisionPoint))
						{
							m_pGO->m_pDebugRenderer->addLine(testPoint, m_pGO->positionXYZ, glm::vec3(1.0f, 0.0f, 0.0f));
							m_pGO->m_pDebugRenderer->addLine(m_pGO->positionXYZ, collisionPoint, glm::vec3(0.0f, 1.0f, 0.0f));
							m_pGO->m_pDebugRenderer->addLine(testPoint, collisionPoint, glm::vec3(0.0f, 0.0f, 1.0f));
							if (glm::length(collisionPoint - testPoint) != 0)
								m_pGO->velocity = (glm::length(m_pGO->velocity) * 0.5f) * glm::normalize(collisionPoint - testPoint);
							//m_pGO->velocity *= glm::normalize(collisionPoint - testPoint);
						//m_pGO->velocity *= 0.9f;
							todraw.push_back(collisionPoint);
							todraw.push_back(testPoint);
							m_pGO->positionXYZ += (collisionPoint - testPoint);
						}
					}

					//WorldRegion* wr = WorldRegion::mapRegions[WorldRegion::GenerateID(testPoint)];
					//glm::vec3 closestPoint = glm::vec3(FLT_MAX);
					//size_t closestIdx = 0;
					//for (std::set<size_t>::iterator i = wr->vecTriangles.begin(); i != wr->vecTriangles.end(); i++)
					//{
					//	glm::vec3 curClosestPoint = ClosestPtPointTriangle(testPoint,
					//													   WorldRegion::AllTriangles[*i]->a,
					//													   WorldRegion::AllTriangles[*i]->b,
					//													   WorldRegion::AllTriangles[*i]->c);
					//	if (glm::distance(testPoint, curClosestPoint) < glm::distance(testPoint, closestPoint))
					//	{
					//		closestPoint = curClosestPoint;
					//		closestIdx = *i;
					//	}

					//}

					////if(glm::distance(testPoint, closestPoint) > 2.0f)
					////	continue;

					//todraw.push_back(closestPoint);

					//glm::vec3 trinorm = glm::normalize(WorldRegion::AllTriangles[closestIdx]->an *
					//								   WorldRegion::AllTriangles[closestIdx]->bn *
					//								   WorldRegion::AllTriangles[closestIdx]->cn);

					//if (glm::dot((testPoint - closestPoint), trinorm) < 0.0f && glm::dot((testPoint - closestPoint), trinorm) > -1.0f)
					//{
					//	vec_pGameObjects[outerLoopIndex]->positionXYZ += trinorm * glm::distance(testPoint, closestPoint);
					//	//printf("collided = %f\n", glm::dot((testPoint - closestPoint), trinorm));
					//}

				}
			}
			continue;
		}

		//for (unsigned int innerLoopIndex = 0;
		//	 innerLoopIndex != vec_pGameObjects.size(); innerLoopIndex++)
		//{
		//	cGameObject* pA = vec_pGameObjects[outerLoopIndex];
		//	cGameObject* pB = vec_pGameObjects[innerLoopIndex];



		//	// Note that if you don't respond to the 
		//	// collision here, then you will get the same
		//	// result twice (Object "A" with "B" and later, 
		//	//   m_pGO "B" with "A" - but it's the same collison

		//	// Compare the two objects:
		//	// Either a sphere-sphere or sphere-mesh
		//	// An I testing the m_pGO with itself? 
		//	//if (pA == pB)
		//	if (pA->getUniqueID() == pB->getUniqueID())
		//	{
		//		// It's the same m_pGO
		//		// Do nothing
		//	}
		//	else if (pA->physicsShapeType == SPHERE &&
		//			 pB->physicsShapeType == SPHERE)
		//	{
		//		if (DoSphereSphereCollisionTest(pA, pB, collisionInfo))
		//		{
		//			vecCollisions.push_back(collisionInfo);
		//		}
		//	}
		//	else if (pA->physicsShapeType == SPHERE &&
		//			 pB->physicsShapeType == MESH)
		//	{
		//		if (DoShphereMeshCollisionTest(pA, pB, collisionInfo))
		//		{
		//			vecCollisions.push_back(collisionInfo);
		//		}
		//	}


		//}//for (unsigned int innerLoopIndex = 0;
	}//for (unsigned int outerLoopIndex = 0;

}

bool cPhysics::DoSphereSphereCollisionTest(cGameObject* pA, cGameObject* pB,
										   sCollisionInfo& collisionInfo)
{
	// TODO: 
	// Run the sphere-sphere collision test
	// If collided, load the collisionInfo struct and return true
	// else return false;

	return false;
}
bool cPhysics::DoShphereMeshCollisionTest(cGameObject* pA, cGameObject* pB,
										  sCollisionInfo& collisionInfo)
{
	// TODO: Do the sphere-Mesh collision test
	// If collided, load the collisionInfo struct and return true
	//  else return false


	return true;
}

// Takes a mesh in "model space" and converts it into "world space"
void cPhysics::CalculateTransformedMesh(cMesh& originalMesh, glm::mat4 matWorld,
										cMesh& mesh_transformedInWorld)
{
	// Make a copy of the mesh...

	mesh_transformedInWorld = originalMesh;

	// Using the same thing that happens in the shader, 
	// we transform the vertices of the mesh by the world matrix
	// 
	// From the vertex shader:
	// fVertWorldLocation = matModel * vec4(vertPosition.xyz, 1.0);
	//

	for (std::vector<sPlyVertexXYZ_N_UV>::iterator itVert = mesh_transformedInWorld.vecVertices.begin();
		 itVert != mesh_transformedInWorld.vecVertices.end(); itVert++)
	{
		glm::vec4 vertex = glm::vec4(itVert->x, itVert->y, itVert->z, 1.0f);

		// boom goes the dynamite
		// https://www.youtube.com/watch?v=W45DRy7M1no
		glm::vec4 vertexWorldTransformed = matWorld * vertex;

		// Update 
		itVert->x = vertexWorldTransformed.x;
		itVert->y = vertexWorldTransformed.y;
		itVert->z = vertexWorldTransformed.z;


		// CALCAULTE THE NORMALS for the this mesh, too (for the response)
		// for the normal, do the inverse transpose of the world matrix
		glm::mat4 matWorld_Inv_Transp = glm::inverse(glm::transpose(matWorld));


		glm::vec4 normal = glm::vec4(itVert->nx, itVert->ny, itVert->nz, 1.0f);

		// boom goes the dynamite
		// https://www.youtube.com/watch?v=W45DRy7M1no
		glm::vec4 normalWorldTransformed = matWorld_Inv_Transp * normal;


		// Update 
		itVert->nx = normalWorldTransformed.x;
		itVert->ny = normalWorldTransformed.y;
		itVert->nz = normalWorldTransformed.z;
	}

	return;
}
