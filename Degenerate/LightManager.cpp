#include "LightManager.h"

#include <sstream>

LightManager::LightManager()
{
}

LightManager::~LightManager()
{
	this->DeleteLights();
}


bool GetUniforHelper(GLint shaderID, LightManager::ShaderLightUniformLocations::NameLocationPair& nameLocPair, std::stringstream& streamErrors)
{
	nameLocPair.location = glGetUniformLocation(shaderID, nameLocPair.name.c_str());
	if (nameLocPair.location == -1)
	{
		streamErrors << "Didn't find " << nameLocPair.name << std::endl;
		return true;
	}
	return false;
}

bool LightManager::InitilizeLightUinforLocations(unsigned int shaderID, std::string lightArrayName, unsigned int numberOfLights, std::string& errors)
{
	bool bError = false;
	std::stringstream streamErrors;
	this->vecUniformLocations.clear();

	for (unsigned int index = 0; index != numberOfLights; index++)
	{
		std::stringstream ssLightPrefix;
		ssLightPrefix << lightArrayName << "[" << index << "].";
		ShaderLightUniformLocations curLightUniforms;

		curLightUniforms.Position.name = ssLightPrefix.str() + "position";
		curLightUniforms.Direction.name = ssLightPrefix.str() + "direction";
		curLightUniforms.Diffuse.name = ssLightPrefix.str() + "diffuse";
		curLightUniforms.Specular.name = ssLightPrefix.str() + "specular";
		curLightUniforms.Atten.name = ssLightPrefix.str() + "atten";
		curLightUniforms.Param1.name = ssLightPrefix.str() + "param1";
		curLightUniforms.Param2.name = ssLightPrefix.str() + "param2";

		bError |= GetUniforHelper(shaderID, curLightUniforms.Position, streamErrors);
		bError |= GetUniforHelper(shaderID, curLightUniforms.Direction, streamErrors);
		bError |= GetUniforHelper(shaderID, curLightUniforms.Diffuse, streamErrors);
		bError |= GetUniforHelper(shaderID, curLightUniforms.Specular, streamErrors);
		bError |= GetUniforHelper(shaderID, curLightUniforms.Atten, streamErrors);
		bError |= GetUniforHelper(shaderID, curLightUniforms.Param1, streamErrors);
		bError |= GetUniforHelper(shaderID, curLightUniforms.Param2, streamErrors);
	}
	return !bError;
}

void LightManager::PassLightsToShader()
{
	//fail if there are too many lights for the locations
	if (vecLights.size() > vecUniformLocations.size())
		return;

	// pass all lights to shader
	for (unsigned index = 0; index < vecLights.size(); index++)
	{
		Light* curLight = this->vecLights[index];
		ShaderLightUniformLocations& curUniLocs = this->vecUniformLocations[index];
		if (curLight->isLightOn)
		{
			glUniform4f(curUniLocs.Position.location,
						curLight->Position.x,
						curLight->Position.y,
						curLight->Position.z,
						1.0f); // currently unused

			glUniform4f(curUniLocs.Diffuse.location,
						curLight->Diffuse.r,
						curLight->Diffuse.g,
						curLight->Diffuse.b,
						1.0f); // currently unused

			glUniform4f(curUniLocs.Specular.location,
						1.0f, 1.0f, 1.0f, 0.1f); //to be moved to object

			glUniform4f(curUniLocs.Atten.location,
						curLight->ConstAtten,
						curLight->LinearAtten,
						curLight->QuadraticAtten,
						curLight->CutOffDistance);

			glUniform4f(curUniLocs.Direction.location,
						curLight->Direction.x,
						curLight->Direction.y,
						curLight->Direction.z,
						1.0f);	// currently unused

			float curlightType = 0.0f; //defualt point light
			switch (curLight->lightType)
			{
				case Light::SPOT_LIGHT:
					curlightType = 1.0f;
					break;
				case Light::DIRECTIONAL_LIGHT:
					curlightType = 2.0f;
					break;
			}

			glUniform4f(curUniLocs.Param1.location,
						curlightType, 
						curLight->SpotInnerAngle, 
						curLight->SpotOuterAngle,
						1.0f);	// currently unused

			glUniform4f(curUniLocs.Param2.location,
						1.0f,	// on
						1.0f, 1.0f, 1.0f);	// currently unused
		}
		else
		{
			glUniform4f(curUniLocs.Param2.location,
						0.0f,	// off
						1.0f, 1.0f, 1.0f);	// currently unused
		}
	}

	//fill excess locations with turned off lights
	if (vecLights.size() < vecUniformLocations.size())
	{
		for (unsigned index = vecLights.size(); index < vecUniformLocations.size(); index++)
		{
			ShaderLightUniformLocations& curUniLocs = this->vecUniformLocations[index];
			glUniform4f(curUniLocs.Param2.location,
						0.0f,	// off
						1.0f, 1.0f, 1.0f);	// currently unused
		}
	}

}

void LightManager::GenerateLights(unsigned LightCount, bool resetExistingLights)
{
	if (vecLights.size() != 0 && resetExistingLights)
		DeleteLights();

	else if (LightCount > vecLights.size())
	{
		for (unsigned i = vecLights.size(); i < LightCount; i++)
		{
			vecLights.push_back(new Light());
		}
	}
	else if (LightCount < vecLights.size())
	{
		for (; vecLights.size() > LightCount;)
		{
			vecLights.pop_back();
		}
	}

}

Light* LightManager::GetLight(unsigned index)
{
	if (index >= vecLights.size())
		return nullptr;
	return this->vecLights[index];
}

unsigned LightManager::GetLightCount()
{
	return vecLights.size();
}

void LightManager::DeleteLights()
{
	for (unsigned int index = 0; index != this->vecLights.size(); index++)
	{
		delete this->vecLights[index];
	}
	this->vecLights.clear();

	return;
}
