#pragma once


#include <string>

namespace DegenRendering
{
	class iSkybox
	{
	public:
		virtual ~iSkybox() = default;

		static const int TEXTURE_COUNT = 4;
		
		virtual bool RenderFirst() = 0;
		virtual std::string Model() = 0;
		virtual std::pair<std::string, float>* CubeMaps() = 0;
	};
}
