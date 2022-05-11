#pragma once
#include "Command.h"
#include <filesystem>
#include "Shell.h"

class Del : public Command
	//A class that represents the del command
{
public:
	Del(std::string inputCommand);
	void checkValidation();
	void execute();
};

