#include <stdlib.h>
#include "board.h"

struct Board * new_board(int height, int width) {
	struct Board * board = malloc(sizeof(struct Board));

	board->board = malloc(sizeof(struct Square) * width * height);
	board->width = width;
	board->height = height;

	for (int r = 0; r < board->height; r++) {
		for (int c = 0; c < board->height; c++) {
			struct Square * sq = get_square(board, r, c);
			sq->c = c;
			sq->r = r;
			sq->data = NULL;
		}
	}

	return board;
}

void clear_board(struct Board * board) {
	for (int r = 0; r < board->height; r++) {
	   for (int c = 0; c < board->width; c++) {
			struct Square * sq = get_square(board, r, c);
			sq->c = c;
			sq->r = r;
			sq->display = ' ';
			sq->type = EMPTY;
			sq->data = NULL;
	   }
	}
}

void generate_walls(struct Board* board) {
	for(int r = 1; r < board->height; r+=2) {
		for(int c = 1; c < board->width; c+=2) {
			struct Square* sq = get_square(board, r, c);
			sq->type = BREAKABLE;
			sq->display = '#';
		}
	}
}

struct Square * get_square(struct Board * board, int row, int col) {
	return &board->board[row * board->width + col];
}
