#pragma once


static const unsigned int NUMBEROFBONES = 4;
struct sComplexVertex
{
	sComplexVertex();
	
	float x, y, z, w;			// w coordinate	
	float r, g, b, a;	// a = alpha (transparency)
	float nx, ny, nz, nw;
	float u0, v0, u1, v1;

	// For bump mapping
	float tx, ty, tz, tw;	// tangent				// 
	float bx, by, bz, bw;	// bi-normal			// 

	// For skinned mesh
	// For the 4 bone skinned mesh information
	float boneID[NUMBEROFBONES]; 		// New		// 
	float boneWeights[NUMBEROFBONES];	// New		// 
};
