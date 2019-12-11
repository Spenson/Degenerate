#pragma once

#include "iCommand.h"


class LocationTrigger : public iCommand
{
	std::string m_Name;
	cGameObject* m_pGO;

	glm::vec3 Position;

	float deviance;

	bool m_Done;

public:
	LocationTrigger(std::string name) : m_Name(name), m_Done(false), m_pGO(nullptr), deviance(5.0) {}
	// Inherited via iCommand
	virtual void SetName(std::string name) override;
	virtual bool IsDone() override;
	virtual bool Update(double deltaTime) override;
	virtual void SetGameObject(cGameObject* pGO) override;
	virtual void Init(std::vector<sPair> vecDetails) override;
	virtual void AddCommand(iCommand* command) override;
};