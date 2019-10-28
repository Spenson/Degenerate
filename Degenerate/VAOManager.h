#pragma once


#include "GLCommon.h"

// Will load the models and place them 
// into the vertex and index buffers to be drawn

#include <string>
#include <map>
#include "Mesh.h"				// File as loaded from the file

// The vertex structure 
//	that's ON THE GPU (eventually) 
// So dictated from THE SHADER
//struct ModelVertex
//{
//	float x, y, z, w;			// w coordinate	
//	float r, g, b, a;	// a = alpha (transparency)
//	float nx, ny, nz, nw;
//	float u0, v0, u1, v1;
//};
struct ModelVertex
{
	glm::vec4 pos;
	glm::vec4 col;
	glm::vec4 norm;
	glm::vec2 tex0;
	glm::vec2 tex1;
};

struct ModelDrawInfo
{
	ModelDrawInfo();

	std::string meshName;

	unsigned int VAO_ID;

	unsigned int VertexBufferID;
	unsigned int VertexBuffer_Start_Index;
	unsigned int numberOfVertices;

	unsigned int IndexBufferID;
	unsigned int IndexBuffer_Start_Index;
	unsigned int numberOfIndices;
	unsigned int numberOfTriangles;

	// The "local" (i.e. "CPU side" temporary array)
	ModelVertex* pVertices;	//  = 0;
	// The index buffer (CPU side)
	unsigned int* pIndices;

	// You could store the max and min values of the 
	//  vertices here (determined when you load them):
	float maxX, maxY, maxZ;
	float minX, minY, minZ;

	//	scale = 5.0/maxExtent;		-> 5x5x5
	float maxExtent;
	float extentX, extentY, extentZ;

	void CalcExtents(void);
};


class VAOManager
{
public:

	// Takes a Mesh object and copies it into the GPU (as a VOA)
	bool LoadModelIntoVAO(std::string fileName,
						  Mesh& theMesh,				// NEW
						  ModelDrawInfo& drawInfo,
						  unsigned int shaderProgramID);

	// We don't want to return an int, likely
	bool FindDrawInfoByModelName(std::string filename,
								 ModelDrawInfo& drawInfo);

	std::string getLastError(bool bAndClear = true);

private:

	std::map< std::string /*model name*/,
		ModelDrawInfo /* info needed to draw*/ >
		m_map_ModelName_to_VAOID;

};