#pragma once

#include "iCommand.h"


class FollowCurveOverTimeCommand : public iCommand
{
	std::string m_Name;
	std::vector<glm::vec3> m_ControlPoints;

	cGameObject* m_pGO;
	bool m_Done;

	float m_Time;
	float m_TimeElapsed;

public:
	FollowCurveOverTimeCommand(std::string name) : m_Name(name), m_Time(0.0f), m_TimeElapsed(0.0f), m_pGO(nullptr), m_Done(false), m_ControlPoints() {}
	// Inherited via iCommand
	virtual void SetName(std::string name) override;
	virtual bool IsDone() override;
	virtual bool Update(double deltaTime) override;
	virtual void SetGameObject(cGameObject* pGO) override;
	virtual void Init(std::vector<sPair> vecDetails) override;
	virtual void AddCommand(iCommand* command) override;

private:
	glm::vec3 getCurvePoint(std::vector<glm::vec3> const& points, float const& step /*0 to 1*/);
};