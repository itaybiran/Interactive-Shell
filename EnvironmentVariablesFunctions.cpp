#include "EnvironmentVariablesFunction.h"


//gets a list of where executable files reside on your system
std::vector<std::string> getPathesFromPATH(const std::string& pathVar) {
	std::vector<std::string> pathes = std::vector<std::string>();
	std::string path = "";
	for (int i = 0; i < pathVar.size(); i++) {
		if (pathVar[i] == ';') {
			if (path != "") {
				pathes.push_back(path);
				path = "";
			}
		}
		else {
			path += pathVar[i];
		}
	}
	pathes.push_back(path);
	return pathes;
}