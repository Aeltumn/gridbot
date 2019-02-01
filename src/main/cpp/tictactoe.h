#pragma once
#include "pch.h"

struct Suggestion { //-10, -10 means NULL
	int x, y;
	Suggestion() {}
	Suggestion(const int &x_, const int &y_) { x = x_; y = y_; }
};

class TicTacToe : public Game {
private:
	char COMPUTER;
	char HUMAN;
	bool FIRST;
	Difficulty DIFFICULTY;

	char board[3][3];
	int computer_turn = 0;
	int human_turn = 0;
	Suggestion suggestion = Suggestion();

	void updateBoard(const Suggestion &suggestion_, const char &who);

public:
	TicTacToe(bool first_, Difficulty diff);
	void tick();
	void handleMove(const int &move);
	void execute(Motor *x, Motor *y, Motor *z);
	std::string getname() { return std::string("Tic Tac Toe"); }
};