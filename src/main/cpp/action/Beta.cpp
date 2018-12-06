#include "../pch.h"

Game* Beta::game;
bool Beta::isRunning;

void Beta::startup() {
	try {
		Logger::info("Starting Beta thread.");
		isRunning = true;
		while (isRunning) {
			if (game != 0) game->tick();
		}
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return;
	}
}

void Beta::execute(Motor *x, Motor *y, Motor *z) { if (game != 0) game->execute(x, y, z); }
void Beta::runGame(Game* g) {
	game = g;
	char buf[256];
	buf[0] = 0;
	strcat(buf, "[BETA] Starting new '");
	strcat(buf, game->getname().c_str());
	strcat(buf, "' game.");
	Logger::info(buf);
}
void Beta::shutdown() {
	char buf[256];
	buf[0] = 0;
	strcat(buf, "[BETA] Shut down '");
	strcat(buf, game->getname().c_str());
	strcat(buf, "' game.");
	Logger::info(buf);
	isRunning = false;
	delete game;
}