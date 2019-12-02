#pragma once

#include "../globals.h"
#include <vector>
#include <set>
#include "../ModelStuff/cMesh.h"


struct UnraveiledTriangle
{
	UnraveiledTriangle(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 an, glm::vec3 bn, glm::vec3 cn) : a(a), b(b), c(c), an(an), bn(bn), cn(cn) {}

	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	glm::vec3 an;
	glm::vec3 bn;
	glm::vec3 cn;
};


class WorldRegion
{
	static void GenerateRegions();
	static void DivideTrianglesIntoRegions(size_t const& idx,
										   glm::vec3 const& a, glm::vec3 const& b, glm::vec3 const& c,
										   float const& maxTriangleSideLength = 1.0f);
	static float s_HalfLength;
public:
	static void init(std::string meshName, cMesh* mesh, float halfLength = 0.0f);
	static unsigned long long GenerateID(glm::vec3 point);

	static std::vector<UnraveiledTriangle*> AllTriangles;
	static std::map<unsigned long long, WorldRegion*> mapRegions;

	static void Output(std::string regionFile);

	static float HalfLength() { return s_HalfLength; }

	WorldRegion(glm::vec3 center) : center(center) {}
	glm::vec3 center;
	std::set<size_t> vecTriangles;

	bool IsPointInRegion(glm::vec3 point);
};



