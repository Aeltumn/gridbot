#pragma once
#include "pch.h"

struct Entry {
	int key, value;
	Entry(int key_, int value_) { key = key_; value = value_; }
};

class TicTacToe : public Game {
private:
	bool FIRST;
	int suggestion = -1; //1-9, -1 is undefined

	void allow();
	bool isTie(Board *board);
	bool isGameOver(Board *board);
	void testLine(Board *board, Figure *ret, int i, int j, int k);
	int calculateBestMove(Board *board, bool surface, bool ai); //the bool ai is whether or not we are the one this move is for (max) or its for the human (min)

public:
	TicTacToe(bool first_);
	void initialise();
	Board* createBoard();
	void calculate(Board *board);
	int getSuggestion();
	void execute(Motor *x, Motor *y, Motor *z, Board *board);
	std::string getname() { return std::string("Tic Tac Toe"); }
};