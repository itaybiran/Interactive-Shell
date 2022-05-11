#pragma once
#include "Command.h"
#include <iostream>
#include <string>

class NoCommand : public Command
	//A class that represents a situation when there is no command
{
public:
	NoCommand(std::string inputCommand);
	void checkValidation() {}
	void execute();
};

