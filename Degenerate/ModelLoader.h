#pragma once


#include <string>	
#include "Mesh.h"

class ModelLoader
{
public:
	ModelLoader();			// constructor
	~ModelLoader();		// destructor

	// Takes the filename to load
	// Returns by ref the mesh
	bool LoadPlyModel(std::string filename,
					  Mesh& theMesh);		// Note the & (by reference)

};
