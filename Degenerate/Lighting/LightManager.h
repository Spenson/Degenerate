#pragma once

#include "../GLCommon.h"
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
	void GenerateLights(std::vector<Light*> vecLights);
	Light* GetLight(unsigned index);
	Light* GetLastLight();
	size_t GetLightCount();
	void DeleteLights();
	void SetAmbient(float a);

private:
	std::vector<Light*> vecLights;
	std::vector<ShaderLightUniformLocations> vecUniformLocations;
	ShaderLightUniformLocations::NameLocationPair UL_Ambient;
	unsigned LastIndex;
	float Ambient;
};

