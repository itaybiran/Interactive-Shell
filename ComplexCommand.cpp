#include "ComplexCommand.h"

ComplexCommand::ComplexCommand(std::string inputCommand, std::vector<Command*> listOfCommands) {
	this->inputCommand = inputCommand;
	this->listOfCommands = listOfCommands;
}

ComplexCommand::~ComplexCommand() {
	delete this;
	std::cout << "deleted!\n";
}
void ComplexCommand::printComplexCommand() {
	for (int i = 0; i < listOfCommands.size(); i++) {
		std::cout << i << ") " << listOfCommands[i]->getInputCommand() << '\n';
	}
}
//executes the complex command
void ComplexCommand::execute() {
	for (int i = 0; i < this->listOfCommands.size(); i++) {
		this->listOfCommands[i]->execute();
	}
}