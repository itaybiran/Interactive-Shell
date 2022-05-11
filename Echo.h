#pragma once
#include "Command.h"

class Echo : public Command
	//A class that represents the echo command
{
public:
	Echo(std::string inputCommand);
	void checkValidation();
	void execute();
};

