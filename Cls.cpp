#include "Cls.h"

Cls::Cls(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Cls::checkValidation() {

}

void Cls::execute() {
	std::system("cls"); //TODO: implement this in cpp
	std::cout << std::flush;
	this->output->output("\n");
}