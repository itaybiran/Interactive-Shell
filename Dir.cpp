#include "Dir.h"


Dir::Dir(std::string inputCommand) {
	this->initCommand(inputCommand);
	this->output = std::unique_ptr<IOutput>(new ConsoleOutput());
}

void Dir::checkValidation() {
	if (this->parameters.size() != 2)
		throw std::exception("The syntax of the command is incorrect.");
	this->addFullPathIfNeeded(0, Shell::environmentVariables["CWD"], Shell::environmentVariables["CWD"].size());
	LPCSTR longString = this->parameters[0].c_str();
	
	int fileAttribute = GetFileAttributesA(longString);
	if (!(fileAttribute & FILE_ATTRIBUTE_DIRECTORY) || fileAttribute == -1)
		throw std::exception("Directory Not Found.");
	if(!isNumber(this->parameters[1]))
		throw std::exception("Invalid Depth.");
		
}

void Dir::execute() {
	this->useCurrentPathIfNoParam();
	this->addDefaultDepth();
	this->checkValidation();
	this->printFilesInDirectory(this->parameters[0], 0);
	this->output->output("\n");
}

void Dir::printFilesInDirectory(std::string dirName, int depth) {
	try {
		for (const auto f : std::filesystem::directory_iterator(dirName)) {
			printFileAttribute(f, depth);
			LPCSTR longString = f.path().string().c_str();
			if (((GetFileAttributesA(longString)) & FILE_ATTRIBUTE_DIRECTORY) && depth < std::atoi(this->parameters[1].c_str())) {
				printFilesInDirectory(f.path().string(), (depth + 1));
			}
		}
	}
	catch (const std::exception) {

	}
}

void Dir::printFileAttribute(const std::filesystem::directory_entry& file, int depth) {
	try {
		this->addInditation(depth);
		this->output->output(file.path().string() + ":\n");
		//std::cout << file.path().string() << ":\n";
		this->addInditation(depth);
		this-> printType(file);
		this->addInditation(depth);
		this-> printSize(file);
		this->addInditation(depth);
		this->printTime(file, depth);
		this->output->output("\n");
		//std::cout << std::endl;
	}
	catch (const std::exception) {
		this->output->output("The process cannot access the file because it is being used by another process.\n\n");
		//std::cout << "The process cannot access the file because it is being used by another process.\n\n";
	}
}

void Dir::printTime(const std::filesystem::directory_entry& file, int depth) {
	FILETIME ftCreate, ftAccess, ftModified;
	SYSTEMTIME cstUTC, cstLocal, astUTC, astLocal, mstUTC, mstLocal;
	std::string stringPath = file.path().string();
	LPSTR path = const_cast<char*>(stringPath.c_str());
	HANDLE handle = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL,OPEN_EXISTING, 0, NULL);
	if (GetFileTime(handle, &ftCreate, &ftAccess, &ftModified)) {
		FileTimeToSystemTime(&ftCreate, &cstUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &cstUTC, &cstLocal);
		FileTimeToSystemTime(&ftAccess, &astUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &astUTC, &astLocal);
		FileTimeToSystemTime(&ftModified, &mstUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &mstUTC, &mstLocal);
		this->output->output(" * Created: " + std::to_string(cstLocal.wMonth) + "/" + std::to_string(cstLocal.wDay) + "/" + std::to_string(cstLocal.wYear) + "  " + std::to_string(cstLocal.wHour) + ":" + std::to_string(cstLocal.wMinute) + "\n");
		//printf(" * Created: %02d/%02d/%d  %02d:%02d\n", cstLocal.wMonth, cstLocal.wDay, cstLocal.wYear, cstLocal.wHour, cstLocal.wMinute);
		this->addInditation(depth);
		this->output->output(" * Accessed: " + std::to_string(astLocal.wMonth) + "/" + std::to_string(astLocal.wDay) + "/" + std::to_string(astLocal.wYear) + "  " + std::to_string(astLocal.wHour) + ":" + std::to_string(astLocal.wMinute) + "\n");
		//printf(" * Accessed: %02d/%02d/%d  %02d:%02d\n", astLocal.wMonth, astLocal.wDay, astLocal.wYear, astLocal.wHour, astLocal.wMinute);
		this->addInditation(depth);
		this->output->output(" * Created: " + std::to_string(mstLocal.wMonth) + "/" + std::to_string(mstLocal.wDay) + "/" + std::to_string(mstLocal.wYear) + "  " + std::to_string(mstLocal.wHour) + ":" + std::to_string(mstLocal.wMinute) + "\n");
		//printf(" * Modified: %02d/%02d/%d  %02d:%02d\n", mstLocal.wMonth, mstLocal.wDay, mstLocal.wYear, mstLocal.wHour, mstLocal.wMinute);
	}
	CloseHandle(handle);
}

void Dir::printSize(const std::filesystem::directory_entry& file) {
	if (std::filesystem::is_directory(std::filesystem::status(file.path().string())))
		this->output->output(" * Size: <DIR> \n");
		//std::cout << " * Size: <DIR> \n";
	else {
		uintmax_t size = std::filesystem::file_size(file.path());
		this->output->output(" * Size: " + convertBytes(size) + "  (" + std::to_string(size) + " bytes)\n");
		//std::cout << " * Size: " << convertBytes(size) << "  ("<< size << " bytes)\n";
	}
}

void Dir::printType(const std::filesystem::directory_entry& file) {
	if (std::filesystem::is_directory(std::filesystem::status(file.path().string())))
		this->output->output(" * Type: File folder\n");
	//std::cout << " * Type: File folder" << '\n';
	else
		if (file.path().has_extension())
			this->output->output(" * Type: " + file.path().extension().string() + "\n");
	//std::cout << " * Type: " << file.path().extension().string() << '\n';
		else
			this->output->output(" * Type: File\n");
			//std::cout << " * Type: File" << '\n';
}


void Dir::addDefaultDepth() {
	if (this->parameters.size() == 1)
		this->parameters.push_back("0");
}

void Dir::useCurrentPathIfNoParam() {
	if (this->parameters.size() == 0) {
		this->parameters.push_back(Shell::environmentVariables["CWD"]);
	}
}

inline void Dir::addInditation(int depth) {
	for (int i = 0; i < depth; i++)
		this->output->output("  ");
		//std::cout << "  ";
}
