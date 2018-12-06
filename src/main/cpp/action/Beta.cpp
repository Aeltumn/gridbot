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
void Beta::runGame(Game* g) { game = g;Logger::info("[BETA] Starting new game."); }
void Beta::shutdown() {
	isRunning = false;
	delete game;
	Logger::info("[BETA] Shut down current game.");
}