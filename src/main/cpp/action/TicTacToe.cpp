#include "../headers/Beta.h"
#include "../headers/Motor.h"

struct Suggestion {
	int x;
	int y;
	//-10, -10 means NULL
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
		Suggestion getfinisher();
		Suggestion getblock();
		void tick();
		void execute(Motor *x, Motor *y, Motor *z);
};

/*
	IF FIRST:
	 1) Center
	 2)	if O = Edge:
			a) Non-bordering Corner
			b)	if not blocked: complete
				if blocked: block opponent
		if O = Corner:
			a) Opposite Corner
			b)	if O == Edge: block or non-bordering corner
				if O == Corner: block, TIE

	IF SECOND:
	1)	if center:
			1) Block or (non-bordering) corner
		else if corner:
			1) Center
			2) Block or edges
		else if edge:
			1) Center
			2) Block or (non-bordering) corner

	U U U	/\
	U U U   |
	U U U   y
	 x --->

	TIE MODE - Block opponent first, block plus pattern second
*/

TicTacToe::TicTacToe(bool first_) {
	first = first_;
}

void TicTacToe::tick() {
	//First things first: Check if we can finish.
	Suggestion finisher = getfinisher();
	if (finisher.x != -10 && finisher.y != -10) {
		sug = finisher;
		return;
	}

	//Do strategy, always block if nessecary
	Suggestion block = getblock();
	if (block.x != -10 && block.y != -10) {
		sug = block;
		return;
	}

	//Center if not claimed
	if (board[0][0] == 0) {
		sug = Suggestion(0, 0);
		return;
	}

	//If First:

}

void TicTacToe::execute(Motor *x, Motor *y, Motor *z) {
	if (sug.x == -10 || sug.y == -10) return;
	

	sug = Suggestion(-10, -10);
}

Suggestion TicTacToe::getfinisher() {
	for (int xrow = 1; xrow >= -1; --xrow) {
		int b = 0;
		int tarx = -10;
		for (int x = 1; x >= -1; --x) {
			if (board[x][xrow] == 1) b++;
			if (board[x][xrow] == 2) break;
			if (board[x][xrow] == 0) tarx = x;
		}
		if (tarx != -10 && b == 2) return Suggestion(tarx, xrow);
	}
	for (int yrow = 1; yrow >= -1; --yrow) {
		int b = 0;
		int tary = -10;
		for (int y = 1; y >= -1; --y) {
			if (board[yrow][y] == 1) b++;
			if (board[yrow][y] == 2) break;
			if (board[yrow][y] == 0) tary = y;
		}
		if (tary != -10 && b == 2) return Suggestion(yrow, tary);
	}
	for (int across = 1; across >= -1; across -= 2) { //Once for 1, once for -1
		int b = 0;
		int tarx = -10;
		for (int x = 1; x >= -1; --x) {
			if (board[x][x] == 1) b++;
			if (board[x][x] == 2) break;
			if (board[x][x] == 0) tarx = x;
		}
		if (tarx != -10 && b == 2) return Suggestion(tarx*across, tarx*across);
	}
	return Suggestion(-10, -10);
}

Suggestion TicTacToe::getblock() {
	for (int xrow = 1; xrow >= -1; --xrow) {
		int b = 0;
		int tarx = -10;
		for (int x = 1; x >= -1; --x) {
			if (board[x][xrow] == 2) b++;
			if (board[x][xrow] == 1) break;
			if (board[x][xrow] == 0) tarx = x;
		}
		if (tarx != -10 && b == 2) return Suggestion(tarx, xrow);
	}
	for (int yrow = 1; yrow >= -1; --yrow) {
		int b = 0;
		int tary = -10;
		for (int y = 1; y >= -1; --y) {
			if (board[yrow][y] == 2) b++;
			if (board[yrow][y] == 1) break;
			if (board[yrow][y] == 0) tary = y;
		}
		if (tary != -10 && b == 2) return Suggestion(yrow, tary);
	}
	for (int across = 1; across >= -1; across -= 2) { //Once for 1, once for -1
		int b = 0;
		int tarx = -10;
		for (int x = 1; x >= -1; --x) {
			if (board[x][x] == 2) b++;
			if (board[x][x] == 1) break;
			if (board[x][x] == 0) tarx = x;
		}
		if (tarx != -10 && b == 2) return Suggestion(tarx*across, tarx*across);
	}
	return Suggestion(-10, -10);
}