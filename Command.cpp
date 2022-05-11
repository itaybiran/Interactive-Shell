#include "Command.h"

//initialize the command
void Command::initCommand(std::string inputCommand) {
	this->inputCommand = inputCommand;
	this->initParameters(inputCommand);
	this->name = this->parameters[0];
	this->parameters.erase(this->parameters.begin()); //Deletes the name of the command from the parameters list
}

//Sets the parameters
void Command::initParameters(std::string inputCommand) {
	int counter = 0;
	while (inputCommand[counter] == ' ' && counter < inputCommand.size()) {
		counter++;
	}
	std::string word("");
	bool quote = false;
	for (int i = counter; i < inputCommand.length(); i++) {
		if (inputCommand[i] == '"')
			quote = !quote;
		if (inputCommand[i] == ' ' && quote == false) {
			if (word != "") {
				this->parameters.push_back(word);
				lowerAllChar(word);
				if (word == "echo") {
					word = "";
					for (int j = i + 1; j < inputCommand.size(); j++) {
						word += inputCommand[j];
					}
					break;
				}
			}
			word = "";
		}
		else {
			if(inputCommand[i] != '"')
				word += inputCommand[i];
		}
	}
	if(word != "")
		this->parameters.push_back(word);
}

//add the full path if needed to the path parameter, in case that the user entered just the name of the file
void Command::addFullPathIfNeeded(const int paramIndex, std::string& cpath, int cpathSize) {
	if (!std::filesystem::exists(this->parameters[paramIndex])) {
		if(cpath[cpathSize - 1] == '\\')
			this->parameters[paramIndex] = cpath + this->parameters[paramIndex];
		else
			this->parameters[paramIndex] = cpath + "\\" + this->parameters[paramIndex];
	}
}

