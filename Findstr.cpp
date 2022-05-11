#include "Findstr.h"

Findstr::Findstr(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());

}

void Findstr::checkValidation() {
	if (this->parameters.size() != 2) {
		throw std::exception("The syntax of the command is incorrect.");
	}
	this->addFullPathIfNeeded(1, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
	if (!std::filesystem::exists(this->parameters[1])) {
		throw std::exception("File Not Found.");
	}

	LPCSTR path = this->parameters[1].c_str();
	int fileAttribute = GetFileAttributesA(path);
	if (fileAttribute & FILE_ATTRIBUTE_DIRECTORY)
		throw std::exception("File Not Found.");
}

void Findstr::execute() {
	this->checkValidation();
	this->separatesStringsToDifferentParameters();
	std::string line;
	std::ifstream file;
	std::string filename = this->parameters[1];
	if (this->strings.size() == 0)
		throw std::exception("No Search Strings.");
	file.open(filename, std::ios::in);
	if(!file)
		throw std::exception("Access is denied.");
	else {
		while (std::getline(file, line)) {
			if (checkIfStringInLine(line))
				this->output->output(line + "\n");
				//std::cout << line << '\n';
		}
	}
	file.close();
	this->output->output("\n");
	//std::cout << "\n";
}

bool Findstr::checkIfStringInLine(std::string line) {
	for (int i = 0; i < this->strings.size(); i++) {
		if (checkIfStringInString(line, this->strings[i])) {
			return true;
		}
	}
	return false;
}


void Findstr::separatesStringsToDifferentParameters() {
	std::string str = "";
	for (int i = 0; i < this->parameters[0].size(); i++) {
		if (this->parameters[0][i] == ' ') {
			if (str != " " && str != "") {
				this->strings.push_back(str);
				str = "";
			}
		}
		else {
			str += this->parameters[0][i];
		}
	}
	if (str != "")
		this->strings.push_back(str);
}
