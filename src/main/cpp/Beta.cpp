#include "pch.h"

Game* Beta::game = NULL;
Board* Beta::board = NULL;
bool Beta::isRunning;
Motor* Beta::x;
Motor* Beta::y;
Motor* Beta::z;
std::stack<int> Beta::history;

void Beta::startup() {
	try {
		Logger::info("[BETA] Starting Beta thread.");
		while (true) {
			if (board != NULL && game != NULL) game->calculate(board); //The game calculate can last as long as it wants so we don't need to worry about aborting the search algorithms and continuing later.
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
		Logger::info("[BETA] Executing game step.");
		game->execute(x, y, z, board);
	}
}
void Beta::handleAIMove(const int &move) {
	board->set(move, Figure::AI);
}
void Beta::rollback() {
	if (game != 0) {
		Logger::info("[BETA] Rolling back last move.");
		int lastMove = history.top();
		history.pop();
		board->set(lastMove, Figure::EMPTY);
		game->allow(); //Allow thinking about next step
		handleAIMove(game->getSuggestion());
	}
}
void Beta::handleMove(const int &move) {
	if (game != 0) {
		Logger::info("[BETA] Registered opponent move.");
		history.push(move);
		board->set(move, Figure::HUMAN);
		game->allow(); //Allow thinking about next step
		handleAIMove(game->getSuggestion());
	}
}

void Beta::runGame(Game* g) {
	if (isRunning) return;
	game = g;
	board = g->createBoard();
	char buf[256];
	buf[0] = 0;
	strcat(buf, "[BETA] Starting new '");
	strcat(buf, game->getname().c_str());
	strcat(buf, "' game.");
	Logger::info(buf);
	game->initialise();
	isRunning = true;
}
void Beta::shutdown() {
	char buf[256];
	buf[0] = 0;
	strcat(buf, "[BETA] Shut down '");
	strcat(buf, game->getname().c_str());
	strcat(buf, "' game.");
	Logger::info(buf);
	isRunning = false;
	//delete game;
	//board->destroy();
	//delete board;
	game = NULL;
	board = NULL;
}