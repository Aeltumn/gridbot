#include "../pch.h"
#include <sstream>

void Captain::handleCommand(const char* txt) {
	std::vector<std::string> args;
	std::stringstream stream;
	int i = 0;
	char in;
	char* j;
	while ((in = *(txt + i)) != 0) {
		//Keep reading until we find a null terminator
		if (in == ' ') {
			Logger::info("Detected space, splitting args. Argument: ");
			stream >> j;
			Logger::info(j);
			args.push_back(std::string(j));
		} else {
			stream << in;
		}
		char buf[256];
		buf[0] = 0;
		strcat(buf, "[CAPTAIN] Read at i =  ");
		strcat(buf, std::to_string(i).c_str());
		strcat(buf, ".");
		Logger::info(buf);
		i++;
		if (i >= 512) break; // txt can't be larger than 512
	}
	stream >> j;
	args.push_back(std::string(j));

	//Args are now all of our arguments
	if (args.size() == 0) return;
	std::string command = args.at(0);
	if (command.compare("execute") == 0) { // Executes the next move.
		Beta::execute();
	} else if (command.compare("testmotors") == 0) {
		if (args.size() >= 3) {
			std::string axis = args.at(1);
			int i = std::stoi(args.at(2), nullptr, 10);
			char buf[256];
			buf[0] = 0;
			strcat(buf, "[CAPTAIN] Moving ");
			strcat(buf, std::to_string(i).c_str());
			strcat(buf, " centimetres .");
			Logger::info(buf);
			Beta::getmotor(axis.compare("x") == 0 ? 0 : axis.compare("y") == 0 ? 1 : 2)->queue(i);
			Logger::info("[CAPTAIN] Moved target axis target distance.");
		} else {
			Logger::error("[CAPTAIN] Invalid syntax! Use: testmotors x|y|z int");
		}
	} else if (command.compare("help") == 0) {
		Logger::info("[CAPTAIN] De volgende commands bestaan:");
		Logger::info("execute - Speelt de volgende beurt van het huidige spel.");
		Logger::info("testmotors x|y|z int - Beweeg de x, y of z as met int centimeter.");
	}
}