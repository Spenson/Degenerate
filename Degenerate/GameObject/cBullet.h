//#pragma once
//#include "../Rendering/iRigidModel.h"
//#include "../AI/iEntity.h"
//
//class cBullet: public DegenRendering::iRigidModel, public DegenBehaviours::iEntity
//{
//public:
//	cBullet();
//	
//	void SetTransform(const glm::mat4& transform) override;
//	
//	bool Visable() override;
//	bool Wireframe() override;
//	bool IgnoreLighting() override;
//	std::string Model() override;
//	glm::mat4 Transform() override;
//	glm::vec3 Scale() override;
//	bool UseDiffuse() override;
//	glm::vec4 Diffuse() override;
//	glm::vec4 Specular() override;
//	bool DepthBufferTest() override;
//	bool DepthBufferWrite() override;
//	std::pair<std::string, float>* Textures() override;
//	std::vector<iRigidModel*> Children() override;
//
//	
//	glm::vec3 Position() override;
//	glm::vec3 Velocity() override;
//	glm::quat Rotation() override;
//	void Velocity(glm::vec3 velocity) override;
//	float Mass() override;
//	float MaxVelocity() override;
//	float MaxForce() override;
//	float MaxSpeed() override;
//
//	void Rotation(glm::quat rotation) override;
//	void Action() override;
//
//	void Diffuse(glm::vec4 diffuse) override;
//	float lifetime;
//	
//	std::string mModel;
//
//	glm::vec3 mPos;
//	glm::vec3 mVel;
//	glm::quat mRot;
//	float mRotChange;
//
//	float mScale;
//	bool mUseDiffuse;
//	glm::vec4 mDiffuse;
//	glm::vec4 mSpecular;
//
//	bool mVisable;
//	bool mWireframe;
//	bool mIgnoreLighting;
//
//	bool mDepthBufferTest;
//	bool mDepthBufferWrite;
//
//	std::pair<std::string, float> mTextures[DegenRendering::RIGID_MODEL_TEXTURES];
//
//	std::vector<iRigidModel*> mChildren;
//	
//};
