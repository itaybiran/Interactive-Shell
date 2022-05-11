#pragma once
#include "Command.h"
#include "Shell.h"
#include <filesystem>
#include <Windows.h>

class Cd : public Command
	//A class that represents the cd commnad
{	
public:
	Cd(std::string inputCommand);
	void checkValidation();
	void execute();
	void executeNoParameters();
	void upOneDirLevel();
	void goInsideOneDir();
};


