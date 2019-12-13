#include "MoveOverTimeCommand.h"

#include <iostream>

void MoveOverTimeCommand::SetName(std::string name)
{
	m_Name = name;
}

bool MoveOverTimeCommand::IsDone()
{
	return m_Done;
}

bool MoveOverTimeCommand::Update(double deltaTime)
{
	if (!m_HasUpdated)
	{
		m_pGO->positionXYZ = m_Start;
		m_HasUpdated = true;
	}
	m_TimeElapsed += deltaTime;

	m_pGO->positionXYZ = m_Start +  ((m_End-m_Start)*(m_TimeElapsed/m_Time));

	if (m_TimeElapsed >= m_Time)
	{
		m_pGO->positionXYZ = m_End;
		m_Done = true;
		return false;
	}

	/*glm::vec3 dir = glm::normalize(m_End - m_Start);

	if (glm::distance(m_pGO->positionXYZ, m_Start) < m_AccelDis)
	{
		float step = glm::smoothstep(0.0f, m_AccelDis, glm::distance(m_pGO->positionXYZ, m_Start));
		if (step < 0.05) step = 0.05;
		m_pGO->velocity = dir * (m_MaxSpeed * step);
	}
	else if (glm::distance(m_pGO->positionXYZ, m_End) < m_DecelDis)
	{
		float step = glm::smoothstep(0.0f, m_DecelDis, glm::distance(m_pGO->positionXYZ, m_End));
		if (step < 0.05) step = 0.05;
		m_pGO->velocity = dir * (m_MaxSpeed * step);
	}
	else
	{
		m_pGO->velocity = dir * m_MaxSpeed;
	}

	if (glm::distance(m_pGO->positionXYZ, m_End) < 0.05 || glm::distance(m_pGO->positionXYZ, m_Start) > glm::distance(m_Start, m_End))
	{
		m_pGO->velocity = glm::vec3(0.0f);
		m_pGO->positionXYZ = m_End;
		m_Done = true;
		return false;
	}*/


	return true;
}

void MoveOverTimeCommand::SetGameObject(cGameObject* pGO)
{
	m_pGO = pGO;
}

void MoveOverTimeCommand::Init(std::vector<sPair> vecDetails)
{
	m_Start = glm::vec3(vecDetails[0].numData);
	m_End = glm::vec3(vecDetails[1].numData);
	m_Time = vecDetails[2].numData.x;

}

void MoveOverTimeCommand::AddCommand(iCommand* command)
{
	std::cout << "Move Command Group does not accept other commands." << std::endl;
}
