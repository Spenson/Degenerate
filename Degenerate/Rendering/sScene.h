#pragma once
#include <vector>
#include "iGeneralModel.h"
#include "iCamera.h"
#include "iLight.h"
#include "iSkybox.h"
#include "FBO/cFBO.h"


namespace DegenRendering
{
struct sScene
{
	std::vector<iGeneralModel*> objects;
	iCamera* camera = nullptr;
	int width = 0, height = 0;
	
	std::vector<iLight*> mLights;
	iSkybox* mSkybox = nullptr;
	cFBO* mFBO = nullptr;

	float mNearPlane = 1.f;
	float mFarPlane = 1000.f;
	float mFOVY = 0.8f;
};

}