#include "ComplicatedCommand.h"
//constructor
ComplicatedCommand::ComplicatedCommand(std::string inputComplicatedCommand, std::vector<std::string> inputCommands, std::vector<Command*> listOfCommands) {
	this->inputComplicatedCommand = inputComplicatedCommand;
	this->inputCommands = inputCommands;
	this->listOfCommands = std::vector<std::unique_ptr<Command>>();
	for (Command* command : listOfCommands) {
		this->listOfCommands.push_back(std::unique_ptr<Command>(command));
	}
}

void ComplicatedCommand::execute() {

}