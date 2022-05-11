#pragma once
#include <iostream>
#include <string>
#include <memory>
#include "Command.h"
class ComplicatedCommand
{
public:
	ComplicatedCommand(std::string inputComplicatedCommand, std::vector<std::string> inputCommands, std::vector<Command*> listOfCommands);
	void execute();
private:
	std::string inputComplicatedCommand;
	std::vector<std::string> inputCommands;
	std::vector<std::unique_ptr<Command>> listOfCommands;
};

