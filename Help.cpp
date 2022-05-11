#include "Help.h"

Help::Help(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Help::checkValidation() {
	if (!(this->parameters.size() == 0 || this->parameters.size() == 1))
		throw std::exception("The syntax of the command is incorrect.");
	if (this->parameters.size() == 1) {
		std::string cmd = this->parameters[0];
		lowerAllChar(cmd);
		if (cmd!= "cls" && cmd != "set" && cmd != "cd" && cmd != "type" && cmd != "dir" && cmd != "echo" && cmd != "help" && cmd != "exit" && cmd != "findstr" && cmd != "start" && cmd != "tasklist" && cmd != "copy" && cmd != "move" && cmd != "del" && cmd != "timeout" && cmd != "whoami") {
			throw std::exception("This command is not supported by the help utility.");
		}
	}
}

void Help::execute() {
	this->checkValidation();
	if (this->parameters.size() == 0) {
		this->output->output("CD            Displays the name of or changes the current directory.\n\
CLS           Clears the screen.\n\
COPY          Copies one or more files to another location.\n\
DEL           Deletes a file.\n\
DIR           Recursively displays a list of files and subdirectories in a directory.\n\
ECHO          Displays messages.\n\
EXIT          Quits the program.\n\
FINDSTR       Searches for strings in files.\n\
HELP          Displays help information on commands.\n\
MOVE          Moves a file or a directory to another location.\n\
SET           Displays, sets, or removes environment variables.\n\
START         Starts a programs or a batch file.\n\
TASKLIST      Displays a list of currently running processes.\n\
TIMEOUT       Wait a specified amount of time.\n\
TYPE          Displays the contents of a file.\n\
WHOAMI        Displays the current username.\n\n");
	}
	else {
		std::map<std::string, std::string> cmdExplain = { 
			{"type", "Displays the contents of a file.\n\nTYPE [Path]\n\nPath - Shows the content of this file."},
			{"dir", "Recursively displays a list of files and subdirectories in a directory.\n\nDIR                 (displays a list of files and subdirectories in the current path)\nDIR [Path]          (displays a list of files and subdirectories in Path)\nDIR [Path][Depth]   (displays recursively a list of files and subdirectories in Path)\n\nPath - Displays a list of files and subdirectories in this directory.\nDepth - The depth of the recursion (default = 0)"},
			{"echo", "Displays messages\n\nECHO [Message]\n\nMessage - Displays this message."}, 
			{"help", "Displays help information on commands.\n\nHELP                (displays all commands)\nHELP[Command]\n\nCommand - Displays help information on that command."},
			{"exit", "Quits the program.\n\nEXIT"},
			{"findstr", "Searches for strings in files.\n\nFINDSTR [Strings][Path]\n\nStrings - The strings to search in the file.\nPath - The file to search the string in."},
			{"start", "Starts a programs or a batch file.\n\nSTART               (start with the current path)\nSTART [Path]\n\nPath - The path that will be executed."},
			{"tasklist", "This tool displays a list of currently running processes.\n\nTASKLIST"},
			{"cls", "Clears the screen.\n\nCLS"},
			{"copy", "Copies one or more files to another location.\n\nCOPY [Source]       (copies to the current path)\nCOPY [Source][Destination]\n\nSource - Specifies the file or files to be copied.\nDestination - Specifies the directory for the new file(s)."},
			{"move", "Moves a file or a directory to another location.\n\nMOVE [Source]       (moves to the current path)\nMOVE [Source][Destination]\n\nSource - Specifies the file or files to be moved.\nDestination - Specifies the directory for the new file(s)."},
			{"del", "Deletes a file.\n\nDEL [Path]\n\nPath - The path of the file that will be deleted."},
			{"timeout", "Wait a specified amount of time.\n\nTIMEOUT [Seconds]\n\nSeconds - The time to wait in seconds."},
			{"whoami", "Displays the current username.\n\nWHOAMI"},
			{"cd", "Displays the name of or changes the current directory.\n\nCD                  (displays the current directory)\nCD [..]\nCD [Path]\n\n .. - Specifies that you want to change to the parent directory.\n Path - The new path."},
			{"set", "Displays, sets, or removes environment variables.\n\nSET                 (Display the current environment variables)\nSET [Name]          (Displays the value of all variables whose prefix matches the name given to the SET command)\nSET [Variable=[String]]\n\nVariable - Specifies the environment-variable name.\nString - Specifies a series of characters to assign to the variable."}
		};
		std::string cmd = this->parameters[0];
		lowerAllChar(cmd);
		for (auto& commandExplain : cmdExplain) {
			if (commandExplain.first == cmd) {
				//std::cout << "dfdfdf";
				this->output->output(std::string(commandExplain.second) + "\n\n");

				//std::cout << commandExplain.second << "\n\n";
			}
		}
	}
}
