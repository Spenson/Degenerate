#include "ModelLoader.h"

#include <iostream>			// cin cout
#include <fstream>		    // ifstream ofstream

ModelLoader::ModelLoader()			// constructor
{
	std::cout << "Model Loader is initialized!" << std::endl;
	return;
}

ModelLoader::~ModelLoader()			// destructor
{
	std::cout << "Model Loader is destroyed!" << std::endl;
	return;
}

// Takes the filename to load
// Returns by ref the mesh
bool ModelLoader::LoadPlyModel(
	std::string filename,
	Mesh& theMesh)				// Note the "&"
{

	std::ifstream theFile(filename.c_str());
	if (!theFile.is_open())
	{
		// On no! Where's the file??? 
		return false;
	}

	// Scan the file until I get to "vertex", and stop
	std::string temp;
	//theFile >> temp;
	while (theFile >> temp)
	{
		// Have it hit the word "vertex"?
		if (temp == "vertex")
		{
			break;		// Exit the while loop
		}
	}// while ( theFile >> temp ) 

	unsigned int numberOfVertices;
	theFile >> numberOfVertices;



	while (theFile >> temp)
	{
		// Have it hit the word "face"?
		if (temp == "face")
		{
			break;		// Exit the while loop
		}
	}// while ( theFile >> temp ) 

	unsigned int numberOfTriangles;
	theFile >> numberOfTriangles;

	while (theFile >> temp)
	{
		// Have it hit the word "end_header"?
		if (temp == "end_header")
		{
			break;		// Exit the while loop
		}
	}// while ( theFile >> temp ) 



	// Read all the vertices
	for (unsigned int index = 0; index != numberOfVertices; index++)
	{
		// -0.0312216 0.126304 0.00514924
		VertexWithNormal tempVertex;

		// -0.0312216 0.126304 0.00514924
		theFile >> tempVertex.x >> tempVertex.y >> tempVertex.z;

		// Also load the normals
		theFile >> tempVertex.nx >> tempVertex.ny >> tempVertex.nz;

		// Add this temp vertex to the vector of vertices
		// (cMesh &theMesh)
		theMesh.vecVertices.push_back(tempVertex);
	}

	for (unsigned int index = 0; index != numberOfTriangles; index++)
	{
		// 3 166 210 265 
		int discardThis;
		TriangleIndex tempTriangle;

		theFile >> discardThis
			>> tempTriangle.a
			>> tempTriangle.b
			>> tempTriangle.c;

		// Add this triangle
		theMesh.vecTriangles.push_back(tempTriangle);
	}


	return true;
}
