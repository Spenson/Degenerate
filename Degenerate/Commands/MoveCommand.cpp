#include "MoveCommand.h"

#include <iostream>

void MoveCommand::SetName(std::string name)
{
	m_Name = name;
}

bool MoveCommand::IsDone()
{
	return m_Done;
}

bool MoveCommand::Update(double deltaTime)
{
	if (!m_HasUpdated)
	{
		if (!m_pGO)
		{
			std::cout << "Move Command: GameObject must be set before Update is called." << std::endl;
			return false;
		}

		m_Start = m_pGO->positionXYZ;
		m_HasUpdated = true;
	}

	glm::vec3 dir = glm::normalize(m_End - m_Start);

	if (glm::distance(m_pGO->positionXYZ, m_Start) < m_AccelDis)
	{
		float step = glm::smoothstep(0.0f, m_AccelDis, glm::distance(m_pGO->positionXYZ, m_Start));
		if(step < 0.05) step = 0.05;
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
	}


	return true;
}

void MoveCommand::SetGameObject(cGameObject* pGO)
{
	m_pGO = pGO;
}

void MoveCommand::Init(std::vector<sPair> vecDetails)
{
	m_End = glm::vec3(vecDetails[0].numData);
	m_MaxSpeed = vecDetails[1].numData.x;
	m_AccelDis = vecDetails[1].numData.y;
	m_DecelDis = vecDetails[1].numData.z;

}

void MoveCommand::AddCommand(iCommand* command)
{
	std::cout << "Move Command Group does not accept other commands." << std::endl;
}
