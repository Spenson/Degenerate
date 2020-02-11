#pragma once
#include "../Rendering/iRigidModel.h"
#include "physics/interfaces/iPhysicsFactory.h"
#include "../LoadingStuff/iSerializable.h"


class cPhysicsGameObject : public DegenRendering::iRigidModel, public DegenSerialize::iSerializable
{
public:
	cPhysicsGameObject();
	
	void SetTransform(const glm::mat4& transform) override;
	bool Visable() override;
	bool Wireframe() override;
	bool IgnoreLighting() override;
	std::string Model() override;
	glm::mat4 Transform() override;
	glm::vec3 Scale() override;
	bool UseDiffuse() override;
	glm::vec4 Diffuse() override;
	glm::vec4 Specular() override;
	bool DepthBufferTest() override;
	bool DepthBufferWrite() override;
	std::pair<std::string, float>* Textures() override;
	std::vector<iRigidModel*> Children() override;

	bool deserialize(rapidjson::Document* document) override;

	
	DegenPhysics::iPhysicsComponent* mPhysicsComponent;

	std::string mModel;
	
	float mScale;
	bool mUseDiffuse;
	glm::vec4 mDiffuse;
	glm::vec4 mSpecular;

	bool mVisable;
	bool mWireframe;
	bool mIgnoreLighting;

	bool mDepthBufferTest;
	bool mDepthBufferWrite;

	glm::mat4 mTransform;

	std::pair<std::string, float> mTextures[DegenRendering::RIGID_MODEL_TEXTURES];

	std::vector<iRigidModel*> mChildren;
	
};
