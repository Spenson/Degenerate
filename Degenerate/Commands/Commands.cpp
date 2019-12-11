#include "Commands.h"


#include "SerialCommandGroup.h"
#include "ParallelCommandGroup.h"
#include "MoveCommand.h"
#include "RotateCommand.h"
#include "FollowCurveCommand.h"
#include "FollowObjectCommand.h"
#include "LocationTrigger.h"


#include <iostream>
#include <sstream>

extern iCommand* g_ParentCommandGroup;

//void splitString(std::vector<std::string>& out, std::string s, std::string delim)
//{
//	while (!s.empty())
//	{
//		if (s.find(delim) != s.npos)
//		{
//			out.push_back(s.substr(0, s.find(delim)));
//			s = s.substr(s.find(delim)+2, s.length()-1);
//			continue;
//		}
//		out.push_back(s);
//		break;
//	}
//}


std::map<int, iCommand*> commandLookup;



int MakeCommand(std::string type, std::string name, std::string params)
{
	iCommand* command = nullptr;

	if ("SerialGroup" == type)
	{
		command = new SerialCommandGroup(name);
	}
	else if ("ParallelGroup" == type)
	{
		command = new ParallelCommandGroup(name);
	}
	else if ("Move" == type)
	{
		command = new MoveCommand(name);

		std::stringstream ss(params);

		std::string objectName;
		ss >> objectName;

		std::vector<sPair> vecParams(2);

		ss >> vecParams[0].numData.x;
		ss >> vecParams[0].numData.y;
		ss >> vecParams[0].numData.z;

		ss >> vecParams[1].numData.x;
		ss >> vecParams[1].numData.y;
		ss >> vecParams[1].numData.z;

		command->SetGameObject(pFindObjectByFriendlyName(objectName));
		command->Init(vecParams);
	}
	else if ("Rotate" == type)
	{
		command = new RotateCommand(name);

		std::stringstream ss(params);

		std::string objectName;
		ss >> objectName;

		std::vector<sPair> vecParams(2);

		ss >> vecParams[0].numData.x;
		ss >> vecParams[0].numData.y;
		ss >> vecParams[0].numData.z;

		ss >> vecParams[1].numData.x;
		ss >> vecParams[1].numData.y;
		ss >> vecParams[1].numData.z;

		command->SetGameObject(pFindObjectByFriendlyName(objectName));
		command->Init(vecParams);
	}
	else if ("FollowCurve" == type)
	{
		command = new FollowCurveCommand(name);

		std::stringstream ss(params);

		std::string objectName;
		ss >> objectName;

		std::vector<sPair> vecParams;

		sPair temp;
		while (!ss.eof())
		{
			ss >> temp.numData.x;
			ss >> temp.numData.y;
			ss >> temp.numData.z;
			vecParams.push_back(temp);
		}


		//ss >> vecParams[0].numData.x;
		//ss >> vecParams[0].numData.y;
		//ss >> vecParams[0].numData.z;

		//ss >> vecParams[1].numData.x;
		//ss >> vecParams[1].numData.y;
		//ss >> vecParams[1].numData.z;

		command->SetGameObject(pFindObjectByFriendlyName(objectName));
		command->Init(vecParams);
	}
	else if ("FollowObject" == type)
	{
		command = new FollowObjectCommand(name);
		std::stringstream ss(params);
		std::string objectName;
		ss >> objectName;
		command->SetGameObject(pFindObjectByFriendlyName(objectName));
		ss >> objectName;
		command->SetGameObject(pFindObjectByFriendlyName(objectName));

		std::vector<sPair> vecParams(1);
		ss >> vecParams[0].numData.x;
		ss >> vecParams[0].numData.y;
		ss >> vecParams[0].numData.z;
		ss >> vecParams[0].numData.w;
		command->Init(vecParams);
	}
	else if ("LocationTrigger")
	{
		command = new LocationTrigger(name);

		std::stringstream ss(params);

		std::string objectName;
		ss >> objectName;

		std::vector<sPair> vecParams(2);
		ss >> vecParams[0].numData.x;
		ss >> vecParams[0].numData.y;
		ss >> vecParams[0].numData.z;

		ss >> vecParams[1].numData.x;

		command->SetGameObject(pFindObjectByFriendlyName(objectName));
		command->Init(vecParams);
	}
	else
	{
		std::cout << "Error: Unknown Command Type (" << type << ")" << std::endl;
	}

	commandLookup[commandLookup.size() + 1] = command;


	return commandLookup.size();
}

//iCommand* InitCommand(iCommand* command, std::vector<sPair> params)
//{
//	command->Init(params);
//
//	return command;
//}

int AddCommandsToGroup(std::vector<int> commands, int commandGroup)
{
	if (commandGroup == 0)
	{
		for (int command : commands)
		{
			g_ParentCommandGroup->AddCommand(commandLookup[command]);
		}
		return 0;
	}


	for (int command : commands)
	{
		commandLookup[commandGroup]->AddCommand(commandLookup[command]);
	}
	return commandGroup;
}

int AddCommandToGroup(int command, int commandGroup)
{
	if (commandGroup == 0)
	{
		g_ParentCommandGroup->AddCommand(commandLookup[command]);
		return 0;
	}
	commandLookup[commandGroup]->AddCommand(commandLookup[command]);
	return commandGroup;
}

iCommand* createParent(std::string name)
{
	return new ParallelCommandGroup(name);
}
