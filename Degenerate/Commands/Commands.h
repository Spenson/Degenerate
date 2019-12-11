#pragma once


#include "iCommand.h"

iCommand* MakeCommand(std::string type, std::string name, std::string params);
//iCommand* InitCommand(iCommand* command, std::vector<sPair> params);
iCommand* AddCommandsToGroup(std::vector<iCommand*> commands, iCommand* commandGroup = 0);
iCommand* AddCommandToGroup(iCommand* command, iCommand* commandGroup = 0);

