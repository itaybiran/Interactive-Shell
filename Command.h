#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "StringFunctions.h"
#include "IOutput.h"
#include "ConsoleOutput.h"
#include <memory>

class Command
	//An abstract class that represents a command
{
protected:
	std::string inputCommand;
	std::string name;
	std::vector<std::string> parameters;
	std::unique_ptr<IOutput> output;
public:
	Command() {};
	void initCommand(std::string inputCommand);
	void initParameters(std::string input_command);
	void addFullPathIfNeeded(const int paramIndex, std::string& cpath, int cpathSize);
	virtual void execute() = 0;
	std::string getName() { return this->name; }
	std::string getInputCommand() { return this->inputCommand; }
	std::vector<std::string> getParameters() { return this->parameters; }
};

