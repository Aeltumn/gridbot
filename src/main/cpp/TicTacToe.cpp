#include "pch.h"
#include "tictactoe.h"

#define FIRST_PLAYER 'X'
#define SECOND_PLAYER 'O'

#define LOWER_HEIGHT 25
#define ENTRY_LENGTH 20

TicTacToe::TicTacToe(bool first_) {
	FIRST = first_;
	if (!FIRST) suggestion = -2;
}
void TicTacToe::initialise() {
	if(FIRST) Beta::handleAIMove(getSuggestion());
}
Board* TicTacToe::createBoard() { return new Board(3, 3, 3.25); }

void TicTacToe::allow() { suggestion = -1; }
void TicTacToe::calculate(Board *board) {
	//Where we figure out our next move
	if (suggestion != -1) return; //If the suggestion isn't -1 we've already calculated our move
	Logger::info("[TICTACTOE] Starting calculation...");
	if (!isTie(board) && !isGameOver(board)) {
		suggestion = calculateBestMove(board, true, true);
	} else {
		Logger::info("[TICTACTOE] Game is a tie or has ended.");
		Beta::shutdown();
		return;
	}
	if (suggestion < 0 || suggestion > 8) {
		char buf[256];
		buf[0] = 0;
		strcat(buf, "[TICTACTOE] Invalid suggested move of '");
		strcat(buf, std::to_string(suggestion).c_str());
		strcat(buf, "'...");
		Logger::error(buf);
		Beta::shutdown();
		return;
	}
	char buf[256];
	buf[0] = 0;
	strcat(buf, "[TICTACTOE] Determined next move to be index '");
	strcat(buf, std::to_string(suggestion).c_str());
	strcat(buf, "'.");
	Logger::info(buf);
}

// Our recursive method to find the best outcome.
int TicTacToe::calculateBestMove(Board *board, bool surface, bool ai) {
	std::vector<Entry> cdf (board->getMaxIndex());
	//Firstly if the state of the game is tied or a win were at the end of our tree and we return back up.
	if (isTie(board)) return 0;
	else if (isGameOver(board)) return -10;
	else {
		//Try all possible moves and grade them.
		for (int s = 0; s < board->getMaxIndex(); s++) {
			if (board->atIndex(s) != 0) {
				if (surface) {
					char buf[256];
					buf[0] = 0;
					strcat(buf, "[TICTACTOE] Move possibility s of '");
					strcat(buf, std::to_string(s).c_str());
					strcat(buf, "' is taken by figure '");
					Figure f = static_cast<Figure>(board->atIndex(s));
					strcat(buf, std::to_string(f).c_str());
					strcat(buf, "'...");
					Logger::info(buf);
				}
				continue;
			}
			board->set(s, ai ? Figure::AI : Figure::HUMAN);
			int score = -1 * calculateBestMove(board, false, !ai);
			cdf.push_back(Entry(s, score)); //We switch the value of the other player, min->max, max->min
			board->set(s, Figure::EMPTY);
			if (surface) {
				char buf[256];
				buf[0] = 0;
				strcat(buf, "[TICTACTOE] Move possibility s of '");
				strcat(buf, std::to_string(s).c_str());
				strcat(buf, "' has score '");
				strcat(buf, std::to_string(score).c_str());
				strcat(buf, "'...");
				Logger::info(buf);
			}
		}

		Entry max = Entry(-2, -200);
		for (int i = 0; i < cdf.size(); i++)
			if (cdf.at(i).value >= max.value) max = cdf.at(i);
		if (surface) return max.key;
		else return max.value;
	}
}

int TicTacToe::getSuggestion() {
	if (suggestion == -1) {
		Logger::info("[TICTACTOE] Waiting on calculation for next move...");
	}
	while (suggestion == -1) {}
	return suggestion;
}

bool TicTacToe::isTie(Board *board) {
	//We determine if it's a tie by seeing if there's no moves to be made. (no winner, no moves, a tie)
	for (int i = 0; i < board->getMaxIndex(); i++) {
		if (board->atIndex(i) == Figure::EMPTY) return false;
	}
	return true;
}
bool TicTacToe::isGameOver(Board *board) {
	//We determine the winner by absolute mad methods, we're going to assume two wins can't happen at the same time.
	Figure ret = static_cast<Figure>(0);
	//X-ways
	ret = testLine(board, ret, 0, 3, 6);
	ret = testLine(board, ret, 1, 4, 7);
	ret = testLine(board, ret, 2, 5, 8);

	//Y-ways
	ret = testLine(board, ret, 0, 1, 2);
	ret = testLine(board, ret, 3, 4, 5);
	ret = testLine(board, ret, 6, 7, 8);

	//Diagonal
	ret = testLine(board, ret, 0, 4, 8);
	ret = testLine(board, ret, 2, 4, 6);
	return (ret == Figure::HUMAN || ret == Figure::AI);
}

Figure TicTacToe::testLine(Board *board, const Figure &ret, int i, int j, int k) {
	Figure r = board->atIndex(i);
	if (r != board->atIndex(j)) r = static_cast<Figure>(0);
	if (r != board->atIndex(k)) r = static_cast<Figure>(0);
	if (r != 0) return r;
	else return ret;
}

//Executes the suggestion by sending cm-based commands to the motors.
//It is assumed we are hovering over the bottom left corner of the bottom left square, x0, y0 and at z100%, magnet off
//It is also assumed that there is a disc or object for it to move at x-1, y0
void TicTacToe::execute(Motor *x, Motor *y, Motor *z, Board *board) {
	double SQUARE_HALF_LENGTH = board->getHalfSquareLength();
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
}