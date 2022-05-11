#pragma once
#include "Command.h"
#include "Shell.h"
#include <filesystem>
#include <windows.h>

class Move : public Command
	//A class that represents the move command
{
public:
	Move(std::string inputCommand);
	void checkValidation();
	void execute();
	void addDestinationIfNeeded();
};

