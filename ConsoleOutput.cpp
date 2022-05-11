#include "ConsoleOutput.h"

void ConsoleOutput::output(std::string str) {
	std::cout << str;
}

void ConsoleOutput::wOutput(std::wstring str) {
	std::wcout << str;
}