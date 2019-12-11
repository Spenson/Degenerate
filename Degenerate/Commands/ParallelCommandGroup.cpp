#include "ParallelCommandGroup.h"

#include <iostream>

void ParallelCommandGroup::SetName(std::string name) 
{
	m_Name = name;
}

bool ParallelCommandGroup::Update(double deltaTime)
{
	for (size_t i = 0; i < m_Commands.size(); i++)
	{
		if (!m_Commands[i]->Update(deltaTime))
		{
			m_Commands.erase(m_Commands.begin() + i);
			i--;
		}
	}

	return !m_Commands.empty();
}

void ParallelCommandGroup::SetGameObject(cGameObject* pGO)
{
	std::cout << "Parallel Command Group does not record Game Object." << std::endl;
}

void ParallelCommandGroup::Init(std::vector<sPair> vecDetails)
{
	std::cout << "Parallel Command Group does not need to be initialized." << std::endl;
}

void ParallelCommandGroup::AddCommand(iCommand* command)
{
	m_Commands.push_back(command);
}

bool ParallelCommandGroup::IsDone()
{
	return m_Commands.empty();
}
