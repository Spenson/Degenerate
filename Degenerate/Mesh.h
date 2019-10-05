#pragma once

#include <vector>		// "smart array"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

// This structure matches the file, so that our life is
//   simpler and happier, and we all get along.
struct VertexWithNormal
{
	float x, y, z;
	float nx, ny, nz;		// NOW with NORMALS!!
};

struct TriangleIndex
{
	unsigned int a;
	unsigned int b;
	unsigned int c;
};

class Mesh
{
public:
	Mesh() {};			// Empty c'tor
	~Mesh() {};		// Empty d'tor
	// Store the vertices
	std::vector<VertexWithNormal> vecVertices;

	// Store the triangles
	std::vector<TriangleIndex> vecTriangles;

};