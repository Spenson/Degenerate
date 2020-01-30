#include "LightManager.h"

#include <sstream>
#include <glm/gtx/quaternion.hpp>

LightManager* g_pLightManager = nullptr;


LightManager::LightManager(): LastIndex(0), Ambient(0.1f)
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

bool LightManager::InitilizeLightUinformLocations(unsigned int shaderID, std::string lightArrayName, unsigned int numberOfLights, std::string& errors)
{
	bool bError = false;
	std::stringstream streamErrors;
	this->vecUniformLocations.clear();


	UL_Ambient.name = "Ambient";
	bError = GetUniforHelper(shaderID, UL_Ambient, streamErrors);

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

		this->vecUniformLocations.push_back(curLightUniforms);
	}
	errors = streamErrors.str();
	return !bError;
}

void LightManager::PassLightsToShader()
{
	//fail if there are too many lights for the locations
	if (vecLights.size() > vecUniformLocations.size())
		return;

	glUniform1f(UL_Ambient.location, Ambient); 

	// pass all lights to shader
	for (unsigned index = 0; index < vecLights.size(); index++)
	{
		Light* curLight = this->vecLights[index];
		ShaderLightUniformLocations& curUniLocs = this->vecUniformLocations[index];
		if (curLight->isLightOn)
		{

			glm::vec3 pos = curLight->matrix * glm::vec4(curLight->Position, 1.0f);

			
			glUniform4f(curUniLocs.Position.location,
						pos.x,
						pos.y,
						pos.z,
						1.0f); // currently unused

			glUniform4f(curUniLocs.Diffuse.location,
						curLight->Diffuse.r,
						curLight->Diffuse.g,
						curLight->Diffuse.b,
						1.0f); // currently unused

			glUniform4f(curUniLocs.Specular.location,
						curLight->Specular.r,
						curLight->Specular.g,
						curLight->Specular.b,
						curLight->Specular.a);

			glUniform4f(curUniLocs.Atten.location,
						curLight->ConstAtten,
						curLight->LinearAtten,
						curLight->QuadraticAtten,
						curLight->CutOffDistance);


			/*glm::vec3 EulerAngleRadians;
			EulerAngleRadians.x = glm::radians(curLight->Rotation.x);
			EulerAngleRadians.y = glm::radians(curLight->Rotation.y);
			EulerAngleRadians.z = glm::radians(curLight->Rotation.z);

			glm::quat angleChange = glm::quat(EulerAngleRadians);
			glm::mat4 matRotation = glm::mat4(angleChange);



			glm::vec4 dir = (matRotation * glm::vec4(glm::normalize(curLight->Direction), 1.0f));*/

			glm::vec4 dir = glm::inverse(glm::transpose(curLight->matrix)) * glm::vec4(curLight->Direction, 1.0f);


			glUniform4f(curUniLocs.Direction.location,
						dir.x,
						dir.y,
						dir.z,
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
		for (size_t index = vecLights.size(); index < vecUniformLocations.size(); index++)
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
		for (size_t i = vecLights.size(); i < LightCount; i++)
		{
			vecLights.push_back(new Light());
		}
	}
	else if (LightCount < vecLights.size())
	{
		for (; vecLights.size() > LightCount;)
		{
			delete this->vecLights[vecLights.size()-1];
			vecLights.pop_back();
		}
	}

}

void LightManager::GenerateLights(std::vector<Light*> vecLights)
{
	DeleteLights();
	this->vecLights = vecLights;
}

Light* LightManager::GetLight(unsigned index)
{
	if (index >= vecLights.size())
		return nullptr;
	LastIndex = index;
	return this->vecLights[LastIndex];
}

Light* LightManager::GetLastLight()
{
	return this->vecLights[LastIndex];
}

size_t LightManager::GetLightCount()
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

void LightManager::SetAmbient(float a)
{
	Ambient = a;
}
