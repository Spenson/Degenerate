#pragma once

#include <vector>		// "smart array"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

// This structure matches the file, so that our life is
//   simpler and happier, and we all get along.
//struct VertexWithNormal
//{
//	float x, y, z;
//	float nx, ny, nz;		// NOW with NORMALS!!
//};
struct VertexPosNormTex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tex1;
	glm::vec2 tex2;
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
	std::vector<VertexPosNormTex> vecVertices;
	// Store the triangles
	std::vector<TriangleIndex> vecTriangles;

};