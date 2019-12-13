#include "WaitCommand.h"

void WaitCommand::SetName(std::string name)
{
	m_Name = name;
}

bool WaitCommand::IsDone()
{
	return m_Done;
}

bool WaitCommand::Update(double deltaTime)
{
	m_TimeElapsed += deltaTime;
	if (m_TimeElapsed >= m_Time)
	{
		m_Done = true;
		return false;
	}
	return true;
}

void WaitCommand::SetGameObject(cGameObject* pGO)
{
}

void WaitCommand::Init(std::vector<sPair> vecDetails)
{
	m_Time = vecDetails[0].numData.x;
}

void WaitCommand::AddCommand(iCommand* command)
{
}
