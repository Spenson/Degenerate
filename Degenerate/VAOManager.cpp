#include "VAOManager.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <vector>

#include <sstream>

ModelDrawInfo::ModelDrawInfo()
{
	this->VAO_ID = 0;

	this->VertexBufferID = 0;
	this->VertexBuffer_Start_Index = 0;
	this->numberOfVertices = 0;

	this->IndexBufferID = 0;
	this->IndexBuffer_Start_Index = 0;
	this->numberOfIndices = 0;
	this->numberOfTriangles = 0;

	// The "local" (i.e. "CPU side" temporary array)
	this->pVertices = 0;	// or NULL
	this->pIndices = 0;		// or NULL

	this->maxX = this->maxY = this->maxZ = 0.0f;
	this->minX = this->minY = this->minZ = 0.0f;
	this->extentX = this->extentY = this->extentZ = this->maxExtent = 0.0f;

	return;
}

void ModelDrawInfo::CalcExtents(void)
{
	// See if we have any vertices loaded...
	if ((this->numberOfVertices == 0) || (this->pVertices == 0))
	{
		return;
	}

	// We're good

	// Assume the 1st vertex is the max and min (so we can compare)
	this->minX = this->maxX = this->pVertices[0].pos.x;
	this->minY = this->maxY = this->pVertices[0].pos.y;
	this->minZ = this->maxZ = this->pVertices[0].pos.z;

	for (unsigned int index = 0; index != this->numberOfVertices; index++)
	{
		if (this->pVertices[index].pos.x < this->minX) { this->minX = this->pVertices[index].pos.x; }
		if (this->pVertices[index].pos.y < this->minY) { this->minY = this->pVertices[index].pos.y; }
		if (this->pVertices[index].pos.z < this->minZ) { this->minZ = this->pVertices[index].pos.z; }

		if (this->pVertices[index].pos.x < this->maxX) { this->maxX = this->pVertices[index].pos.x; }
		if (this->pVertices[index].pos.y < this->maxY) { this->maxY = this->pVertices[index].pos.y; }
		if (this->pVertices[index].pos.z < this->maxZ) { this->maxZ = this->pVertices[index].pos.z; }
	}

	this->extentX = this->maxX - this->minX;
	this->extentY = this->maxY - this->minY;
	this->extentZ = this->maxZ - this->minZ;

	this->maxExtent = this->extentX;
	if (this->extentY > this->maxExtent) { this->maxExtent = this->extentY; }
	if (this->extentZ > this->maxExtent) { this->maxExtent = this->extentZ; }

	return;
}


bool VAOManager::LoadModelIntoVAO(
	std::string fileName,
	Mesh& theMesh,					// NEW
	ModelDrawInfo& drawInfo,
	unsigned int shaderProgramID)

