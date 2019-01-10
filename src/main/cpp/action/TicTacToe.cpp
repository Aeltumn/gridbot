#include "../pch.h"
#include "tictactoe.h"

#define FIRST_PLAYER 'X'
#define SECOND_PLAYER 'O'

#define SQUARE_HALF_LENGTH 1.375
#define LOWER_HEIGHT 2


TicTacToe::TicTacToe(bool first_, Difficulty diff) {
	FIRST = first_; DIFFICULTY = diff;
	COMPUTER = FIRST ? FIRST_PLAYER : SECOND_PLAYER;
	HUMAN = FIRST ? SECOND_PLAYER : FIRST_PLAYER;
}

//Updates the board and increased the turn counter.
void TicTacToe::updateBoard(const Suggestion &suggestion_, const char &who) {
	board[suggestion_.x][suggestion_.y] = who;
	if (who == COMPUTER) {
		computer_turn++;
		suggestion = Suggestion();
	}
	if (who == HUMAN) { human_turn++; }
}

//Handles the incoming move, template for TicTacToe: int x: 0x16 - y: 0x16
void TicTacToe::handleMove(const int &move) { updateBoard(Suggestion(move >> 16, (move << 16 >> 16)), HUMAN); }

//The normal tick which tries to figure out what the next move should be.
void TicTacToe::tick() {
	
}

//Executes the suggestion by sending cm-based commands to the motors.
//It is assumed we are hovering over the bottom left corner of the bottom left square, x0, y0 and at z100%, magnet off
//It is also assumed that there is a disc or object for it to move at x-1, y0
void TicTacToe::execute(Motor *x, Motor *y, Motor *z) {
	//Move to pickup stone.
	x->queue(-SQUARE_HALF_LENGTH);
	y->queue(SQUARE_HALF_LENGTH);
	z->queue(-LOWER_HEIGHT);
	//Enable magnet
	GPIO::set(10, true);

	z->queue(LOWER_HEIGHT);

	//Move to square
	x->queue(SQUARE_HALF_LENGTH*2); //We're at x0.5, y0.5 or above square 0,0
	
	//Place here
	z->queue(-LOWER_HEIGHT);
	GPIO::set(10, false);
	z->queue(LOWER_HEIGHT);

	//Move back to base?

	updateBoard(suggestion, COMPUTER);
}