#include <stdlib.h>
#include "board.h"

struct Board * new_board(int height, int width) {
	struct Board * board = malloc(sizeof(struct Board));

	board->board = malloc(sizeof(struct Square) * width * height);
	board->width = width;
	board->height = height;

	return board;
}

void clear_board(struct Board * board) {
	for (int r = 0; r < board->height; r++) {
	   for (int c = 0; c < board->width; c++) {
			struct Square * sq = &board->board[r * board->width + c];
			sq->x = c;
			sq->y = r;
			sq->display = ' ';
			sq->type = EMPTY;
			sq->data = NULL;
	   }
	}
}

struct Square * get_square(struct Board * board, int row, int col) {
	return &board->board[row * board->width + col];
}