{
	// Write some code to copy the infomation from cMesh& theMesh
	//  to the ModelDrawInfo& drawInfo...

	drawInfo.numberOfVertices = (unsigned int)theMesh.vecVertices.size();
	// Allocate an array big enought
	drawInfo.pVertices = new ModelVertex[drawInfo.numberOfVertices];

	// Copy the data from the vecVertices...
	for (unsigned int index = 0; index != drawInfo.numberOfVertices; index++)
	{

		drawInfo.pVertices[index].pos.x = theMesh.vecVertices[index].pos.x;
		drawInfo.pVertices[index].pos.y = theMesh.vecVertices[index].pos.y;
		drawInfo.pVertices[index].pos.z = theMesh.vecVertices[index].pos.z;
		drawInfo.pVertices[index].pos.w = 1.0f;		// Set to 1 if not sure

		drawInfo.pVertices[index].col.r = 1.0f;
		drawInfo.pVertices[index].col.g = 1.0f;
		drawInfo.pVertices[index].col.b = 1.0f;
		drawInfo.pVertices[index].col.a = 1.0f;		// Again, if not sure, set to 1.0f

		drawInfo.pVertices[index].norm.x = theMesh.vecVertices[index].norm.x;
		drawInfo.pVertices[index].norm.y = theMesh.vecVertices[index].norm.y;
		drawInfo.pVertices[index].norm.z = theMesh.vecVertices[index].norm.z;
		drawInfo.pVertices[index].norm.w = 1.0f;		// if unsure, set to 1.0f

		// These are the "texture coordinates", and we aren't loading them, yet
		drawInfo.pVertices[index].tex0.s = 1.0f;
		drawInfo.pVertices[index].tex0.t = 1.0f;
		drawInfo.pVertices[index].tex1.s = 1.0f;
		drawInfo.pVertices[index].tex1.t = 1.0f;

	}

	// Now copy the index information, too
	drawInfo.numberOfTriangles = (unsigned int)theMesh.vecTriangles.size();
	drawInfo.numberOfIndices = (unsigned int)theMesh.vecTriangles.size() * 3;

	// Allocate the index array
	drawInfo.pIndices = new unsigned int[drawInfo.numberOfIndices];

	unsigned int indexTri = 0;
	unsigned int indexIndex = 0;
	for (; indexTri != drawInfo.numberOfTriangles; indexTri++, indexIndex += 3)
	{
		drawInfo.pIndices[indexIndex + 0] = (unsigned int)theMesh.vecTriangles[indexTri].a;
		drawInfo.pIndices[indexIndex + 1] = (unsigned int)theMesh.vecTriangles[indexTri].b;
		drawInfo.pIndices[indexIndex + 2] = (unsigned int)theMesh.vecTriangles[indexTri].c;
	}


	drawInfo.meshName = fileName;

	// TODO: Load the model from file

	// 
	// Model is loaded and the vertices and indices are in the drawInfo struct
	// 

	// Create a VAO (Vertex Array Object), which will 
	//	keep track of all the 'state' needed to draw 
	//	from this buffer...

	// Ask OpenGL for a new buffer ID...
	glGenVertexArrays(1, &(drawInfo.VAO_ID));
	// "Bind" this buffer:
	// - aka "make this the 'current' VAO buffer
	glBindVertexArray(drawInfo.VAO_ID);

	// Now ANY state that is related to vertex or index buffer
	//	and vertex attribute layout, is stored in the 'state' 
	//	of the VAO... 


	// NOTE: OpenGL error checks have been omitted for brevity
//	glGenBuffers(1, &vertex_buffer);
	glGenBuffers(1, &(drawInfo.VertexBufferID));

	//	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, drawInfo.VertexBufferID);
	// sVert vertices[3]
	glBufferData(GL_ARRAY_BUFFER,
				 sizeof(ModelVertex) * drawInfo.numberOfVertices,	// ::g_NumberOfVertsToDraw,	// sizeof(vertices), 
				 (GLvoid*)drawInfo.pVertices,							// pVertices,			//vertices, 
				 GL_STATIC_DRAW);


	// Copy the index buffer into the video card, too
	// Create an index buffer.
	glGenBuffers(1, &(drawInfo.IndexBufferID));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, drawInfo.IndexBufferID);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,			// Type: Index element array
				 sizeof(unsigned int) * drawInfo.numberOfIndices,
				 (GLvoid*)drawInfo.pIndices,
				 GL_STATIC_DRAW);

	// Set the vertex attributes.

	//struct ModelVertex
	//{
	//	float x, y, z, w;			// w coordinate	
	//	float r, g, b, a;		// a = alpha (transparency)
	//	float nx, ny, nz, nw;
	//	float u0, v0, u1, v1;
	//};
	GLint vpos_location = glGetAttribLocation(shaderProgramID, "vPosition");	// program
	GLint vcol_location = glGetAttribLocation(shaderProgramID, "vColour");	// program;
	GLint vnorm_location = glGetAttribLocation(shaderProgramID, "vNormal");	// program;
	GLint vUV_location = glGetAttribLocation(shaderProgramID, "vUVx2");	// program;

	// Set the vertex attributes for this shader
	glEnableVertexAttribArray(vpos_location);	// vPos
	glVertexAttribPointer(vpos_location, 4,		// now a vec4
						  GL_FLOAT, GL_FALSE,
						  sizeof(ModelVertex),						// sizeof(float) * 6,
						  (void*)(offsetof(ModelVertex, pos.x)));

	glEnableVertexAttribArray(vcol_location);	// vCol
	glVertexAttribPointer(vcol_location, 4,		// vCol
						  GL_FLOAT, GL_FALSE,
						  sizeof(ModelVertex),
						  (void*)(offsetof(ModelVertex, col.r)));


	//	float nx, ny, nz, nw;
	glEnableVertexAttribArray(vnorm_location);	// vNormal
	glVertexAttribPointer(vnorm_location, 4,		// vNormal
						  GL_FLOAT, GL_FALSE,
						  sizeof(ModelVertex),
						  (void*)(offsetof(ModelVertex, norm.x)));

	//	float u0, v0, u1, v1;
	glEnableVertexAttribArray(vUV_location);		// vUVx2
	glVertexAttribPointer(vUV_location, 4,		// vUVx2
						  GL_FLOAT, GL_FALSE,
						  sizeof(ModelVertex),
						  (void*)(offsetof(ModelVertex, tex0.s)));



	// Now that all the parts are set up, set the VAO to zero
	glBindVertexArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(vpos_location);
	glDisableVertexAttribArray(vcol_location);


	// Store the draw information into the map
	this->m_map_ModelName_to_VAOID[drawInfo.meshName] = drawInfo;


	return true;
}


// We don't want to return an int, likely
bool VAOManager::FindDrawInfoByModelName(
	std::string filename,
	ModelDrawInfo& drawInfo)
{
	std::map< std::string /*model name*/,
		ModelDrawInfo /* info needed to draw*/ >::iterator
		itDrawInfo = this->m_map_ModelName_to_VAOID.find(filename);

	// Find it? 
	if (itDrawInfo == this->m_map_ModelName_to_VAOID.end())
	{
		// Nope
		return false;
	}

	// Else we found the thing to draw
	// ...so 'return' that information
	drawInfo = itDrawInfo->second;
	return true;
}

