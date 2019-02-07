#pragma once
#include "pch.h"

class TicTacToe : public Game {
private:
	bool FIRST;
	int suggestion = -1; //1-9, -1 is undefined

	bool isTie(Board *board);
	int getWinner(Board *board);

public:
	TicTacToe(bool first_);
	Board createBoard();
	void calculate();
	int execute(Motor *x, Motor *y, Motor *z);
	std::string getname() { return std::string("Tic Tac Toe"); }
};