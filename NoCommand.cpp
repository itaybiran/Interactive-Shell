#include "NoCommand.h"

NoCommand::NoCommand(std::string inputCommand) {
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void NoCommand::execute() {
	throw std::exception("Invalid Command.");
}
