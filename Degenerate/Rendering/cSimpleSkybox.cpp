#include "cSimpleSkybox.h"

cSimpleSkybox::~cSimpleSkybox()
{
	delete[] mCubeMaps;
}

cSimpleSkybox::cSimpleSkybox(): mModel("sphere.ply"), mRenderFirst(true)
{
	mCubeMaps[0].first = "Skybox";
	mCubeMaps[0].second = 1.f;

	mCubeMaps[1].first = "";
	mCubeMaps[1].second = 0.f;

	mCubeMaps[2].first = "";
	mCubeMaps[2].second = 0.f;

	mCubeMaps[3].first = "";
	mCubeMaps[3].second = 0.f;

}

bool cSimpleSkybox::RenderFirst()
{
	return mRenderFirst;
}

std::string cSimpleSkybox::Model()
{
	return mModel;
}

std::pair<std::string, float>* cSimpleSkybox::CubeMaps()
{
	return mCubeMaps;
}
