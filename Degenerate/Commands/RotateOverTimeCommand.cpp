#include "RotateOverTimeCommand.h"


#include <iostream>


void RotateOverTimeCommand::SetName(std::string name)
{
	m_Name = name;
}

bool RotateOverTimeCommand::IsDone()
{
	return m_Done;
}

bool RotateOverTimeCommand::Update(double deltaTime)
{
	if (!m_HasUpdated)
	{
		if (!m_pGO)
		{
			std::cout << "Move Command: GameObject must be set before Update is called." << std::endl;
			return false;
		}
		
		m_pGO->setOrientation(m_StartQ);

		m_HasUpdated = true;
	}


	m_TimeElapsed += deltaTime;

	m_pGO->setOrientation(glm::slerp(m_StartQ, m_EndQ, (float)m_TimeElapsed / m_Time));

	if (m_TimeElapsed >= m_Time)
	{
		m_pGO->setOrientation(m_EndQ);
		m_Done = true;
		return false;
	}



	return true;



}

void RotateOverTimeCommand::SetGameObject(cGameObject* pGO)
{
	m_pGO = pGO;
}

void RotateOverTimeCommand::Init(std::vector<sPair> vecDetails)
{

	
	m_StartQ = glm::quat(glm::radians(glm::vec3(vecDetails[0].numData)));
	m_EndQ = glm::quat(glm::radians(glm::vec3(vecDetails[1].numData)));

	m_Time = vecDetails[2].numData.x;
	//m_AccelDis = vecDetails[1].numData.y;
	//m_DecelDis = vecDetails[1].numData.z;

}

void RotateOverTimeCommand::AddCommand(iCommand* command)
{
	std::cout << "Rotate Command Group does not accept other commands." << std::endl;
}
