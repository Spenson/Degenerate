#pragma once

#include "iCommand.h"


class FollowObjectCommand : public iCommand
{
	std::string m_Name;
	cGameObject* m_pGO;
	cGameObject* m_pGOTarget;
	float m_Time;
	float m_TimeToFollow;
	float m_Speed;
	float m_FarBound;
	float m_NearBound;
	bool m_Done;

public:
	FollowObjectCommand(std::string name) : m_Name(name), m_Done(false), m_Time(0.0f), m_TimeToFollow(0.0f), m_pGO(nullptr), m_pGOTarget(nullptr) {}
	// Inherited via iCommand
	virtual void SetName(std::string name) override;
	virtual bool IsDone() override;
	virtual bool Update(double deltaTime) override;
	virtual void SetGameObject(cGameObject* pGO) override;
	virtual void Init(std::vector<sPair> vecDetails) override;
	virtual void AddCommand(iCommand* command) override;
};