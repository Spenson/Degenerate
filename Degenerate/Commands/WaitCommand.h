#pragma once

#include "iCommand.h"


class WaitCommand : public iCommand
{
	std::string m_Name;
	float m_Time;
	float m_TimeElapsed;
	bool m_Done;

public:
	WaitCommand(std::string name): m_Name(name), m_Time(0), m_TimeElapsed(0), m_Done(false){}
	virtual void SetName(std::string name) override;
	virtual bool IsDone() override;
	virtual bool Update(double deltaTime) override;
	virtual void SetGameObject(cGameObject* pGO) override;
	virtual void Init(std::vector<sPair> vecDetails) override;
	virtual void AddCommand(iCommand* command) override;
};