#pragma once

#include "../GameObject/cGameObject.h"


struct sPair
{
	sPair() {};
	sPair(std::string stringData, glm::vec4 numData)
	{
		this->stringData = stringData;
		this->numData = numData;
	}
	sPair(std::string stringData)
	{
		this->stringData = stringData;
	}
	sPair(glm::vec4 numData)
	{
		this->numData = numData;
	}
	sPair(glm::vec3 numData)
	{
		this->numData = glm::vec4(numData, 1.0f);
	}
	sPair(float num)
	{
		this->numData.x = num;
	}
	std::string stringData;
	glm::vec4 numData;
};


class iCommand
{
public:
	virtual void SetName(std::string name) = 0;
	virtual bool IsDone() = 0;

	// Command Stuff
	virtual bool Update(double deltaTime) = 0;
	virtual void SetGameObject(cGameObject* pGO) = 0;
	virtual void Init(std::vector<sPair> vecDetails) = 0;

	// Command Group Stuff
	virtual void AddCommand(iCommand* command) = 0;
};
