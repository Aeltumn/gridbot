#include "../pch.h"
#include <sstream>

void Captain::handleCommand(const char* txt) {
	std::vector<std::string> args;
	std::stringstream stream;
	int i = 0;
	char in;
	while ((in = *(txt + i)) != 0) {
		//Keep reading until we find a null terminator
		if (in == ' ') {
			char* j;
			stream >> j;
			args.push_back(std::string(j));
		} else {
			stream << in;
		}
		i++;
	}
	char* j;
	stream >> j;
	args.push_back(std::string(j));

	//Args are now all of our arguments
	if (args.size() == 0) return;
	std::string command = args.at(0);
	if (command.compare("execute") == 0) {
		Beta::execute();
	} else if (command.compare("testrotate") == 0) {
		Beta::getmotor(0)->queue(20);
	}
}