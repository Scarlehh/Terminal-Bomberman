#include "man.h"
#include "board.h"
#include "bomb.h"
#include <stdlib.h>

struct Man* new_man(int r, int c, struct Board* board) {
	struct Man* this = malloc(sizeof(struct Man));
	// Initialise position
	this->r = r;
	this->c = c;
	// Set movement to nothing
	this->dR = 0;
	this->dC = 0;
	
	this->display = 'M';
	this->hasBomb = 0;
	this->isDead = 0;

	// Set attributes on square
	struct Square* sq = get_square(board, r, c);
	sq->type = PLAYER;
	sq->display = this->display;
	sq->data = this;

	init_bomb(&this->bomb);
	return this;
}

void delete_man(struct Man* this) {
	free(this);
}

void move_man(struct Man* this, struct Board* board, int newr, int newc) {
	struct Square* sq = get_square(board, this->r, this->c);
	if(this->hasBomb) {
		sq->type = BOMB;
		sq->display = '@';
		sq->data = 0;
		this->hasBomb = 0;
	} else {
		sq->type = EMPTY;
		sq->display = ' ';
	}

	sq = get_square(board, newr, newc);
	sq->type = PLAYER;
	sq->display = this->display;

	this->r = newr;
	this->c = newc;
}

void man_up(struct Man* this, struct Board* board) {
	this->dR--;
	//move_man(this, board, this->r-1, this->c);
}

void man_down(struct Man* this, struct Board* board) {
	this->dR++;
	//move_man(this, board, this->r+1, this->c);
}

void man_left(struct Man* this, struct Board* board) {
	this->dC--;
	//move_man(this, board, this->r, this->c-1);
}

void man_right(struct Man* this, struct Board* board) {
	this->dC++;
	//move_man(this, board, this->r, this->c+1);
}

void get_bomb(struct Man* this) {
	this->hasBomb = 1;
}

void kill_man(struct Man* this, struct Board* board) {
	this->isDead = 1;
	struct Square* sq = get_square(board, this->r, this->c);
	sq->type = EMPTY;
	sq->display = 'X';
}
