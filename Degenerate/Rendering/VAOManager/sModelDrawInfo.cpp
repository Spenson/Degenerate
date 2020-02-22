#include "sModelDrawInfo.h"


sModelDrawInfo::sModelDrawInfo()
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

void sModelDrawInfo::CalcExtents(void)
{
	// See if we have any vertices loaded...
	if ((this->numberOfVertices == 0) || (this->pVertices == 0))
	{
		return;
	}

	// We're good

	// Assume the 1st vertex is the max and min (so we can compare)
	this->minX = this->maxX = this->pVertices[0].x;
	this->minY = this->maxY = this->pVertices[0].y;
	this->minZ = this->maxZ = this->pVertices[0].z;

	for (unsigned int index = 0; index != this->numberOfVertices; index++)
	{
		if (this->pVertices[index].x < this->minX) { this->minX = this->pVertices[index].x; }
		if (this->pVertices[index].y < this->minY) { this->minY = this->pVertices[index].y; }
		if (this->pVertices[index].z < this->minZ) { this->minZ = this->pVertices[index].z; }

		if (this->pVertices[index].x < this->maxX) { this->maxX = this->pVertices[index].x; }
		if (this->pVertices[index].y < this->maxY) { this->maxY = this->pVertices[index].y; }
		if (this->pVertices[index].z < this->maxZ) { this->maxZ = this->pVertices[index].z; }
	}

	this->extentX = this->maxX - this->minX;
	this->extentY = this->maxY - this->minY;
	this->extentZ = this->maxZ - this->minZ;

	this->maxExtent = this->extentX;
	if (this->extentY > this->maxExtent) { this->maxExtent = this->extentY; }
	if (this->extentZ > this->maxExtent) { this->maxExtent = this->extentZ; }

	return;
}

