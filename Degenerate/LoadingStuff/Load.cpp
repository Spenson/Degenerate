#include "Load.h"
#include "cJSONUtility.h"
#include "../GameObject/cPhysicsGameObject.h"

void LoadScene(std::string file, DegenRendering::cRenderer& renderer, DegenPhysics::iPhysicsWorld* &world, std::vector<cPhysicsGameObject*> &objects)
{
	if (DegenPhysics::PhysicsFactory == nullptr)
	{
		DegenPhysics::LoadPhysicsFactory("DegenBulletWrapper.dll");
	}

	rapidjson::Document document = DegenSerialize::cJSONUtility::open_document(file);

	if (document["Objects"].IsArray())
	{
		auto objectsArr = document["Objects"].GetArray();
		
		for(size_t i = 0; i < objectsArr.Size(); ++i)
		{
			cPhysicsGameObject* obj = new cPhysicsGameObject();
			rapidjson::Document temp;
			temp.CopyFrom(objectsArr[i], temp.GetAllocator());
			obj->deserialize(&temp);
			objects.push_back(obj);

		}
	}

	world = DegenPhysics::CreateWorld();

	for(size_t i = 0; i < objects.size();i++)
	{
		renderer.AddRenderComponent(objects[i]);
		world->AddObject(objects[i]->mPhysicsComponent);
	}
}
