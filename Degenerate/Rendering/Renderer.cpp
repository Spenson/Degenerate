#include "Renderer.h"

#include <iostream>
#include "SimpleShaderStuff/UniformManager.h"

namespace DegenRendering
{
	cBasicTextureManager* cRenderer::mTextureManager;
	cModelLoader* cRenderer::mModelLoader;
	cVAOManager* cRenderer::mVAOManager;
	cShaderManager* cRenderer::mShaderManager;


	cRenderer::cRenderer() : mCamera(nullptr), mSkybox(nullptr) {}

	bool cRenderer::Initialize()
	{
		if (!mTextureManager)
		{
			mTextureManager = new cBasicTextureManager();
			mTextureManager->SetBasePath("assets/textures/");

		}
		if (!mVAOManager)
		{
			mVAOManager = new cVAOManager();
		}
		if (!mModelLoader)
		{
			mModelLoader = new cModelLoader();
		}
		if (!mShaderManager)
		{
			mShaderManager = new cShaderManager();

			//cShaderManager* pTheShaderManager = new cShaderManager();

			cShaderManager::cShader vertexShad;
			vertexShad.fileName = "assets/shaders/vertexShader01.glsl";

			cShaderManager::cShader fragShader;
			fragShader.fileName = "assets/shaders/fragmentShader01.glsl";

			if (!mShaderManager->createProgramFromFile("UberShader", vertexShad, fragShader))
			{
				std::cout << "Error: didn't compile the shader" << std::endl;
				std::cout << mShaderManager->getLastError();
				return false;
			}
			mShaderManager->pGetShaderProgramFromFriendlyName("UberShader")->LoadActiveUniforms();
		}
		return true;
	}

	void cRenderer::SetPerspectiveDetails(float fovy, float near, float far)
	{
		mFOVY = fovy;
		mNearPlane = near;
		mFarPlane = far;
	}

	void cRenderer::AddModel(const std::string& model, std::string path)
	{
		if (path.empty())
			path = "./assets/models/";

		cMesh newMesh;
		if (mModelLoader->LoadPlyModel(path + model, newMesh))
			std::cout << "Loaded mesh: " << model << std::endl;
		else
			std::cout << "Didn't load mesh: " << path << model << std::endl;


		sModelDrawInfo drawInfo;
		if (mVAOManager->LoadModelIntoVAO(model, newMesh, drawInfo, mShaderManager->getIDFromFriendlyName("UberShader")))
			std::cout << "Loaded Mesh into VAO: " << model << std::endl;
		else
			std::cout << "Error loading Mesh into VAO: " << model << std::endl;
	}

	void cRenderer::AddModel(cSkinnedMesh* mesh)
	{
		mVAOManager->LoadModelDrawInfoIntoVAO(*mesh->CreateModelDrawInfoObjectFromCurrentModel(), mShaderManager->getIDFromFriendlyName("UberShader"));
	}

	void cRenderer::AddTexture(const std::string& texture, std::string path)
	{
		if (!path.empty())
			mTextureManager->SetBasePath(path);
		if (mTextureManager->Create2DTextureFromBMPFile(texture, true))
			std::cout << "Loaded texture: " << texture << std::endl;
		else
			std::cout << "Didn't load texture: " << texture << std::endl;
	}

	void cRenderer::AddCubeMap(const std::string& name, const std::string& up, const std::string& down,
							   const std::string& left, const std::string& right, const std::string& back,
							   const std::string& front, std::string path)
	{
		if (!path.empty())
			mTextureManager->SetBasePath(path);
		std::string errorString;
		if (mTextureManager->CreateCubeTextureFromBMPFiles(name,
														   left, right, down,
														   up, front, back,
														   true, errorString))
		{
			std::cout << "Loaded cube map: " << name << std::endl;
		}
		else
			std::cout << "Didn't load cube map: " << name << "\n\t" << errorString << std::endl;
	}

	void cRenderer::SetCamera(iCamera* camera)
	{
		mCamera = camera;
	}

