#include "SubdivideWorld.h"

#include <iostream>

float WorldRegion::s_HalfLength = 0.0f;
std::map<unsigned long long, WorldRegion*> WorldRegion::mapRegions;
std::vector<UnraveiledTriangle*> WorldRegion::AllTriangles;


unsigned long long WorldRegion::GenerateID(glm::vec3 point)
{
	float x = point.x + (s_HalfLength * 2.0f) * 100000;
	x = ((x + s_HalfLength) / (s_HalfLength * 2.0f));
	unsigned long long xId = x;


	float y = point.y + (s_HalfLength * 2.0f) * 100000;
	y = ((y + s_HalfLength) / (s_HalfLength * 2.0f));
	unsigned long long yId = y;


	float z = point.z + (s_HalfLength * 2.0f) * 100000;
	z = ((z + s_HalfLength) / (s_HalfLength * 2.0f));
	unsigned long long zId = z;


	xId *= 1000000ull * 1000000ull;
	yId *= 1000000ull;
	zId *= 1;

	unsigned long long Id = xId + yId + zId;

	return Id;

}

#include <fstream>

void WorldRegion::Output(std::string regionFile)
{
	std::fstream file;

	file.open(regionFile, std::fstream::out);
	for (static std::map<unsigned long long, WorldRegion*>::iterator i = mapRegions.begin(); i != mapRegions.end(); i++)
	{
		for (std::set<size_t>::iterator is = i->second->vecTriangles.begin(); is != i->second->vecTriangles.end(); is++)
		{
			file << i->first << " " << *is << std::endl;
		}
	}
	//file << fflush;
	file.close();

	// Uncomment if you want to just generate file
	//exit(0);
}

bool WorldRegion::IsPointInRegion(glm::vec3 point)
{
	if (abs(point.x - center.x) > s_HalfLength)  return false;
	if (abs(point.y - center.y) > s_HalfLength)  return false;
	if (abs(point.z - center.z) > s_HalfLength)  return false;
	return true;
}


void WorldRegion::DivideTrianglesIntoRegions(size_t const& idx,
											 glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c,
											 float const& maxTriangleSideLength)
{
	if (glm::distance(a, b) > maxTriangleSideLength
		|| glm::distance(b, c) > maxTriangleSideLength
		|| glm::distance(c, a) > maxTriangleSideLength)
	{
		glm::vec3 ab, bc, ca;
		ab = ((b - a) / 2.0f) + a; // point half way between a and b
		bc = ((c - b) / 2.0f) + b; // point half way between a and b
		ca = ((a - c) / 2.0f) + c; // point half way between a and b

		DivideTrianglesIntoRegions(idx, a, ab, ca, maxTriangleSideLength);
		DivideTrianglesIntoRegions(idx, ab, b, bc, maxTriangleSideLength);
		DivideTrianglesIntoRegions(idx, ca, bc, c, maxTriangleSideLength);
		DivideTrianglesIntoRegions(idx, ca, ab, bc, maxTriangleSideLength);

	}
	else
	{
		//triangles->push_back(tri);
		mapRegions[GenerateID(a)]->vecTriangles.insert(idx);
		mapRegions[GenerateID(b)]->vecTriangles.insert(idx);
		mapRegions[GenerateID(c)]->vecTriangles.insert(idx);
	}

}

void WorldRegion::GenerateRegions()
{
	float length = 2 * s_HalfLength;

	for (long long x = -50; x <= 50; x++)
	{
		for (long long y = -50; y <= 50; y++)
		{
			for (long long z = -50; z <= 50; z++)
			{
				glm::vec3 loc = glm::vec3(x * length, y * length, z * length);
				mapRegions[WorldRegion::GenerateID(loc)] = new WorldRegion(loc);
			}
		}
	}

}

void WorldRegion::init(std::string meshName, cMesh* mesh, float halfLength)
{
	if (halfLength == 0.0f) {}
	else if (s_HalfLength == 0.0f)
		s_HalfLength = halfLength;
	else
		std::cout << "Cannot change half length." << std::endl;

	if (mapRegions.size() == 0)
		GenerateRegions();

	for (size_t i = 0; i < mesh->vecTriangles.size(); i++)
	{

		glm::vec3 a = glm::vec3(mesh->vecVertices[mesh->vecTriangles[i].vert_index_1].x,
								mesh->vecVertices[mesh->vecTriangles[i].vert_index_1].y,
								mesh->vecVertices[mesh->vecTriangles[i].vert_index_1].z);

		glm::vec3 b = glm::vec3(mesh->vecVertices[mesh->vecTriangles[i].vert_index_2].x,
								mesh->vecVertices[mesh->vecTriangles[i].vert_index_2].y,
								mesh->vecVertices[mesh->vecTriangles[i].vert_index_2].z);

		glm::vec3 c = glm::vec3(mesh->vecVertices[mesh->vecTriangles[i].vert_index_3].x,
								mesh->vecVertices[mesh->vecTriangles[i].vert_index_3].y,
								mesh->vecVertices[mesh->vecTriangles[i].vert_index_3].z);


		glm::vec3 an = glm::vec3(mesh->vecVertices[mesh->vecTriangles[i].vert_index_1].nx,
								 mesh->vecVertices[mesh->vecTriangles[i].vert_index_1].ny,
								 mesh->vecVertices[mesh->vecTriangles[i].vert_index_1].nz);

		glm::vec3 bn = glm::vec3(mesh->vecVertices[mesh->vecTriangles[i].vert_index_2].nx,
								 mesh->vecVertices[mesh->vecTriangles[i].vert_index_2].ny,
								 mesh->vecVertices[mesh->vecTriangles[i].vert_index_2].nz);

		glm::vec3 cn = glm::vec3(mesh->vecVertices[mesh->vecTriangles[i].vert_index_3].nx,
								 mesh->vecVertices[mesh->vecTriangles[i].vert_index_3].ny,
								 mesh->vecVertices[mesh->vecTriangles[i].vert_index_3].nz);

		AllTriangles.push_back(new UnraveiledTriangle(a, b, c, an, bn, cn));
	}

	std::string regionFile = "assets/regions_" + meshName + ".txt";

	std::ifstream f(regionFile);
	 
	if (f.good())
	{
		printf("Reading in triangles.\n");
		unsigned long long Id = 0;
		size_t triIdx = 0;
		while (!f.eof())
		{
			f >> Id;
			f >> triIdx;

			mapRegions[Id]->vecTriangles.insert(triIdx);
		}
		f.close();
	}
	else
	{
		f.close();
		for (size_t i = 0; i < mesh->vecTriangles.size(); i++)
		{
			DivideTrianglesIntoRegions(i, AllTriangles[i]->a, AllTriangles[i]->b, AllTriangles[i]->c, 1.0f);
		}

		Output(regionFile);
	}
	return;
}