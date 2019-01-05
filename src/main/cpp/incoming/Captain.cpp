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
	if (command.compare("execute") == 0) { // Executes the next move.
		Beta::execute();
	} else if (command.compare("testmotors") == 0) {
		if (args.size() >= 3) {
			std::string axis = args.at(1);
			int i = std::stoi(args.at(2), nullptr, 10);
			char buf[256];
			buf[0] = 0;
			strcat_s(buf, "[CAPTAIN] Moving ");
			strcat_s(buf, std::to_string(i).c_str());
			strcat_s(buf, " centimetres .");
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