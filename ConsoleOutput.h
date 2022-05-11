#pragma once
#include "IOutput.h"
class ConsoleOutput : public IOutput
	//A class that represents a console output
{
	void output(std::string);
	void wOutput(std::wstring);

};

