#pragma once
#include "../gpio/motor.h"

class Game {
public:
	Game() {}
	virtual void tick() = 0;
	virtual void handleMove(const int &move) = 0;
	virtual void execute(Motor *x, Motor *y, Motor *z) = 0;
};

enum Difficulty {
	EASY, NORMAL, HARD
};

class Beta {
public:
	static void startup();
	static void shutdown();
	static void runGame(Game* g);
	static void execute(Motor *x, Motor *y, Motor *z);

private:
	static Game* game;
	static bool isRunning;
};