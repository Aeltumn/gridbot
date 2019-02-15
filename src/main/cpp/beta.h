#pragma once
#include "motor.h"
#include <string>
#include <string.h>

enum Figure { EMPTY = 0, HUMAN = 1, AI = 2 };

class Board {
private:
	int width, height;
	double half_square;
	int *board = NULL; //2d array of integers
	
public:
	//width = x, height = y
	Board(const int &width_, const int &height_, const double &half_square_) {
		width = width_; height = height_; half_square = half_square_;
		board = new int[width*height];
		for (int i = 0; i < width*height; i++) {
			set(i, Figure::EMPTY);
		}
	}
	void set(const int &index, Figure figure) {
		*(board + index) = figure;
	}
	Figure at(const int &x, const int &y) { return static_cast<Figure>(*(board + getIndex(x, y))); }
	Figure atIndex(const int &index) { 
		checkValidIndex(index);
		return static_cast<Figure>(*(board + index));
	}
	int getMaxIndex() { return width * height; }
	double getHalfSquareLength() { return half_square; }
	int getIndex(const int &x, const int &y) { 
		int ret = x * width + y;
		checkValidIndex(ret);
		return ret;
	}
	int getXFromIndex(const int &index) { return (index / width); }
	int getYFromIndex(const int &index) { return (index % width); }
	void destroy() {
		delete[] board;
		board = NULL;
	}
	void checkValidIndex(const int &index) {
		if (index >= getMaxIndex()) {
			char buf[256];
			buf[0] = 0;
			strcat(buf, "[BOARD] Found invalid index of '");
			strcat(buf, std::to_string(index).c_str());
			strcat(buf, "' game.");
			Logger::error(buf);
		}
	}
};

class Game {
public:
	Game() {}
	virtual Board* createBoard() = 0;
	virtual void initialise() = 0;
	virtual void allow() = 0;
	virtual void calculate(Board *board) = 0;
	virtual int getSuggestion() = 0;
	virtual void execute(Motor *x, Motor *y, Motor *z, Board *board) = 0;
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
	static void handleAIMove(const int &move);
};