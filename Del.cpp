#include "Del.h"


Del::Del(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Del::checkValidation() {
	if (this->parameters.size() != 1) {
		throw std::exception("The syntax of the command is incorrect.");
	}
	this->addFullPathIfNeeded(0, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
	if (!std::filesystem::exists(this->parameters[0])) {
		throw std::exception("File Does Not Exist.");
	}
}

void Del::execute() {
	
	this->checkValidation();
	const std::filesystem::path pathToDelete(this->parameters[0]);
	std::filesystem::remove(pathToDelete);
	this->output->output("deleted.\n\n");
	//std::cout << "deleted.\n\n";
}