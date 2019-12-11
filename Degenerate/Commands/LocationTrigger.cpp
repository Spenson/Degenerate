#include "LocationTrigger.h"

void LocationTrigger::SetName(std::string name)
{
	m_Name = name;
}

bool LocationTrigger::IsDone()
{
	return m_Done;
}

bool LocationTrigger::Update(double deltaTime)
{
	if (glm::distance(m_pGO->positionXYZ, Position) <= deviance)
	{
		m_Done = true;
		return false;
	}

	return true;
}

void LocationTrigger::SetGameObject(cGameObject* pGO)
{
	m_pGO = pGO;
}

void LocationTrigger::Init(std::vector<sPair> vecDetails)
{
	Position = vecDetails[0].numData;
	deviance = vecDetails[1].numData.x;
}

void LocationTrigger::AddCommand(iCommand* command)
{
}