	void cRenderer::SetSkybox(iSkybox* skybox)
	{
		mSkybox = skybox;


		const std::pair<std::string, float>* cubemaps = skybox->CubeMaps();

		// Tie the texture to the texture unit
		GLuint skybox0_UL = mTextureManager->getTextureIDFromName(cubemaps[0].first);
		glActiveTexture(GL_TEXTURE4);				// Texture Unit 0
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox0_UL);	// Texture now assoc with texture unit 0

		GLuint skybox1_UL = mTextureManager->getTextureIDFromName(cubemaps[1].first);
		glActiveTexture(GL_TEXTURE5);				// Texture Unit 1
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox1_UL);	// Texture now assoc with texture unit 0

		GLuint skybox2_UL = mTextureManager->getTextureIDFromName(cubemaps[2].first);
		glActiveTexture(GL_TEXTURE6);				// Texture Unit 2
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox2_UL);	// Texture now assoc with texture unit 0

		GLuint skybox3_UL = mTextureManager->getTextureIDFromName(cubemaps[3].first);
		glActiveTexture(GL_TEXTURE7);				// Texture Unit 3
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox3_UL);	// Texture now assoc with texture unit 0

	}

	bool cRenderer::AddRenderComponent(iRenderComponent* comp)
	{
		if (std::find(mObjects.begin(), mObjects.end(), comp) == mObjects.end())
		{
			mObjects.push_back(comp);
			return true;
		}
		return false;
	}

	bool cRenderer::RemoveRenderComponent(iRenderComponent* comp)
	{
		auto compiter = std::find(mObjects.begin(), mObjects.end(), comp);
		if (compiter == mObjects.end())
			return false;

		mObjects.erase(compiter);
		return true;
	}

	bool cRenderer::AddLight(iLight* light)
	{
		if (mLights.size() < MAX_LIGHTS && std::find(mLights.begin(), mLights.end(), light) == mLights.end())
		{
			mLights.push_back(light);
			return true;
		}
		return false;
	}

	void cRenderer::RenderScene(const int& width, const int& height)
	{
		cShaderManager::cShaderProgram* shaderProgram = mShaderManager->pGetShaderProgramFromFriendlyName("UberShader");

		glEnable(GL_DEPTH);			// Write to the depth buffer
		glEnable(GL_DEPTH_TEST);	// Test with buffer when drawing

		glUseProgram(shaderProgram->ID);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float ratio;
		ratio = (float)width / (float)height;

		glm::mat4 perspective = glm::perspective(mFOVY, ratio, mNearPlane, mFarPlane);
		glm::mat4 view = glm::lookAt(mCamera->Position(), mCamera->Target(), mCamera->UpVector());

		glUniformMatrix4fv(shaderProgram->getUniformLocID("matView"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(shaderProgram->getUniformLocID("matProj"), 1, GL_FALSE, glm::value_ptr(perspective));
		SetUpTextureBindingsForSkybox(shaderProgram);
		DrawSkybox(shaderProgram);

		for (size_t c = 0; c < mObjects.size(); c++)
		{
			if (mObjects[c]->GetComponentType() == eRendType::Model)
			{
				auto* pCurrentObject = dynamic_cast<iGeneralModel*>(mObjects[c]);
				DrawObject(glm::mat4(1.f), pCurrentObject, shaderProgram);
			}
		}
	}

	void cRenderer::SetUpTextureBindingsForObject(iGeneralModel* pCurrentObject, cShaderManager::cShaderProgram* shaderProg)
	{
		const std::pair<std::string, float>* textures = pCurrentObject->Textures();

		// Tie the texture to the texture unit
		GLuint texSamp0_UL = mTextureManager->getTextureIDFromName(textures[0].first);
		glActiveTexture(GL_TEXTURE0);				// Texture Unit 0
		glBindTexture(GL_TEXTURE_2D, texSamp0_UL);	// Texture now assoc with texture unit 0

		GLuint texSamp1_UL = mTextureManager->getTextureIDFromName(textures[1].first);
		glActiveTexture(GL_TEXTURE1);				// Texture Unit 1
		glBindTexture(GL_TEXTURE_2D, texSamp1_UL);	// Texture now assoc with texture unit 0

		GLuint texSamp2_UL = mTextureManager->getTextureIDFromName(textures[2].first);
		glActiveTexture(GL_TEXTURE2);				// Texture Unit 2
		glBindTexture(GL_TEXTURE_2D, texSamp2_UL);	// Texture now assoc with texture unit 0

		GLuint texSamp3_UL = mTextureManager->getTextureIDFromName(textures[3].first);
		glActiveTexture(GL_TEXTURE3);				// Texture Unit 3
		glBindTexture(GL_TEXTURE_2D, texSamp3_UL);	// Texture now assoc with texture unit 0

		// Tie the texture units to the samplers in the shader

		glUniform1i(shaderProg->getUniformLocID("texture00"), 0);	// Texture unit 0

		glUniform1i(shaderProg->getUniformLocID("texture01"), 1);	// Texture unit 1

		glUniform1i(shaderProg->getUniformLocID("texture02"), 2);	// Texture unit 2

		glUniform1i(shaderProg->getUniformLocID("texture03"), 3);	// Texture unit 3

		glUniform4f(shaderProg->getUniformLocID("texture_ratios"),
					textures[0].second,		// 1.0
					textures[1].second,
					textures[2].second,
					textures[3].second);
		return;
	}

	void cRenderer::DrawObject(glm::mat4 matModel, iGeneralModel* pCurrentObject, cShaderManager::cShaderProgram* shaderProg)
	{

		if (pCurrentObject->Visable() == false)
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


		SetUpTextureBindingsForObject(pCurrentObject, shaderProg);

		// Don't draw back facing triangles (default)
		glCullFace(GL_BACK);

		glUniform1f(shaderProg->getUniformLocID("useOffset"), (float)GL_FALSE);
		glUniform1f(shaderProg->getUniformLocID("offset"), 0.f);

		glm::mat4 matWorldCurrentGO = matModel * (pCurrentObject->Transform() * glm::scale(glm::mat4(1.f), pCurrentObject->Scale()));

		glUniformMatrix4fv(shaderProg->getUniformLocID("matModel"), 1, GL_FALSE, glm::value_ptr(matWorldCurrentGO));

		// Calcualte the inverse transpose of the model matrix and pass that...
		// Stripping away scaling and translation, leaving only rotation
		// Because the normal is only a direction, really

		glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matWorldCurrentGO));
		glUniformMatrix4fv(shaderProg->getUniformLocID("matModelInverseTranspose"), 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));




		// Find the location of the uniform variable newColour


		glUniform4f(shaderProg->getUniformLocID("diffuseColour"),
					pCurrentObject->Diffuse().r,
					pCurrentObject->Diffuse().g,
					pCurrentObject->Diffuse().b,
					pCurrentObject->Diffuse().a);	// *********

		glUniform4f(shaderProg->getUniformLocID("specularColour"),
					pCurrentObject->Specular().r,	// R
					pCurrentObject->Specular().g,	// G
					pCurrentObject->Specular().b,	// B
					pCurrentObject->Specular().a);	// Specular "power" (how shinny the m_pGO is)
													// 1.0 to really big (10000.0f)


					//uniform vec4 debugColour;
					//uniform bool bDoNotLight;

		float doNotLight = pCurrentObject->IgnoreLighting();

		if (pCurrentObject->Wireframe())
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);		// LINES

			//glUniform1f(UniformManager::bDoNotLight_UL, (float)GL_TRUE);
			doNotLight = GL_TRUE;
		}
		else
		{	// Regular m_pGO (lit and not wireframe)
			//glUniform1f(UniformManager::bDoNotLight_UL, (float)GL_FALSE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		// SOLID
		}
		//glPointSize(15.0f);

		float useDiffuse = pCurrentObject->UseDiffuse();
		//float isImposter = GL_FALSE;

		glUniform4f(shaderProg->getUniformLocID("boolModifiers"),
			(float)ShaderMode::Object,
					doNotLight,
					useDiffuse,
					0);


		if (!pCurrentObject->DepthBufferTest())
		{
			glDisable(GL_DEPTH_TEST);					// DEPTH Test OFF
		}
		else
		{
			glEnable(GL_DEPTH_TEST);						// Turn ON depth test
		}

		if (!pCurrentObject->DepthBufferWrite())
		{
			glDisable(GL_DEPTH);						// DON'T Write to depth buffer
		}
		else
		{
			glEnable(GL_DEPTH);								// Write to depth buffer
		}


		//		glDrawArrays(GL_TRIANGLES, 0, 2844);
		//		glDrawArrays(GL_TRIANGLES, 0, numberOfVertsOnGPU);











		if (pCurrentObject->IsSkinnedMesh())
		{
			glUniform1f(shaderProg->getUniformLocID("isSkinnedMesh"), (float)GL_TRUE);

			// Set to all identity
			const int NUMBEROFBONES = 100;
			//glm::mat4 matBones[NUMBEROFBONES];

			//for (int index = 0; index != NUMBEROFBONES; index++)
			//{
			//	matBones[index] = glm::mat4(1.0f);	// Identity
			//}

			// Taken from "Skinned Mesh 2 - todo.docx"
			std::vector< glm::mat4x4 > vecFinalTransformation;
			std::vector< glm::mat4x4 > vecOffsets;
			std::vector< glm::mat4x4 > vecObjectBoneTransformation;

			// This loads the bone transforms from the animation model
			pCurrentObject->Mesh()->BoneTransform(pCurrentObject->CurrentAnimationTime(),	// 0.0f // Frame time
												  pCurrentObject->CurrentAnimation(),
												  vecFinalTransformation,
												  vecObjectBoneTransformation,
												  vecOffsets);

			// Wait until all threads are done updating.

			//HACK_FrameTime += 0.01f;

			//{// Forward kinematic stuff

			//	// "Bone" location is at the origin
			//	glm::vec4 boneLocation = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

			//	// bone #22 is "B_R_Hand" in this model
			//	glm::mat4 matSpecificBone = vecFinalTransformation[22];

			//	// Transformed into "model" space where that bone is.
			//	::g_HACK_vec3_BoneLocationFK = matSpecificBone * boneLocation;

			//	//			// If it's in world space
			//	//			::g_HACK_vec3_BoneLocationFK = matModel * ::g_HACK_vec3_BoneLocationFK;


			//}// Forward kinematic 


				// Copy all 100 bones to the shader
		//	GLint matBonesArray_UniLoc = glGetUniformLocation(shaderProgID, "matBonesArray");
			// The "100" is to pass 100 values, starting at the pointer location of matBones[0];
			//glUniformMatrix4fv(matBonesArray_UniLoc, 100, GL_FALSE, glm::value_ptr(matBones[0]));

			GLint numBonesUsed = (GLint)vecFinalTransformation.size();

			glUniformMatrix4fv(shaderProg->getUniformLocID("matBonesArray[0]"), numBonesUsed,
							   GL_FALSE,
							   glm::value_ptr(vecFinalTransformation[0]));

		}
		else
		{
			glUniform1f(shaderProg->getUniformLocID("isSkinnedMesh"), (float)GL_FALSE);
		}
		// ************************************************


























		sModelDrawInfo drawInfo;
		//if (pTheVAOManager->FindDrawInfoByModelName("bunny", drawInfo))
		if (mVAOManager->FindDrawInfoByModelName(pCurrentObject->Model(), drawInfo))
		{
			glBindVertexArray(drawInfo.VAO_ID);
			glDrawElements(GL_TRIANGLES,
						   drawInfo.numberOfIndices,
						   GL_UNSIGNED_INT,
						   0);
			glBindVertexArray(0);
		}


		// Draw any child objects...
		std::vector<iGeneralModel*> hack = pCurrentObject->Children();
		if (hack.size() > 0)
			for (std::vector<iGeneralModel*>::iterator itCGO = hack.begin();
				 itCGO != hack.end(); itCGO++)
		{
			// I'm passing in the current game m_pGO matrix... 
			iGeneralModel* pChildGO = *itCGO;

			// NOTE: Scale of the parent m_pGO will mess around 
			//	with the translations (and later scaling) of the child m_pGO.
			//float inverseScale = 1.0f / pCurrentObject->scale;
			//glm::mat4 matInverseScale = glm::scale(glm::mat4(1.0f),
			//									   glm::vec3(inverseScale, inverseScale, inverseScale));

			// Apply the inverse of the parent's scale to the matrix, 
			// leaving only tranlation and rotation
			//glm::mat4 matParentNoScale = matWorldCurrentGO * matInverseScale;


			DrawObject(pCurrentObject->Transform(), pChildGO, shaderProg);//, pVAOManager);
		}//for (std::vector<cGameObject*>::iterator itCGO







		return;
	} // DrawObject;

	void cRenderer::SetUpTextureBindingsForSkybox(cShaderManager::cShaderProgram* shaderProg)
	{
		const std::pair<std::string, float>* cubemaps = mSkybox->CubeMaps();

		// Tie the texture units to the samplers in the shader

		glUniform1i(mShaderManager->pGetShaderProgramFromFriendlyName("UberShader")->getUniformLocID("skybox00"), 4);	// Texture unit 0

		glUniform1i(mShaderManager->pGetShaderProgramFromFriendlyName("UberShader")->getUniformLocID("skybox01"), 5);	// Texture unit 1

		glUniform1i(mShaderManager->pGetShaderProgramFromFriendlyName("UberShader")->getUniformLocID("skybox02"), 6);	// Texture unit 2

		glUniform1i(mShaderManager->pGetShaderProgramFromFriendlyName("UberShader")->getUniformLocID("skybox03"), 7);	// Texture unit 3

		glUniform4f(mShaderManager->pGetShaderProgramFromFriendlyName("UberShader")->getUniformLocID("skybox_ratios"),
					cubemaps[0].second, cubemaps[1].second, cubemaps[2].second, cubemaps[3].second);
	}

	void cRenderer::DrawSkybox(cShaderManager::cShaderProgram* shaderProg)
	{
		if (mSkybox == nullptr)
		{
			return;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glCullFace(GL_FRONT_AND_BACK);

		glUniform1f(shaderProg->getUniformLocID("useOffset"), (float)GL_FALSE);
		glUniform1f(shaderProg->getUniformLocID("isSkinnedMesh"), (float)GL_FALSE);
		//if texture binding needs to be moved do here

		sModelDrawInfo drawInfo;
		//if (pTheVAOManager->FindDrawInfoByModelName("bunny", drawInfo))
		if (!mVAOManager->FindDrawInfoByModelName(mSkybox->Model(), drawInfo))
		{
			return;
		}

		glm::mat4 matWorldCurrentGO = glm::translate(glm::mat4(1.f), mCamera->Position());
		glUniformMatrix4fv(shaderProg->getUniformLocID("matModel"), 1, GL_FALSE, glm::value_ptr(matWorldCurrentGO));

		glm::mat4 matModelInverseTranspose = glm::inverse(glm::transpose(matWorldCurrentGO));
		glUniformMatrix4fv(shaderProg->getUniformLocID("matModelInverseTranspose"), 1, GL_FALSE, glm::value_ptr(matModelInverseTranspose));

		glUniform4f(shaderProg->getUniformLocID("boolModifiers"),
			(float)ShaderMode::Skybox, 0, 0, 0);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_DEPTH);

		glBindVertexArray(drawInfo.VAO_ID);
		glDrawElements(GL_TRIANGLES,
					   drawInfo.numberOfIndices,
					   GL_UNSIGNED_INT,
					   0);
		glBindVertexArray(0);

	}

}
