//#include "cBullet.h"
//
//cBullet::cBullet()
//{
//	mModel = "sphere_hires.ply";
//
//	mPos = glm::vec3(0.f);
//	mVel = glm::vec3(0.f);
//	mRot = glm::quat(glm::vec3(0.f));
//	mRotChange = 0.f;
//
//	mScale = 0.5f;
//	mUseDiffuse = true;
//	mDiffuse = glm::vec4(1.f);
//	mSpecular = glm::vec4(1.f);
//
//	mVisable = true;
//	mWireframe = false;
//	mIgnoreLighting = true;
//
//	mDepthBufferTest = true;
//	mDepthBufferWrite = true;
//
//	lifetime = 0.f;
//}
//
//void cBullet::SetTransform(const glm::mat4& transform) {}
//std::string cBullet::Model() { return this->mModel; }
//
//glm::mat4 cBullet::Transform()
//{
//	glm::mat4 transform(1.f);
//	transform = glm::translate(transform, this->mPos);
//	transform *= glm::mat4(this->mRot);
//	return transform;
//}
//
//glm::vec3 cBullet::Scale() { return glm::vec3(this->mScale); }
//glm::vec4 cBullet::Diffuse() { return this->mDiffuse; }
//glm::vec4 cBullet::Specular() { return this->mSpecular; }
//bool cBullet::Visable() { return this->mVisable; }
//bool cBullet::Wireframe() { return this->mWireframe; }
//bool cBullet::IgnoreLighting() { return this->mIgnoreLighting; }
//bool cBullet::UseDiffuse() { return this->mUseDiffuse; }
//bool cBullet::DepthBufferTest() { return this->mDepthBufferTest; }
//bool cBullet::DepthBufferWrite() { return this->mDepthBufferWrite; }
//std::pair<std::string, float>* cBullet::Textures() { return this->mTextures; }
//std::vector<DegenRendering::iRigidModel*> cBullet::Children() { return this->mChildren; }
//
//glm::vec3 cBullet::Position() { return mPos; }
//glm::vec3 cBullet::Velocity() { return mVel; }
//void cBullet::Velocity(glm::vec3 velocity) { mVel = velocity; }
//glm::quat cBullet::Rotation() { return mRot; }
//float cBullet::Mass() { return 1.0f; }
//float cBullet::MaxVelocity() { return 2.0f; }
//float cBullet::MaxForce() { return 2.0f; }
//float cBullet::MaxSpeed() { return 5.0f; }
//
//void cBullet::Rotation(glm::quat rotation)
//{
//	this->mRot = rotation;
//}
//
//void cBullet::Action()
//{
//}
//
//void cBullet::Diffuse(glm::vec4 diffuse)
//{
//}
