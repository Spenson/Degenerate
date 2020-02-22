#pragma once


#include "iRenderComponent.h"
#include <string>
#include <vector>
#include "VAOManager/SkinnedMesh/cSkinnedMesh.h"


namespace DegenRendering
{
	static const int RIGID_MODEL_TEXTURES = 4;
	class iGeneralModel : public iRenderComponent
	{

	public:
		virtual ~iGeneralModel() = default;
		iGeneralModel() : iRenderComponent(eRendType::Model) {}

		virtual bool Visable() = 0;
		virtual bool Wireframe() = 0;
		virtual bool IgnoreLighting() = 0;

		virtual std::string Model() = 0;

		virtual glm::mat4 Transform() = 0;
		virtual glm::vec3 Scale() = 0;

		virtual bool UseDiffuse() = 0;
		virtual glm::vec4 Diffuse() = 0;
		virtual glm::vec4 Specular() = 0;

		virtual bool DepthBufferTest() = 0;
		virtual bool DepthBufferWrite() = 0;

		virtual std::pair<std::string, float>* Textures() = 0;//[RIGID_MODEL_TEXTURES];

		virtual std::vector<iGeneralModel*> Children() = 0;

		
		virtual bool IsSkinnedMesh() = 0;

		virtual cSkinnedMesh* Mesh() = 0;
		
		virtual std::string CurrentAnimation() = 0;
		virtual void CurrentAnimation(std::string name, bool lock) = 0;

		virtual void AnimationTimeStep(float dt) = 0;
		virtual float CurrentAnimationTime() = 0;
	};

};