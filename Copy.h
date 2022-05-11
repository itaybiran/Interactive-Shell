#pragma once
#include "Command.h"
#include "Shell.h"
#include <Windows.h>
#include <filesystem>


class Copy : public Command
	//A class that represents the copy command
{
public:
	Copy(std::string inputCommand);
	void checkValidation();
	void execute();
	void addDestinationIfNeeded();
};

