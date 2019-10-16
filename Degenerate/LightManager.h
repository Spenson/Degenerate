#pragma once

#include "GLCommon.h"
#include "Light.h"
#include <vector>
#include <string>

class LightManager
{
public:

	struct ShaderLightUniformLocations
	{
		struct NameLocationPair
		{
			NameLocationPair(): location(-1){};
			GLint location;
			std::string name;
		};
		NameLocationPair Position;
		NameLocationPair Diffuse;
		NameLocationPair Specular;
		NameLocationPair Atten;
		NameLocationPair Direction;
		NameLocationPair Param1;
		NameLocationPair Param2;
	};

	//std::map<std::string, Light*> lights;

	LightManager();
	virtual ~LightManager();

	bool InitilizeLightUinformLocations(unsigned int shaderID, std::string lightArrayName,
								   unsigned int numberOfLights /*size of array*/,
								   std::string& errors);
	void PassLightsToShader();
	void GenerateLights(unsigned LightCount, bool resetCurrentLights);
	Light* GetLight(unsigned index);
	unsigned GetLightCount();
	void DeleteLights();

private:
	std::vector<Light*> vecLights;
	std::vector<ShaderLightUniformLocations> vecUniformLocations;
	
};
