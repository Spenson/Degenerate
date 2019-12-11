#pragma once

#include "iCommand.h"


class FollowCurveCommand : public iCommand
{
	std::string m_Name;
	std::vector<glm::vec3> m_ControlPoints;
	float m_Time;
	cGameObject* m_pGO;
	bool m_Done;

	float m_MaxSpeed;
	//float m_AccelDis;
	//float m_DecelDis;

public:
	FollowCurveCommand(std::string name): m_Name(name), m_Time(0.0f), m_pGO(nullptr), m_Done(false) {}
	// Inherited via iCommand
	virtual void SetName(std::string name) override;
	virtual bool IsDone() override;
	virtual bool Update(double deltaTime) override;
	virtual void SetGameObject(cGameObject* pGO) override;
	virtual void Init(std::vector<sPair> vecDetails) override;
	virtual void AddCommand(iCommand* command) override;
};