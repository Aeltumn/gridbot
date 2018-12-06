#include "../pch.h"

Game* Beta::game;
bool Beta::isRunning;

void Beta::startup() {
	try {
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
void Beta::runGame(Game* g) { game = g; }
void Beta::shutdown() {
	isRunning = false;
	delete game;
}