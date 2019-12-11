#include "RotateCommand.h"

#include <iostream>


void RotateCommand::SetName(std::string name)
{
	m_Name = name;
}

bool RotateCommand::IsDone()
{
	return m_Done;
}

bool RotateCommand::Update(double deltaTime)
{
	if (!m_HasUpdated)
	{
		if (!m_pGO)
		{
			std::cout << "Move Command: GameObject must be set before Update is called." << std::endl;
			return false;
		}
		m_Start = this->m_pGO->getEulerAngle();
		m_StartQ = m_pGO->getQOrientation();

		m_HasUpdated = true;
	}


	timePassed += deltaTime;

	/*
	
	
	

		NOTHING ELSE WORKED BECAUSE OF THE DRIFT WITH QUATERNIONS!!!!!!!!!!!!!
	
	
	
	
	*/

	m_pGO->setOrientation(glm::slerp(m_StartQ, m_EndQ, glm::radians(m_MaxSpeed) * (float)timePassed));

	if (glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_End) < 0.1f || glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_Start) > glm::distance(m_Start, m_End))
	{
		m_pGO->setOrientation(m_EndQ);

		m_Done = true;
		return false;
	}



	return true;












	//m_pGO->updateOrientation(glm::normalize( glm::slerp(glm::normalize(m_Start), glm::normalize(glm::inverse(m_End)), (1/m_MaxSpeed) * (float)deltaTime)));

	//bool x = false,y = false,z = false;

	/*glm::vec3 cur = this->m_pGO->getEulerAngle();

	glm::quat curAngle(glm::vec3(0.0f));

	if (abs(m_End.x - cur.x) > 0.5)
	{
		curAngle *= glm::slerp(m_Start, glm::inverse(m_TargetX), (1 / m_MaxSpeed) * (float)timePassed);
	}
	else
	{
		m_TargetX = glm::quat(glm::vec3(0.0f));
		bool x = true;
	}

	if (abs(m_End.y - cur.y) > 0.5)
	{
		curAngle *= glm::slerp(m_Start, m_TargetY, (1 / m_MaxSpeed) * (float)timePassed);
	}
	else
	{
		m_TargetY = glm::quat(glm::vec3(0.0f));
		bool y = true;
	}

	if (abs(m_End.z - cur.z) > 0.5)
	{
		m_TargetZ = glm::quat(glm::vec3(0.0f));
		curAngle *= glm::slerp(m_Start, m_TargetZ, (1 / m_MaxSpeed) * (float)timePassed);
	}
	else
	{
		bool z = true;
	}

	if (x && y && z)
	{
		m_Done = true;
		return false;
	}

	m_pGO->setOrientation(curAngle);*/


	//float test = glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_End);


	//if (glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_Start) < m_AccelDis)
	//{
	//	float step = glm::smoothstep(0.0f, m_AccelDis, glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_Start));
	//	if (step < 0.05) step = 0.05;
	//	glm::vec3 rot = dir * (m_MaxSpeed * step);
	//	m_pGO->setAngularVelocity(rot);
	//}
	//else if (glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_End) < m_DecelDis)
	//{
	//	//currently not working
	//	float step = glm::smoothstep(0.0f, m_DecelDis, glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_End));
	//	if (step < 0.05) step = 0.05;
	//	glm::vec3 rot = dir * (m_MaxSpeed * step);
	//	m_pGO->setAngularVelocity(rot);
	//}
	//else
	//{
	//	glm::vec3 rot = dir * m_MaxSpeed;
	//	m_pGO->setAngularVelocity(rot);
	//}

	//if (glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_End) < 0.1f || glm::distance(glm::degrees(m_pGO->getEulerAngle()), m_Start) > glm::distance(m_Start, m_End))
	//{
	//	m_pGO->setAngularVelocity(glm::vec3(0.0f));
	//	//m_pGO->positionXYZ = m_End;
	//	m_Done = true;
	//	return false;
	//}
	//glm::quat qCurrentRotation = glm::lerp(this->m_Start, this->m_End, 1/m_MaxSpeed);

	//m_pGO->setAngularVelocity();

}

void RotateCommand::SetGameObject(cGameObject* pGO)
{
	m_pGO = pGO;
}

void RotateCommand::Init(std::vector<sPair> vecDetails)
{

	m_End = glm::vec3(vecDetails[0].numData);

	m_EndQ = glm::quat(glm::radians( glm::vec3(vecDetails[0].numData)));

	m_MaxSpeed = vecDetails[1].numData.x;
	//m_AccelDis = vecDetails[1].numData.y;
	//m_DecelDis = vecDetails[1].numData.z;

}

void RotateCommand::AddCommand(iCommand* command)
{
	std::cout << "Rotate Command Group does not accept other commands." << std::endl;
}
