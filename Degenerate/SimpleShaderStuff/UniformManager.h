#pragma once
#include "../globals.h"
#include "../ShaderManager/cShaderManager.h"
#include "../GameObject/cGameObject.h"
#include "../VAOManager/cVAOManager.h"


// Didn't want these everywhere! I can find them here
class UniformManager
{
public:

	static GLuint shaderProgID;
	static cShaderManager* pTheShaderManager;

	//Uniforms
	static GLint eyeLocation_UL;
	static GLint matView_UL;
	static GLint matProj_UL;
	static GLint textSamp00_UL;
	static GLint textSamp01_UL;
	static GLint textSamp02_UL;
	static GLint textSamp03_UL;
	static GLint tex0_ratio_UL;
	//static GLint textureWhatTheWhat_UL;
	//static GLint bIsSkyBox_UL;
	static GLint skyBoxSampler_UL;
	static GLint matModel_UL;
	static GLint matModelIT_UL;
	static GLint newColour_location;
	static GLint diffuseColour_UL;
	static GLint specularColour_UL;
	static GLint debugColour_UL;

	static GLint heightMap_UL;
	static GLint isWater_UL;
	static GLint isIsland_UL;
	static GLint offsetText1_UL;
	static GLint textOffset_UL;
	//static GLint bDoNotLight_UL;

	static GLint boolModifiers_UL; // doNotLight, isSkyBox, useDiffuse, isImposter

	static bool Init();

};