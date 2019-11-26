#include "Rendering.h"
#include "UniformManager.h"
#include <glm/gtc/type_ptr.hpp>


void SetUpTextureBindingsForObject(cGameObject* pCurrentObject, GLint shaderProgID)
{
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

	glUniform1i(UniformManager::textSamp00_UL, 0);	// Texture unit 0

	glUniform1i(UniformManager::textSamp01_UL, 1);	// Texture unit 1

	glUniform1i(UniformManager::textSamp02_UL, 2);	// Texture unit 2

	glUniform1i(UniformManager::textSamp03_UL, 3);	// Texture unit 3

	glUniform4f(UniformManager::tex0_ratio_UL,
				pCurrentObject->textureRatio[0],		// 1.0
				pCurrentObject->textureRatio[1],
				pCurrentObject->textureRatio[2],
				pCurrentObject->textureRatio[3]);

	{
		//textureWhatTheWhat
		// TODO: Fix garbage name
		//GLuint texSampWHAT_ID = ::g_pTextureManager->getTextureIDFromName("WhatTheWhat.bmp");
		//glActiveTexture(GL_TEXTURE13);				// Texture Unit 13
		//glBindTexture(GL_TEXTURE_2D, texSampWHAT_ID);	// Texture now assoc with texture unit 0

		//glUniform1i(UniformManager::textureWhatTheWhat_UL, 13);	// Texture unit 13
	}



	return;
}




void DrawObject(glm::mat4 matModel, cGameObject* pCurrentObject, GLint shaderProgID, cVAOManager* pVAOManager)
{

	if (pCurrentObject->isVisible == false)
	{
		return;
	}

	// Turns on "alpha transparency"
	glEnable(GL_BLEND);

	// Reads what's on the buffer already, and 
	// blends it with the incoming colour based on the "alpha" 
	// value, which is the 4th colour output
	// RGB+A
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// This block of code, where I generate the world matrix from the 
	// position, scale, and rotation (orientation) of the object
	// has been placed into calculateWorldMatrix()


	// ************ 
	// Set the texture bindings and samplers

	// See if this is a skybox object? 

	float isSkyBox = GL_FALSE;

	if (pCurrentObject->friendlyName != "skybox")
	{
		// Is a regular 2D textured object
		SetUpTextureBindingsForObject(pCurrentObject, shaderProgID);
		//glUniform1f(UniformManager::bIsSkyBox_UL, (float)GL_FALSE);
		isSkyBox = GL_FALSE;

		// Don't draw back facing triangles (default)
		glCullFace(GL_BACK);
	}
	else
	{
		// Draw the back facing triangles. 
		// Because we are inside the object, so it will force a draw on the "back" of the sphere 
		glCullFace(GL_FRONT_AND_BACK);

		//glUniform1f(UniformManager::bIsSkyBox_UL, (float)GL_TRUE);
		isSkyBox = GL_TRUE;

		GLuint skyBoxTextureID = ::g_pTextureManager->getTextureIDFromName("space");
		glActiveTexture(GL_TEXTURE26);				// Texture Unit 26
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyBoxTextureID);	// Texture now assoc with texture unit 0

		// Tie the texture units to the samplers in the shader
		glUniform1i(UniformManager::skyBoxSampler_UL, 26);	// Texture unit 26
	}


	// ************


	//glm::mat4 matWorld = glm::mat4(1.0f);	// identity matry

	glm::mat4 matWorldCurrentGO = calculateWorldMatrix(pCurrentObject, matModel);



	//uniform mat4 matModel;		// Model or World 
	//uniform mat4 matView; 		// View or camera
	//uniform mat4 matProj;


	glUniformMatrix4fv(UniformManager::matModel_UL, 1, GL_FALSE, glm::value_ptr(matWorldCurrentGO));
	//glUniformMatrix4fv(matView_UL, 1, GL_FALSE, glm::value_ptr(v));
	//glUniformMatrix4fv(matProj_UL, 1, GL_FALSE, glm::value_ptr(p));

	// Calcualte the inverse transpose of the model matrix and pass that...
	// Stripping away scaling and translation, leaving only rotation
	// Because the normal is only a direction, really

	glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matWorldCurrentGO));
	glUniformMatrix4fv(UniformManager::matModelIT_UL, 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));




	// Find the location of the uniform variable newColour

	glUniform3f(UniformManager::newColour_location,
				pCurrentObject->objectColourRGBA.r,
				pCurrentObject->objectColourRGBA.g,
				pCurrentObject->objectColourRGBA.b);

	glUniform4f(UniformManager::diffuseColour_UL,
				pCurrentObject->diffuseColour.r,
				pCurrentObject->diffuseColour.g,
				pCurrentObject->diffuseColour.b,
				pCurrentObject->diffuseColour.a);	// *********

	glUniform4f(UniformManager::specularColour_UL,
				pCurrentObject->specularColour.r,	// R
				pCurrentObject->specularColour.g,	// G
				pCurrentObject->specularColour.b,	// B
				pCurrentObject->specularColour.a);	// Specular "power" (how shinny the object is)
							// 1.0 to really big (10000.0f)


	//uniform vec4 debugColour;
	//uniform bool bDoNotLight;

	float doNotLight = GL_FALSE;

	if (pCurrentObject->isWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES
		glUniform4f(UniformManager::debugColour_UL,
					pCurrentObject->debugColour.r,
					pCurrentObject->debugColour.g,
					pCurrentObject->debugColour.b,
					pCurrentObject->debugColour.a);
		//glUniform1f(UniformManager::bDoNotLight_UL, (float)GL_TRUE);
		doNotLight = GL_TRUE;
	}
	else if (pCurrentObject->doNotLight)
	{	// Regular object (lit and not wireframe)
		//glUniform1f(UniformManager::bDoNotLight_UL, (float)GL_TRUE);
		doNotLight = GL_TRUE;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
	}
	else
	{	// Regular object (lit and not wireframe)
		//glUniform1f(UniformManager::bDoNotLight_UL, (float)GL_FALSE);
		doNotLight = GL_FALSE;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
	}
	//glPointSize(15.0f);

	float useDiffuse = pCurrentObject->useDiffuse;
	float isImposter = pCurrentObject->isImposter;

	glUniform4f(UniformManager::boolModifiers_UL,
				doNotLight,
				isSkyBox,
				useDiffuse,
				isImposter);


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

	sModelDrawInfo drawInfo;
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


	// Draw any child objects...
	for (std::vector<cGameObject*>::iterator itCGO = pCurrentObject->vec_pChildObjects.begin();
		 itCGO != pCurrentObject->vec_pChildObjects.end(); itCGO++)
	{
		// I'm passing in the current game object matrix... 
		cGameObject* pChildGO = *itCGO;

		// NOTE: Scale of the parent object will mess around 
		//	with the translations (and later scaling) of the child object.
		float inverseScale = 1.0f / pCurrentObject->scale;
		glm::mat4 matInverseScale = glm::scale(glm::mat4(1.0f),
											   glm::vec3(inverseScale, inverseScale, inverseScale));

		// Apply the inverse of the parent's scale to the matrix, 
		// leaving only tranlation and rotation
		glm::mat4 matParentNoScale = matWorldCurrentGO * matInverseScale;


		DrawObject(matParentNoScale, pChildGO, shaderProgID, pVAOManager);
	}//for (std::vector<cGameObject*>::iterator itCGO




	return;
} // DrawObject;
