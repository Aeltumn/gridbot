#include "pch.h"
#include "tictactoe.h"

#define FIRST_PLAYER 'X'
#define SECOND_PLAYER 'O'

#define LOWER_HEIGHT 25
#define ENTRY_LENGTH 20

static const double SQUARE_HALF_LENGTH = 1.37;

TicTacToe::TicTacToe(bool first_) {
	FIRST = first_;
}
Board TicTacToe::createBoard() { return Board(3, 3); }

void TicTacToe::calculate() {
	//Where we figure out our next move
	if (suggestion != -1) return; //If the suggestion is -1 we've already calculated our move

}

bool TicTacToe::isTie(Board *board) {
	//We determine if it's a tie by seeing if there's no moves to be made. (no winner, no moves, a tie)
	for (int i = 0; i < board->getMaxIndex(); i++) {
		if (board->atIndex(i) == Figure::EMPTY) return false;
	}
	return true;
}
int TicTacToe::getWinner(Board *board) {
	//We determine the winner by absolute
}

//Executes the suggestion by sending cm-based commands to the motors.
//It is assumed we are hovering over the bottom left corner of the bottom left square, x0, y0 and at z100%, magnet off
//It is also assumed that there is a disc or object for it to move at x-1, y0
int TicTacToe::execute(Motor *x, Motor *y, Motor *z) {
	x->queue(ENTRY_LENGTH);

	//Move to pickup stone.
	x->queue(-3*SQUARE_HALF_LENGTH);
	z->queue(-LOWER_HEIGHT);
	//Enable magnet
	GPIO::set(10, true);
	z->queue(LOWER_HEIGHT);

	//Move to square
	x->queue(SQUARE_HALF_LENGTH*4); //We're at x0.5, y0.5 or above square 0,0
	// The tic tac toe board is on x2 y2
	
	int moveX = suggestion / 3, moveZ = suggestion % 3;
	x->queue(SQUARE_HALF_LENGTH*(2*(moveZ+2)));
	y->queue(SQUARE_HALF_LENGTH*(2*(moveX+2)));

	//Place here
	z->queue(-LOWER_HEIGHT);
	GPIO::set(10, false);
	z->queue(LOWER_HEIGHT);

	//Move back
	x->queue(-SQUARE_HALF_LENGTH*(2 * (moveZ + 2)));
	y->queue(-SQUARE_HALF_LENGTH*(2 * (moveX + 2)));

	//Move back to base?
	x->queue(-SQUARE_HALF_LENGTH);
	x->queue(-ENTRY_LENGTH);

	int sug = suggestion;
	suggestion = -1;
	return sug;
}