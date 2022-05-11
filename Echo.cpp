#include "Echo.h"

Echo::Echo(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Echo::checkValidation() {
	if (this->parameters.size() != 1) {
		throw std::exception("The syntax of the command is incorrect.");
	}
}

void Echo::execute() {
	this->checkValidation();
	this->output->output(this->parameters[0] + "\n\n");
	//std::cout << this->parameters[0] << "\n\n";
}
