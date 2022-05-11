#include "Copy.h"

Copy::Copy(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Copy::checkValidation() {
	if (this->parameters.size() != 2) {
		throw std::exception("The syntax of the command is incorrect.");
	}
	this->addFullPathIfNeeded(0, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
	this->addFullPathIfNeeded(1, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
	if (!std::filesystem::exists(this->parameters[0]) || !std::filesystem::exists(this->parameters[1]))
		throw std::exception("The system cannot find the path specified.");
}

void Copy::execute() {
	this->addDestinationIfNeeded();
	this->checkValidation();
	std::filesystem::path from = (this->parameters[0]);
	std::filesystem::path to = (this->parameters[1]);
	std::filesystem::copy(from, to);
	this->output->output("copied.\n\n");
	//std::cout << "copied.\n\n";
}

void Copy::addDestinationIfNeeded() {
	if (this->parameters.size() == 1) {
		this->parameters.push_back(Shell::environmentVariables["CWD"]);
	}
}

