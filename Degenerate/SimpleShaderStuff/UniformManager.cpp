#include "UniformManager.h"
#include <iostream>



GLuint UniformManager::shaderProgID = NULL;
cShaderManager* UniformManager::pTheShaderManager = NULL;


GLint UniformManager::eyeLocation_UL = NULL;
GLint UniformManager::matView_UL = NULL;
GLint UniformManager::matProj_UL = NULL;
GLint UniformManager::textSamp00_UL = NULL;
GLint UniformManager::textSamp01_UL = NULL;
GLint UniformManager::textSamp02_UL = NULL;
GLint UniformManager::textSamp03_UL = NULL;
GLint UniformManager::tex0_ratio_UL = NULL;
//GLint UniformManager::textureWhatTheWhat_UL = NULL;
//GLint UniformManager::bIsSkyBox_UL = NULL;
GLint UniformManager::skyBoxSampler_UL = NULL;
GLint UniformManager::matModel_UL = NULL;
GLint UniformManager::matModelIT_UL = NULL;
GLint UniformManager::newColour_location = NULL;
GLint UniformManager::diffuseColour_UL = NULL;
GLint UniformManager::specularColour_UL = NULL;
GLint UniformManager::debugColour_UL = NULL;
//GLint UniformManager::bDoNotLight_UL = NULL;


GLint UniformManager::boolModifiers_UL = NULL;






bool UniformManager::Init()
{

	pTheShaderManager = new cShaderManager();

	cShaderManager::cShader vertexShad;
	vertexShad.fileName = "assets/shaders/vertexShader01.glsl";

	cShaderManager::cShader fragShader;
	fragShader.fileName = "assets/shaders/fragmentShader01.glsl";

	if (!pTheShaderManager->createProgramFromFile("SimpleShader", vertexShad, fragShader))
	{
		std::cout << "Error: didn't compile the shader" << std::endl;
		std::cout << pTheShaderManager->getLastError();
		return false;
	}



	shaderProgID = pTheShaderManager->getIDFromFriendlyName("SimpleShader");

	eyeLocation_UL = glGetUniformLocation(shaderProgID, "eyeLocation");

	matView_UL = glGetUniformLocation(shaderProgID, "matView");
	matProj_UL = glGetUniformLocation(shaderProgID, "matProj");

	textSamp00_UL = glGetUniformLocation(shaderProgID, "textSamp00");
	textSamp01_UL = glGetUniformLocation(shaderProgID, "textSamp01");
	textSamp02_UL = glGetUniformLocation(shaderProgID, "textSamp02");
	textSamp03_UL = glGetUniformLocation(shaderProgID, "textSamp03");

	tex0_ratio_UL = glGetUniformLocation(shaderProgID, "tex_0_3_ratio");

	//textureWhatTheWhat_UL = glGetUniformLocation(shaderProgID, "textureWhatTheWhat");

	//bIsSkyBox_UL = glGetUniformLocation(shaderProgID, "bIsSkyBox");
	//bDoNotLight_UL = glGetUniformLocation(shaderProgID, "bDoNotLight");

	boolModifiers_UL = glGetUniformLocation(shaderProgID, "boolModifiers");

	skyBoxSampler_UL = glGetUniformLocation(shaderProgID, "skyBox");

	matModel_UL = glGetUniformLocation(shaderProgID, "matModel");
	matModelIT_UL = glGetUniformLocation(shaderProgID, "matModelInverseTranspose");

	newColour_location = glGetUniformLocation(shaderProgID, "newColour");
	diffuseColour_UL = glGetUniformLocation(shaderProgID, "diffuseColour");
	specularColour_UL = glGetUniformLocation(shaderProgID, "specularColour");
	debugColour_UL = glGetUniformLocation(shaderProgID, "debugColour");




	return true;
}


