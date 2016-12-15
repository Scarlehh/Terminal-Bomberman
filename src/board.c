#include <stdlib.h>
#include "board.h"

struct Board * new_board(int height, int width) {
	struct Board * board = malloc(sizeof(struct Board));

	board->board = malloc(sizeof(struct Square) * width * height);
	board->width = width;
	board->height = height;

	for (int r = 0; r < board->height; r++) {
		for (int c = 0; c < board->width; c++) {
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

void clear_sides(struct Board* board, int r, int c) {
	struct Square* sq;
	if(r > 0) {
		sq = get_square(board, r-1, c);
		sq->display = ' ';
		sq->type = EMPTY;
		sq->data = NULL;
	}
	if(r+1 < board->height) {
		sq = get_square(board, r+1, c);
		sq->display = ' ';
		sq->type = EMPTY;
		sq->data = NULL;
	}
	if(c > 0) {
		sq = get_square(board, r, c-1);
		sq->display = ' ';
		sq->type = EMPTY;
		sq->data = NULL;
	}
	if(c+1 < board->width) {
		sq = get_square(board, r, c+1);
		sq->display = ' ';
		sq->type = EMPTY;
		sq->data = NULL;
	}
}

void generate_walls(struct Board* board) {
	time_t t;
	/* Intializes random number generator */
	srand((unsigned) time(&t));

	for(int r = 0; r < board->height; r++) {
		for(int c = 0; c < board->width; c++) {
			struct Square* sq = get_square(board, r, c);
			// Leave perimeter open
			if((r+1)%2==0 && (c+1)%2 == 0) {
				sq->type = BLOCK;
				sq->display = BLOCK_DISPLAY;
			}
			else if(rand()%3 < 1) {
				sq->type = BREAKABLE;
				sq->display = BLOCK_DISPLAY;
			}
		}
	}
}

struct Square * get_square(struct Board * board, int row, int col) {
	return &board->board[row * board->width + col];
}
