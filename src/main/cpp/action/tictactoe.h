#pragma once
#include "../pch.h"

struct Suggestion { //-10, -10 means NULL
	int x, y;
	Suggestion(const int &x_, const int &y_) { x = x_; y = y_; }
};

class TicTacToe : public Game {
private:
	int board[3][3];
	int turn = 0;
	bool first;
	Suggestion sug = Suggestion(-10, -10);

public:
	TicTacToe(bool first_);
	void tick();
	void execute(Motor *x, Motor *y, Motor *z);
};