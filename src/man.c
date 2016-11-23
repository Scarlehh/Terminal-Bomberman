#include "man.h"
#include "board.h"
#include <stdlib.h>

struct Man* new_man(int r, int c) {
	struct Man* this = malloc(sizeof(struct Man));
	this->r = r;
	this->c = c;
	this->display = 'M';
	return this;
}

void delete_man(struct Man* this) {
	free(this);
}

void man_up(struct Man* this, struct Board* board) {
	struct Square* sq = get_square(board, this->r, this->c);
	sq->type = EMPTY;
	sq->display = ' ';

	// Update position
	this->r--;

	sq = get_square(board, this->r, this->c);
	sq->type = PLAYER;
	sq->display = this->display;
}

void man_down(struct Man* this, struct Board* board) {
	struct Square* sq = get_square(board, this->r, this->c);
	sq->type = EMPTY;
	sq->display = ' ';

	// Update position
	this->r++;

	sq = get_square(board, this->r, this->c);
	sq->type = PLAYER;
	sq->display = this->display;
}

void man_left(struct Man* this, struct Board* board) {
	struct Square* sq = get_square(board, this->r, this->c);
	sq->type = EMPTY;
	sq->display = ' ';

	// Update position
	this->c--;

	sq = get_square(board, this->r, this->c);
	sq->type = PLAYER;
	sq->display = this->display;
}

void man_right(struct Man* this, struct Board* board) {
	struct Square* sq = get_square(board, this->r, this->c);
	sq->type = EMPTY;
	sq->display = ' ';

	// Update position
	this->c++;

	sq = get_square(board, this->r, this->c);
	sq->type = PLAYER;
	sq->display = this->display;
}

