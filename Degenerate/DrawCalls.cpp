#include "DrawCalls.h"
#include "MatrixCalc.h"

#include <glm/glm.hpp>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include <iostream>

GLint eyeLocation_UL;
GLint matView_UL;
GLint matProj_UL;

ShaderManager* pTheShaderManager;
GLuint shaderProgID;

GLint matModel_UL;
GLint matModelIT_UL;
GLint diffuseColour_UL;
GLint specularColour_UL;
GLint debugColour_UL;
GLint bDoNotLight_UL;
GLint newColour_location;

cBasicTextureManager* g_pTextureManager = NULL;


void InitUniformLocations()
{
	pTheShaderManager = new ShaderManager();

	ShaderManager::Shader vertexShad;
	vertexShad.fileName = "../assets/shaders/vertexShader01.glsl";

	ShaderManager::Shader fragShader;
	fragShader.fileName = "../assets/shaders/fragmentShader01.glsl";

	if (!pTheShaderManager->createProgramFromFile("SimpleShader", vertexShad, fragShader))
	{
		std::cout << "Error: didn't compile the shader" << std::endl;
		std::cout << pTheShaderManager->getLastError();
		exit(-1);
	}

	::g_pTextureManager = new cBasicTextureManager();
	::g_pTextureManager->SetBasePath("assets/textures");

	shaderProgID = pTheShaderManager->getIDFromFriendlyName("SimpleShader");

	eyeLocation_UL = glGetUniformLocation(shaderProgID, "eyeLocation");

	matView_UL = glGetUniformLocation(shaderProgID, "matView");
	matProj_UL = glGetUniformLocation(shaderProgID, "matProj");

	// Declared above in global. TODO: As above
	matModel_UL = glGetUniformLocation(shaderProgID, "matModel");
	matModelIT_UL = glGetUniformLocation(shaderProgID, "matModelInverseTranspose");
	diffuseColour_UL = glGetUniformLocation(shaderProgID, "diffuseColour");
	specularColour_UL = glGetUniformLocation(shaderProgID, "specularColour");
	debugColour_UL = glGetUniformLocation(shaderProgID, "debugColour");
	bDoNotLight_UL = glGetUniformLocation(shaderProgID, "bDoNotLight");
	newColour_location = glGetUniformLocation(shaderProgID, "newColour");
}

void SetUpTextureBindingsForObject(GameObject* pCurrentObject, GLint shaderProgID)
{

	//// Tie the texture to the texture unit
	//GLuint texSamp0_UL = ::g_pTextureManager->getTextureIDFromName("Pizza.bmp");
	//glActiveTexture(GL_TEXTURE0);				// Texture Unit 0
	//glBindTexture(GL_TEXTURE_2D, texSamp0_UL);	// Texture now assoc with texture unit 0

	// Tie the texture to the texture unit
	GLuint texSamp0_UL = ::g_pTextureManager->getTextureIDFromName(pCurrentObject->textures[0]);
	glActiveTexture(GL_TEXTURE0);				// Texture Unit 0
	glBindTexture(GL_TEXTURE_2D, texSamp0_UL);	// Texture now assoc with texture unit 0

	GLuint texSamp1_UL = ::g_pTextureManager->getTextureIDFromName(pCurrentObject->textures[1]);
	glActiveTexture(GL_TEXTURE1);				// Texture Unit 1
	glBindTexture(GL_TEXTURE_2D, texSamp1_UL);	// Texture now assoc with texture unit 0

	GLuint texSamp2_UL = ::g_pTextureManager->getTextureIDFromName(pCurrentObject->textures[2]);
	glActiveTexture(GL_TEXTURE2);				// Texture Unit 2
	glBindTexture(GL_TEXTURE_2D, texSamp2_UL);	// Texture now assoc with texture unit 0

	GLuint texSamp3_UL = ::g_pTextureManager->getTextureIDFromName(pCurrentObject->textures[3]);
	glActiveTexture(GL_TEXTURE3);				// Texture Unit 3
	glBindTexture(GL_TEXTURE_2D, texSamp3_UL);	// Texture now assoc with texture unit 0

	// Tie the texture units to the samplers in the shader
	GLint textSamp00_UL = glGetUniformLocation(shaderProgID, "textSamp00");
	glUniform1i(textSamp00_UL, 0);	// Texture unit 0

	GLint textSamp01_UL = glGetUniformLocation(shaderProgID, "textSamp01");
	glUniform1i(textSamp01_UL, 1);	// Texture unit 1

	GLint textSamp02_UL = glGetUniformLocation(shaderProgID, "textSamp02");
	glUniform1i(textSamp02_UL, 2);	// Texture unit 2

	GLint textSamp03_UL = glGetUniformLocation(shaderProgID, "textSamp03");
	glUniform1i(textSamp03_UL, 3);	// Texture unit 3


	GLint tex0_ratio_UL = glGetUniformLocation(shaderProgID, "tex_0_3_ratio");
	glUniform4f(tex0_ratio_UL,
				pCurrentObject->textureRatio[0],		// 1.0
				pCurrentObject->textureRatio[1],
				pCurrentObject->textureRatio[2],
				pCurrentObject->textureRatio[3]);

	{
		//textureWhatTheWhat
		GLuint texSampWHAT_ID = ::g_pTextureManager->getTextureIDFromName("WhatTheWhat.bmp");
		glActiveTexture(GL_TEXTURE13);				// Texture Unit 13
		glBindTexture(GL_TEXTURE_2D, texSampWHAT_ID);	// Texture now assoc with texture unit 0

		GLint textureWhatTheWhat_UL = glGetUniformLocation(shaderProgID, "textureWhatTheWhat");
		glUniform1i(textureWhatTheWhat_UL, 13);	// Texture unit 13
	}



	return;
}




