#include "../pch.h"
#include "tictactoe.h"

TicTacToe::TicTacToe(bool first_, Difficulty diff) {
	first = first_; difficult = diff;
	if (first) { me = 'X'; opp = 'O'; }
	else { me = 'O'; opp = 'X'; }
}
void TicTacToe::tick() {
	
}

void TicTacToe::execute(Motor *x, Motor *y, Motor *z) {
	if (sug.x == -1 || sug.y == -1) return;
	turn++;

	sug = Suggestion(-1, -1);
}

Suggestion TicTacToe::gettiar(char* board, const char &c_, const char &o) {
	for (int N = 2; N >= 0; --N) {
		Suggestion ret = gettiarrow(board, c_, o, N, 3);
		if (ret.x == -1 && ret.y == -1) ret = gettiarrow(board, c_, o, N * 3, 1);
		if (ret.x == -1 && ret.y == -1 && N != 0) ret = gettiarrow(board, c_, o, N-10, -1);
	}
}

Suggestion TicTacToe::gettiarrow(char* board, const char &c_, const char &o, const int &N, const int &t) {
	int tarJ = -1;
	int b = 0;
	for (int J = 2; J >= 0; --J) {
		if (*(board + (t != -1 ? (N + t * J) : (N == -8 && J == 0 ? 0 : J) + (N == -8 && J == 2 ? 0 : J) * 3)) == c_) b++;
		if (*(board + (t != -1 ? (N + t * J) : (J + (N == -8 ? 0 : J) * 3))) != o) tarJ = J - 1;
	}

	if (b == 2 && tarJ != -1) return Suggestion(N, tarJ);
	return Suggestion(-1, -1);
}