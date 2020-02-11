#pragma once

#include "../GLCommon.h"

#include "iRenderComponent.h"
#include "iCamera.h"
#include "iLight.h"
#include "iRigidModel.h"
#include "iSkybox.h"


#include <string>


//potentially moved to cpp
#include "VAOManager/cVAOManager.h"
#include "Texture/cBasicTextureManager.h"
#include "ModelStuff/cModelLoader.h"
#include "Shaders/cShaderManager.h"



namespace DegenRendering
{
	class cRenderer
	{
		enum class ShaderMode
		{
			Object,
			Imposter,
			Skybox
		};
		
	public:
		static const unsigned int MAX_LIGHTS = 50;

		cRenderer();

		bool Initialize();

		void SetPerspectiveDetails(float fovy,float near, float far);


		void AddModel(const std::string& model, std::string path = "");
		void AddTexture(const std::string& texture, std::string path = "");
		void AddCubeMap(const std::string& name, const std::string& up, const std::string& down,
		                    const std::string& left, const std::string& right, const std::string& back,
		                    const std::string& front, std::string path = "");

		void SetCamera(iCamera* camera);
		void SetSkybox(iSkybox* skybox);
		bool AddRenderComponent(iRenderComponent* comp);
		bool RemoveRenderComponent(iRenderComponent* comp);
		bool AddLight(iLight* light);

		//void RenderSkybox();
		//void RenderScene(glm::mat4 view, glm::mat4 perspective, int width, int height);
		void RenderScene(const int& width, const int& height);
	protected:
		void SetUpTextureBindingsForObject(iRigidModel* pCurrentObject, cShaderManager::cShaderProgram* shaderProg);
		void DrawObject(glm::mat4 matModel, iRigidModel* pCurrentObject, cShaderManager::cShaderProgram* shaderProg);
		void SetUpTextureBindingsForSkybox(cShaderManager::cShaderProgram* shaderProg);
		void DrawSkybox(cShaderManager::cShaderProgram* shaderProg);
	private:
		std::vector<iRenderComponent*> mObjects;
		std::vector<iLight*> mLights;
		iCamera* mCamera;
		iSkybox* mSkybox;

		float mNearPlane;
		float mFarPlane;
		float mFOVY;
		
		static cBasicTextureManager* mTextureManager;
		static cModelLoader* mModelLoader;
		static cVAOManager* mVAOManager;
		static cShaderManager* mShaderManager;
	};

}