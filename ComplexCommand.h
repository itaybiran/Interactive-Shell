#pragma once
#include <string>
#include <vector>
#include "Command.h"

class ComplexCommand
//a class that represents all the line of the command, even if it uses piping
{
public:
	ComplexCommand(std::string inputCommand, std::vector<Command*> listOfCommands);
	~ComplexCommand();
	void execute();
	void printComplexCommand();
private:
	std::string inputCommand;
	std::vector<Command*> listOfCommands;

};

