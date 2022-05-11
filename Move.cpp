#include "Move.h"

Move::Move(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Move::checkValidation() {
	if (this->parameters.size() != 2) {
		throw std::exception("The syntax of the command is incorrect.");
	}
	this->addFullPathIfNeeded(0, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
	this->addFullPathIfNeeded(1, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
	if (!(std::filesystem::exists(this->parameters[0]))) {
		throw std::exception("The system cannot find the path specified.");
	}
}

void Move::execute() {
	this->addDestinationIfNeeded();
	this->checkValidation();
	//copying the file to the destination
	std::filesystem::path from = (this->parameters[0]);
	std::filesystem::path to = (this->parameters[1]);
	std::filesystem::copy(from, to);
	//deleting the file from the source
	LPCSTR deleteFrom = this->parameters[0].c_str();
	DeleteFileA(deleteFrom);
	this->output->output("moved.\n\n");
	//std::cout << "moved.\n\n";
}


void Move::addDestinationIfNeeded() {
	if (this->parameters.size() == 1) {
		this->parameters.push_back(Shell::environmentVariables["CWD"]);
	}
}
