#pragma once
#include "Command.h"
class Cls : public Command
	//A class that represents the cls command
{
public:
	Cls(std::string inputCommand);
	void checkValidation();
	void execute();
};

