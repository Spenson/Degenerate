#pragma once


#include "iCommand.h"

int MakeCommand(std::string type, std::string name, std::string params);
//iCommand* InitCommand(iCommand* command, std::vector<sPair> params);
int AddCommandsToGroup(std::vector<int> commands, int commandGroup = 0);
int AddCommandToGroup(int command, int commandGroup = 0);

iCommand* createParent(std::string name);