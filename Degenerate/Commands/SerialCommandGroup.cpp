#include "SerialCommandGroup.h"

#include <iostream>

void SerialCommandGroup::SetName(std::string name)
{
	m_Name = name;
}

bool SerialCommandGroup::Update(double deltaTime)
{
	if (!m_Commands[0]->Update(deltaTime))
	{
		m_Commands.erase(m_Commands.begin());
	}

	return !m_Commands.empty();
}

void SerialCommandGroup::SetGameObject(cGameObject* pGO)
{
	std::cout << "Serial Command Group does not record Game Object." << std::endl;
}

void SerialCommandGroup::Init(std::vector<sPair> vecDetails)
{
	std::cout << "Serial Command Group does not need to be initialized." << std::endl;
}

void SerialCommandGroup::AddCommand(iCommand* command)
{
	m_Commands.push_back(command);
}

bool SerialCommandGroup::IsDone()
{
	return m_Commands.empty();
}
