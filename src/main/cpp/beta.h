#pragma once
#include "motor.h"
#include <string>
#include <string.h>

enum Figure { EMPTY = 0, HUMAN = 1, AI = 2 };

class Board {
private:
	int width, height;
	int *board = NULL; //2d array of integers
	
public:
	//width = x, height = y
	Board(const int &width_, const int &height_) {
		width = width_; height = height_;
		board = new int[width*height];
	}
	void set(const int &index, Figure figure) {
		*(board + index) = figure;
	}
	Figure at(const int &x, const int &y) { return static_cast<Figure>(*(board + getIndex(x, y))); }
	Figure atIndex(const int &index) { return static_cast<Figure>(*(board + index)); }
	int getMaxIndex() { return width * height; }
	int getIndex(const int &x, const int &y) {return x + y * width; }
	int getXFromIndex(const int &index) { return (index % width); }
	int getYFromIndex(const int &index) { return (index / width); }
	void destroy() {
		delete[] board;
		board = NULL;
	}
};

class Game {
public:
	Game() {}
	virtual Board* createBoard() = 0;
	virtual void allow() = 0;
	virtual void calculate(Board *board) = 0;
	virtual int getSuggestion() = 0;
	virtual void execute(Motor *x, Motor *y, Motor *z) = 0;
	virtual std::string getname() = 0;
};

class Beta {
private:
	static Game* game;
	static Board* board;
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
	static void handleMove(const int &move);
};