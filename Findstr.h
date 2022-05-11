#pragma once
#include "Command.h"
#include "StringFunctions.h"
#include<filesystem>
#include <Windows.h>
#include <fstream>
#include <string>
#include "Shell.h"

class Findstr : public Command
	//A class that represents the findstr command
{
private:
	std::vector<std::string> strings;
public:
	Findstr(std::string inputCommand);
	void checkValidation();
	void execute();
	void separatesStringsToDifferentParameters();
	bool checkIfStringInLine(std::string line);
};

