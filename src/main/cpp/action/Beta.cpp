#include "../pch.h"

Game* Beta::game;
bool Beta::isRunning;
Motor* Beta::x;
Motor* Beta::y;
Motor* Beta::z;

void Beta::startup() {
	try {
		Logger::info("[BETA] Starting Beta thread.");
		isRunning = true;
		while (isRunning) {
			if (game != 0) game->tick();
		}
	} catch (const std::exception& e) {
		Logger::info(e.what());
		return;
	}
}

Motor* Beta::getmotor(const int &c) {
	if(c==0) return x;
	if(c==1) return y;
	if(c==2) return z;
	return nullptr;
}
void Beta::setmotors(Motor *x_, Motor *y_, Motor *z_) { x = x_; y = y_; z = z_; }
void Beta::execute() { 
	Logger::info("[BETA] Executing game step.");
	if (game != 0) game->execute(x, y, z);
}

#if defined(__linux__)
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
#else
void Beta::runGame(Game* g) {
	game = g;
	char buf[256];
	buf[0] = 0;
	strcat_s(buf, "[BETA] Starting new '");
	strcat_s(buf, game->getname().c_str());
	strcat_s(buf, "' game.");
	Logger::info(buf);
}
void Beta::shutdown() {
	char buf[256];
	buf[0] = 0;
	strcat_s(buf, "[BETA] Shut down '");
	strcat_s(buf, game->getname().c_str());
	strcat_s(buf, "' game.");
	Logger::info(buf);
	isRunning = false;
	delete game;
}
#endif