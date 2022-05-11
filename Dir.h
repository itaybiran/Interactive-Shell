#pragma once
#include "Command.h"
#include "StringFunctions.h"
#include <windows.h>
#include <fileapi.h>
#include <minwinbase.h>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <io.h>
#include <fcntl.h>
#include <cstring>
#include <chrono>
#include <iomanip>
#include "Memory.h"
#include "Shell.h"

class Dir : public Command
	//A class that represents the dir command
{
public:
	Dir(std::string inputCommand);
	void checkValidation();
	void execute(); //executes the command
	void addDefaultDepth(); //sets 0 as depth if the user didn't enter depth as parameter
	void useCurrentPathIfNoParam(); //uses current path as directory if there are 0 parameters
	void printFilesInDirectory(std::string dirName, int depth); //prints the files in the directory recursivly (depending on depth)
	void printFileAttribute(const std::filesystem::directory_entry& file, int depth); //prints all the files attribute
	void printType(const std::filesystem::directory_entry& file);
	void printSize(const std::filesystem::directory_entry& file);
	void printTime(const std::filesystem::directory_entry& file, int depth);
	inline void addInditation(int depth); //add inditation according to the depth of the current file
};

