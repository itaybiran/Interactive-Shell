#include "Cd.h"

Cd::Cd(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Cd::checkValidation() {
	if (this->parameters.size() != 0 && this->parameters.size() != 1) {
		throw std::exception("The syntax of the command is incorrect.");
	}
	if (this->parameters.size() == 1) {
		if (this->parameters[0] != "..") {
			this->addFullPathIfNeeded(0, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
			LPCSTR path = this->parameters[0].c_str();


			if (std::filesystem::exists(this->parameters[0])) {
				if (!(GetFileAttributesA(path) & FILE_ATTRIBUTE_DIRECTORY)) {
					throw std::exception("The directory name is invalid.");
				}
			}
			else {
				throw std::exception("The system cannot find the path specified.");
			}
		}
	}
}

void Cd::execute() {
	this->checkValidation();
	if (this->parameters.size() == 0) {
		this->executeNoParameters();
	}
	else if (this->parameters[0] == "..") {
		this->upOneDirLevel();
	}
	else if (std::filesystem::exists(this->parameters[0])) {
		Shell::environmentVariables["CWD"] = this->parameters[0];
	}
	else {
		this->goInsideOneDir();
	}
	this->output->output("\n");
}

void Cd::executeNoParameters() {
	this->output->output(Shell::environmentVariables["CWD"] + "\n");
	//std::cout << Shell::environmentVariables["CWD"] << "\n";
}

void Cd::upOneDirLevel() {
	if (Shell::environmentVariables["CWD"] != "c:") {
		int lastSlashIndex = 0;
		std::string newPath = "";
		int slashCount = 0;
		for (int i = Shell::environmentVariables["CWD"].size() - 1; i >= 0; i--) {
			if (Shell::environmentVariables["CWD"][i] == '\\') {
				lastSlashIndex = i;
				break;
			}
		}
		for (int i = 0; i <= lastSlashIndex; i++) {
			if (Shell::environmentVariables["CWD"][i] == '\\')
				slashCount++;
			if (i == lastSlashIndex && slashCount > 1) {
				break;
			}
			newPath += Shell::environmentVariables["CWD"][i];
		}
		Shell::environmentVariables["CWD"] = newPath;
	}
}

void Cd::goInsideOneDir() {
	if (Shell::environmentVariables["CWD"][Shell::environmentVariables["CWD"].size() - 1] == '\\')
		Shell::environmentVariables["CWD"] = Shell::environmentVariables["CWD"] + this->parameters[0];
	else {
		Shell::environmentVariables["CWD"] = Shell::environmentVariables["CWD"] + "\\" + this->parameters[0];
	}
}