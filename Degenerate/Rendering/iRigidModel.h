#pragma once


#include "iRenderComponent.h"
#include <string>
#include <vector>


namespace DegenRendering
{
	static const int RIGID_MODEL_TEXTURES = 4;
	class iRigidModel : public iRenderComponent
	{

	public:
		virtual ~iRigidModel() = default;
		iRigidModel() : iRenderComponent(eType::RigidModel) {}

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

		virtual std::vector<iRigidModel*> Children() = 0;

	};

};