#include "cPhysicsGameObject.h"
#include "physics/interfaces/iSphereComponent.h"
#include "physics/interfaces/iPlaneComponent.h"

#include "../Physics/Physics.h"

cPhysicsGameObject::cPhysicsGameObject()
{
	this->mPhysicsComponent = nullptr;

	this->mModel = "sphere_hires.ply";

	this->mScale = 1.f;
	this->mUseDiffuse = true;
	this->mDiffuse = glm::vec4(1.f);;
	this->mSpecular = glm::vec4(1.f);;

	this->mVisable = true;
	this->mWireframe = false;
	this->mIgnoreLighting = true;

	this->mDepthBufferTest = true;
	this->mDepthBufferWrite = true;

	mTransform =glm::mat4(1.f);

	mTextures[0].first = "gridtexture.bmp";
	mTextures[0].second = 1.f;
	mTextures[1].first = "";
	mTextures[1].second = 0.f;
	mTextures[2].first = "";
	mTextures[2].second = 0.f;
	mTextures[3].first = "";
	mTextures[3].second = 0.f;

}

void cPhysicsGameObject::SetTransform(const glm::mat4& transform)
{

}

bool cPhysicsGameObject::Visable()
{
	return this->mVisable;
}

bool cPhysicsGameObject::Wireframe()
{
	return this->mWireframe;
}

bool cPhysicsGameObject::IgnoreLighting()
{
	return this->mIgnoreLighting;
}

std::string cPhysicsGameObject::Model()
{
	return this->mModel;
}

glm::mat4 cPhysicsGameObject::Transform()
{
	this->mPhysicsComponent->GetTransform(this->mTransform);
	return this->mTransform;
}

glm::vec3 cPhysicsGameObject::Scale()
{
	return glm::vec3(this->mScale);
}

bool cPhysicsGameObject::UseDiffuse()
{
	return this->mUseDiffuse;
}

glm::vec4 cPhysicsGameObject::Diffuse()
{
	return this->mDiffuse;
}

glm::vec4 cPhysicsGameObject::Specular()
{
	return this->mSpecular;
}

bool cPhysicsGameObject::DepthBufferTest()
{
	return this->mDepthBufferTest;
}

bool cPhysicsGameObject::DepthBufferWrite()
{
	return this->mDepthBufferWrite;
}

std::pair<std::string, float>* cPhysicsGameObject::Textures()
{
	return this->mTextures;
}

std::vector<DegenRendering::iRigidModel*> cPhysicsGameObject::Children()
{
	return this->mChildren;
}

bool cPhysicsGameObject::deserialize(rapidjson::Document* document)
{
	const auto& doc = *document;

	if (doc["Model"].IsString())
		mModel = doc["Model"].GetString();

	if (doc["Scale"].IsFloat())
		mScale = doc["Scale"].GetFloat();

	if (doc["UseDiffuse"].IsBool())
		mUseDiffuse = doc["UseDiffuse"].GetBool();

	if (doc["Diffuse"].IsArray() && doc["Diffuse"].Size() == 4)
		mDiffuse = glm::vec4(doc["Diffuse"][0].GetFloat(),
							 doc["Diffuse"][1].GetFloat(),
							 doc["Diffuse"][2].GetFloat(),
							 doc["Diffuse"][3].GetFloat());

	if (doc["Specular"].IsArray() && doc["Specular"].Size() == 4)
		mSpecular = glm::vec4(doc["Specular"][0].GetFloat(),
							  doc["Specular"][1].GetFloat(),
							  doc["Specular"][2].GetFloat(),
							  doc["Specular"][3].GetFloat());

	if (doc["Visable"].IsBool())
		mVisable = doc["Visable"].GetBool();


	if (doc["Wireframe"].IsBool())
		mWireframe = doc["Wireframe"].GetBool();

	if (doc["IgnoreLighting"].IsBool())
		mIgnoreLighting = doc["IgnoreLighting"].GetBool();


	if (doc["DepthBufferTest"].IsBool())
		mDepthBufferTest = doc["DepthBufferTest"].GetBool();

	if (doc["DepthBufferWrite"].IsBool())
		mDepthBufferWrite = doc["DepthBufferWrite"].GetBool();

	if (doc["Textures"].IsArray() && doc["Textures"].Size() == 4)
	{
		mTextures[0].first = doc["Textures"][0][0].GetString();
		mTextures[0].second = doc["Textures"][0][1].GetFloat();

		mTextures[1].first = doc["Textures"][1][0].GetString();
		mTextures[1].second = doc["Textures"][1][1].GetFloat();

		mTextures[2].first = doc["Textures"][2][0].GetString();
		mTextures[2].second = doc["Textures"][2][1].GetFloat();

		mTextures[3].first = doc["Textures"][3][0].GetString();
		mTextures[3].second = doc["Textures"][3][1].GetFloat();
	}

	if (doc["PhysicsComponent"].IsObject())
	{
		const auto& physics = doc["PhysicsComponent"].GetObject();
		if (std::strcmp(physics["Type"].GetString(), "sphere") == 0)
		{
			DegenPhysics::sSphereDef def;

			def.Radius = physics["Radius"].GetFloat();
			def.Mass = physics["Mass"].GetFloat();

			def.Position = glm::vec3(physics["Position"][0].GetFloat(),
									 physics["Position"][1].GetFloat(),
									 physics["Position"][2].GetFloat());

			def.Velocity = glm::vec3(physics["Velocity"][0].GetFloat(),
									 physics["Velocity"][1].GetFloat(),
									 physics["Velocity"][2].GetFloat());

			def.Acceleration = glm::vec3(physics["Acceleration"][0].GetFloat(),
										 physics["Acceleration"][1].GetFloat(),
										 physics["Acceleration"][2].GetFloat());


			mPhysicsComponent = DegenPhysics::CreateObject(def);
		}
		else if (std::strcmp(physics["Type"].GetString(), "plane") == 0)
		{
			DegenPhysics::sPlaneDef def;
			def.Normal = glm::vec3(physics["Normal"][0].GetFloat(),
								   physics["Normal"][1].GetFloat(),
								   physics["Normal"][2].GetFloat());

			def.Constant = physics["Constant"].GetFloat();

			mPhysicsComponent = DegenPhysics::CreateObject(def);
		}
		else
		{
			return false;
		}
		
	}
	return true;
}
