#pragma once
#include <iostream>
#include <string>

//interface for commands output
class IOutput
{
public:
	virtual void output(std::string) = 0;
	virtual void wOutput(std::wstring) = 0;
};

