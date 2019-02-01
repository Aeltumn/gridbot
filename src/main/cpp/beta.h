#pragma once
#include "motor.h"
#include <string>
#include <string.h>

class Game {
public:
	Game() {}
	virtual void tick() = 0;
	virtual void handleMove(const int &move) = 0;
	virtual void execute(Motor *x, Motor *y, Motor *z) = 0;
	virtual std::string getname() = 0;
};

enum Difficulty {
	EASY, NORMAL, HARD
};

class Beta {
private:
	static Game* game;
	static bool isRunning;
	static Motor* x;
	static Motor* y;
	static Motor* z;

public:
	static void startup();
	static void shutdown();
	static void runGame(Game* g);
	static void setmotors(Motor *x_, Motor *y, Motor *z);
	static Motor* getmotor(const int &c);
	static void execute();
};