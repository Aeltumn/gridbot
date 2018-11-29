#include "../pch.h"
#include "tictactoe.h"

TicTacToe::TicTacToe(bool first_) { first = first_; }
void TicTacToe::tick() {
	
}

void TicTacToe::execute(Motor *x, Motor *y, Motor *z) {
	if (sug.x == -10 || sug.y == -10) return;
	turn++;

	sug = Suggestion(-10, -10);
}