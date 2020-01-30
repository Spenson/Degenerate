#pragma once
#include "iSkybox.h"


class cSimpleSkybox: public DegenRendering::iSkybox
{
public:
	virtual ~cSimpleSkybox();
	cSimpleSkybox();
	virtual bool RenderFirst() override;
	virtual std::string Model() override;
	virtual std::pair<std::string, float>* CubeMaps() override;

	std::pair<std::string, float> mCubeMaps[TEXTURE_COUNT];
	std::string mModel;
	bool mRenderFirst;
	
};
