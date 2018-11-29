#include "../headers/Beta.h"
#include "../headers/Motor.h"

Game Beta::*game;
bool Beta::isRunning;

void Beta::startup() {
	isRunning = true;
	while (isRunning) {
		if(game!=0) game->tick();
	}
}

void Beta::execute(Motor *x, Motor *y, Motor *z) { if (game != 0) game->execute(x, y, z); }
void Beta::runGame(Game* g) { game = g; }
void Beta::shutdown() {
	isRunning = false;
	delete game;
}