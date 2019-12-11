#include "FollowObjectCommand.h"

void FollowObjectCommand::SetName(std::string name)
{
	m_Name = name;
}

bool FollowObjectCommand::IsDone()
{
	return m_Done;
}

bool FollowObjectCommand::Update(double deltaTime)
{
	m_Time += deltaTime;
	glm::vec3 velocity;
	if (m_Time >= m_TimeToFollow)
	{
		m_pGOTarget->velocity = glm::vec3(0.0f);
		m_Done = true;
		return false;

	}
	else
	{
		glm::vec3 dir = glm::normalize(m_pGO->positionXYZ - m_pGOTarget->positionXYZ);
		float dis = glm::distance(m_pGOTarget->positionXYZ, m_pGO->positionXYZ);
		m_pGOTarget->velocity = dir * (glm::smoothstep(m_NearBound, m_FarBound, dis) * m_Speed);
	}

	return true;
}

void FollowObjectCommand::SetGameObject(cGameObject* pGO)
{
	if (!m_pGO)
		m_pGO = pGO;
	m_pGOTarget = pGO;
}

void FollowObjectCommand::Init(std::vector<sPair> vecDetails)
{
	m_Speed = vecDetails[0].numData.x;
	m_TimeToFollow = vecDetails[0].numData.y;
	m_FarBound = vecDetails[0].numData.z;
	m_NearBound = vecDetails[0].numData.w;
}

void FollowObjectCommand::AddCommand(iCommand* command)
{
}
