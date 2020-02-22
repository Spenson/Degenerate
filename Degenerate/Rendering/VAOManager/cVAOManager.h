#ifndef _cVAOManager_HG_
#define _cVAOManager_HG_

#include "../../GLCommon.h"

// Will load the models and place them 
// into the vertex and index buffers to be drawn

#include <string>
#include <map>
#include "../ModelStuff/cMesh.h"				// File as loaded from the file
#include "sModelDrawInfo.h"



class cVAOManager
{
public:

	// Takes a cMesh m_pGO and copies it into the GPU (as a VOA)
	bool LoadModelIntoVAO(std::string fileName, 
						  cMesh &theMesh,				// NEW
						  sModelDrawInfo &drawInfo, 
						  unsigned int shaderProgramID);

	bool LoadModelDrawInfoIntoVAO(sModelDrawInfo& drawInfo,
								  unsigned int shaderProgramID);
	
	// We don't want to return an int, likely
	bool FindDrawInfoByModelName(std::string filename,
								 sModelDrawInfo &drawInfo);

	std::string getLastError(bool bAndClear = true);

private:

	std::map< std::string /*model name*/,
		      sModelDrawInfo /* info needed to draw*/ >
		m_map_ModelName_to_VAOID;

};

#endif	// _cVAOManager_HG_
