#pragma once
#include "Command.h"
#include "StringFunctions.h"
#include <map>

class Help : public Command
	//A class that represents the help command
{
public:
	Help(std::string inputCommand);
	void checkValidation();
	void execute();
};

