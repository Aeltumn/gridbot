#include "pch.h"

Game* Beta::game;
Board* Beta::board = NULL;
bool Beta::isRunning;
Motor* Beta::x;
Motor* Beta::y;
Motor* Beta::z;

void Beta::startup() {
	try {
		Logger::info("[BETA] Starting Beta thread.");
		while (true) {
			if (game != 0) game->calculate(board); //The game calculate can last as long as it wants so we don't need to worry about aborting the search algorithms and continuing later.
		}
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return;
	}
}

//The motors have indexes, 0 = X, 1 = Y, 2 = Z, unknown will default to X
Motor* Beta::getmotor(const int &c) {
	if(c==1) return y;
	if(c==2) return z;
	return x;
}
void Beta::setmotors(Motor *x_, Motor *y_, Motor *z_) { x = x_; y = y_; z = z_; }
void Beta::execute() { 
	if (game != 0) {
		int move = game->execute(x, y, z);
		board->set(move, Figure::AI);
		Logger::info("[BETA] Executing game step.");
	}
}
void Beta::handleMove(const int &move) {
	if (game != 0) {
		Logger::info("[BETA] Registered opponent move.");
		board->set(move, Figure::HUMAN);
	}
}

void Beta::runGame(Game* g) {
	game = g;
	board = g->createBoard();
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
	delete board;
	game = NULL;
	board = NULL;
}