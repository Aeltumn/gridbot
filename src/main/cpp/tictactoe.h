#pragma once
#include "pch.h"

class TicTacToe : public Game {
private:
	char COMPUTER;
	char HUMAN;
	bool FIRST;
	Difficulty DIFFICULTY;

	char board[3][3]; //0, 1 or 2
	int computer_turn = 0;
	int human_turn = 0;
	int suggestion = -1; //1-9, -1 is undefined

	void updateBoard(const int &suggestion_, const char &who);
	int getIndex(const int &x_, const int &z_);

public:
	TicTacToe(bool first_, Difficulty diff);
	void tick();
	void handleMove(const int &move);
	void execute(Motor *x, Motor *y, Motor *z);
	std::string getname() { return std::string("Tic Tac Toe"); }
};