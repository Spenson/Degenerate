#pragma once


class iCommand
{
	virtual bool Update() = 0;
};

class iCommandGroup : public iCommand
{
	virtual void AddCommand(iCommand* command) = 0;
};