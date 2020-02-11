//#include "cShip.h"
//
//
//cBullet* Shoot(glm::quat rot, glm::vec3 pos, float& lastShot, std::vector<cBullet*> bullets)
//{
//	if (glfwGetTime() - lastShot > 1)
//	{
//		cBullet* bullet = new cBullet();
//		bullet->mVel = rot * glm::vec3(0.f, 0.f, 10.f);
//		bullet->mPos = pos + (bullet->mVel / 2.f);
//
//		lastShot = glfwGetTime();
//
//		bullets.push_back(bullet);
//		//g_Renderer.AddRenderComponent(bullet);
//
//		return bullet;
//	}
//	return nullptr;
//}
//
//cShip::cShip()
//{
//	mModel = "EnemyShip.ply";
//
//	mPos = glm::vec3(0.f);
//	mVel = glm::vec3(0.f);
//	mRot = glm::quat(glm::vec3(0.f));
//	mRotChange = 0.f;
//
//	mScale = 1.f;
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
//}
//
//void cShip::SetTransform(const glm::mat4& transform)
//{
//}
//
//std::string cShip::Model() { return this->mModel; }
//
//glm::mat4 cShip::Transform()
//{
//	glm::mat4 transform(1.f);
//	transform = glm::translate(transform, this->mPos);
//	transform *= glm::mat4(this->mRot);
//	return transform;
//}
//
//glm::vec3 cShip::Scale()		{ return glm::vec3(this->mScale); }
//glm::vec4 cShip::Diffuse()		{ return this->mDiffuse; }
//glm::vec4 cShip::Specular()		{ return this->mSpecular; }
//bool cShip::Visable()			{ return this->mVisable; }
//bool cShip::Wireframe()			{ return this->mWireframe; }
//bool cShip::IgnoreLighting()	{ return this->mIgnoreLighting; }
//bool cShip::UseDiffuse()		{ return this->mUseDiffuse; }
//bool cShip::DepthBufferTest()	{ return this->mDepthBufferTest; }
//bool cShip::DepthBufferWrite()	{ return this->mDepthBufferWrite; }
//std::pair<std::string, float>* cShip::Textures() { return this->mTextures; }
//std::vector<DegenRendering::iRigidModel*> cShip::Children() { return this->mChildren; }
//
//glm::vec3 cShip::Position()	{ return mPos; }
//glm::vec3 cShip::Velocity()	{ return mVel; }
//glm::quat cShip::Rotation()	{ return mRot; }
//float cShip::Mass()			{ return 1.0f; }
//float cShip::MaxVelocity()	{ return 6.0f; }
//float cShip::MaxForce()		{ return 2.0f; }
//float cShip::MaxSpeed()		{ return 6.0f; }
//void cShip::Velocity(glm::vec3 velocity) { mVel = velocity; }
//void cShip::Rotation(glm::quat rotation) { this->mRot = rotation; }
//
//void cShip::Action()
//{
//	Shoot(this->mRot, this->mPos, this->lastshot);
//}
//
//void cShip::Diffuse(glm::vec4 diffuse)
//{
//	mDiffuse = diffuse;
//}
