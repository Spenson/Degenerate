#include "FollowCurveCommand.h"

#include <iostream>

void FollowCurveCommand::SetName(std::string name)
{
}

bool FollowCurveCommand::IsDone()
{
	return m_Done;
}

glm::vec3 getCurvePoint(std::vector<glm::vec3> const& points, float const& step)
{

	if (points.size() == 1)
	{
		return points[0];
	}

	std::vector<glm::vec3> newPoints;

	for(size_t idx = 0; idx < points.size()-1; idx++)
	{
		newPoints.push_back(((points[idx+1] - points[idx]) * step) + points[idx]);
	}

	return getCurvePoint(newPoints, step);
}

bool FollowCurveCommand::Update(double deltaTime)
{
	m_Time += deltaTime;

	float step =  m_MaxSpeed/ glm::distance(m_ControlPoints[0], m_ControlPoints[m_ControlPoints.size()-1]) * m_Time;

	m_pGO->positionXYZ = getCurvePoint(m_ControlPoints, step);

	if (step >= 1.0f)
	{
		m_Done = true;
		return false;
	}

	return true;
}

void FollowCurveCommand::SetGameObject(cGameObject* pGO)
{
	m_pGO = pGO;
}

void FollowCurveCommand::Init(std::vector<sPair> vecDetails)
{
	while (vecDetails.size() > 1)
	{
		m_ControlPoints.push_back(vecDetails[0].numData);
		vecDetails.erase(vecDetails.begin());
	}

	m_MaxSpeed = vecDetails[0].numData.x;
	//m_AccelDis = vecDetails[0].numData.y;
	//m_DecelDis = vecDetails[0].numData.z;
}

void FollowCurveCommand::AddCommand(iCommand* command)
{
	std::cout << "Follow Curve Command Group does not accept other commands." << std::endl;
}
