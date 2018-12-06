#pragma once
#include "pch.h"

struct Suggestion { //-10, -10 means NULL
	int x, y;
	Suggestion(const int &x_, const int &y_) { x = x_; y = y_; }
};

enum Difficulty {
	EASY, NORMAL, HARD
};

class TicTacToe : public Game {
private:
	char me;
	char opp;
	char currentboard[3][3];
	int turn = 0;
	bool first;
	Difficulty difficult;
	Suggestion sug = Suggestion(-10, -10);
	Suggestion gettiar(char* board, const char &c_, const char &o);
	Suggestion gettiarrow(char* board, const char &c_, const char &o, const int &N, const int &t);

public:
	TicTacToe(bool first_, Difficulty diff);
	void tick();
	void execute(Motor *x, Motor *y, Motor *z);
};