void DrawObject(glm::mat4 matModel,
				GameObject* pCurrentObject,
				GLint shaderProgID,
				VAOManager* pVAOManager)
{

	if (pCurrentObject->isVisible == false)
	{
		return;
	}
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	GLint bIsSkyBox_UL = glGetUniformLocation(shaderProgID, "bIsSkyBox");
	if (pCurrentObject->friendlyName != "skybox")
	{
		// Is a regular 2D textured object
		SetUpTextureBindingsForObject(pCurrentObject, shaderProgID);
		glUniform1f(bIsSkyBox_UL, (float)GL_FALSE);

		// Don't draw back facing triangles (default)
		glCullFace(GL_BACK);
	}
	else
	{
		// Draw the back facing triangles. 
		// Because we are inside the object, so it will force a draw on the "back" of the sphere 
		glCullFace(GL_FRONT_AND_BACK);

		glUniform1f(bIsSkyBox_UL, (float)GL_TRUE);

		GLuint skyBoxTextureID = ::g_pTextureManager->getTextureIDFromName("space");
		glActiveTexture(GL_TEXTURE26);				// Texture Unit 26
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextureID);	// Texture now assoc with texture unit 0

		// Tie the texture units to the samplers in the shader
		GLint skyBoxSampler_UL = glGetUniformLocation(shaderProgID, "skyBox");
		glUniform1i(skyBoxSampler_UL, 26);	// Texture unit 26
	}



	// mat4x4_identity(m);
	glm::mat4 matWorldCurrentGO = calculateWorldMatrix(pCurrentObject, matModel);




	//uniform mat4 matModel;		// Model or World 
	//uniform mat4 matView; 		// View or camera
	//uniform mat4 matProj;


	glUniformMatrix4fv(matModel_UL, 1, GL_FALSE, glm::value_ptr(matWorldCurrentGO));
	//glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
	//glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));

	// Calcualte the inverse transpose of the model matrix and pass that...
	// Stripping away scaling and translation, leaving only rotation
	// Because the normal is only a direction, really


	glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matWorldCurrentGO));
	glUniformMatrix4fv(matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));


	// Find the location of the uniform variable newColour

	glUniform3f(newColour_location,
				pCurrentObject->objectColour.r,
				pCurrentObject->objectColour.g,
				pCurrentObject->objectColour.b);


	glUniform4f(diffuseColour_UL,
				pCurrentObject->objectColour.r,
				pCurrentObject->objectColour.g,
				pCurrentObject->objectColour.b,
				pCurrentObject->objectColour.a);	// 

	glUniform4f(specularColour_UL,
				1.0f,	// R
				1.0f,	// G
				1.0f,	// B
				1000.0f);	// Specular "power" (how shinny the object is)
							// 1.0 to really big (10000.0f)


	//uniform vec4 debugColour;
	//uniform bool bDoNotLight;

	if (pCurrentObject->isWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES
		glUniform4f(debugColour_UL,
					pCurrentObject->debugColour.r,
					pCurrentObject->debugColour.g,
					pCurrentObject->debugColour.b,
					pCurrentObject->debugColour.a);
		glUniform1f(bDoNotLight_UL, (float)GL_TRUE);
	}
	else
	{	// Regular object (lit and not wireframe)
		glUniform1f(bDoNotLight_UL, (float)GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
	}
	//glPointSize(15.0f);

	if (pCurrentObject->disableDepthBufferTest)
	{
		glDisable(GL_DEPTH_TEST);					// DEPTH Test OFF
	}
	else
	{
		glEnable(GL_DEPTH_TEST);						// Turn ON depth test
	}

	if (pCurrentObject->disableDepthBufferWrite)
	{
		glDisable(GL_DEPTH);						// DON'T Write to depth buffer
	}
	else
	{
		glEnable(GL_DEPTH);								// Write to depth buffer
	}


	//		glDrawArrays(GL_TRIANGLES, 0, 2844);
	//		glDrawArrays(GL_TRIANGLES, 0, numberOfVertsOnGPU);

	ModelDrawInfo drawInfo;
	//if (pTheVAOManager->FindDrawInfoByModelName("bunny", drawInfo))
	if (pVAOManager->FindDrawInfoByModelName(pCurrentObject->meshName, drawInfo))
	{
		glBindVertexArray(drawInfo.VAO_ID);
		glDrawElements(GL_TRIANGLES,
					   drawInfo.numberOfIndices,
					   GL_UNSIGNED_INT,
					   0);
		glBindVertexArray(0);
	}



	for (std::vector<GameObject*>::iterator itCGO = pCurrentObject->vec_pChildObjects.begin();
		 itCGO != pCurrentObject->vec_pChildObjects.end(); itCGO++)
	{
		// I'm passing in the current game object matrix... 
		GameObject* pChildGO = *itCGO;

		// NOTE: Scale of the parent object will mess around 
		//	with the translations (and later scaling) of the child object.
		glm::vec3 inverseScale;
		inverseScale.x = 1.0f / pCurrentObject->scale.x;
		inverseScale.y = 1.0f / pCurrentObject->scale.y;
		inverseScale.z = 1.0f / pCurrentObject->scale.z;

		glm::mat4 matInverseScale = glm::scale(glm::mat4(1.0f),
											   glm::vec3(inverseScale.x, inverseScale.y, inverseScale.z));

		// Apply the inverse of the parent's scale to the matrix, 
		// leaving only tranlation and rotation
		glm::mat4 matParentNoScale = matWorldCurrentGO * matInverseScale;


		DrawObject(matParentNoScale, pChildGO, shaderProgID, pVAOManager);
	}//for (std::vector<cGameObject*>::iterator itCGO



	return;
} // DrawObject;