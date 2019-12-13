#pragma once

#pragma once

#include "iCommand.h"


class RotateOverTimeCommand : public iCommand
{

	std::string m_Name;
	bool m_Done;

	cGameObject* m_pGO;

	float m_Time;
	float m_TimeElapsed;

	glm::quat m_StartQ;
	glm::quat m_EndQ;

	bool m_HasUpdated;

public:
	RotateOverTimeCommand(std::string name) : m_Name(name), m_Done(false), m_HasUpdated(false),
		m_Time(0), m_TimeElapsed(0), m_StartQ(glm::quat()), m_EndQ(glm::quat()),
		m_pGO(nullptr)
	{
	};
	// Inherited via iCommand
	virtual void SetName(std::string name) override;
	virtual bool IsDone() override;
	virtual bool Update(double deltaTime) override;
	virtual void SetGameObject(cGameObject* pGO) override;
	virtual void Init(std::vector<sPair> vecDetails) override;
	virtual void AddCommand(iCommand* command) override;
};