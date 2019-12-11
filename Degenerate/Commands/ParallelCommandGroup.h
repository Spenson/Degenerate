#pragma once
#include "iCommand.h"

class ParallelCommandGroup : public iCommand
{
	std::string m_Name;
	std::vector<iCommand*> m_Commands;
public:
	// Inherited via iCommand
	ParallelCommandGroup(std::string name): m_Name(name) {}

	virtual void SetName(std::string name) override;
	virtual bool Update(double deltaTime) override;
	virtual void SetGameObject(cGameObject* pGO) override;
	virtual void Init(std::vector<sPair> vecDetails) override;
	virtual void AddCommand(iCommand* command) override;

	// Inherited via iCommand
	virtual bool IsDone() override;
};