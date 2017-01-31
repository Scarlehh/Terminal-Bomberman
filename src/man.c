#include "man.h"
#include "board.h"
#include "bomb.h"
#include <stdlib.h>

struct Man* new_man(int r, int c, struct Board* board, short colour) {
	struct Man* this = malloc(sizeof(struct Man));
	// Initialise position
	this->r = r;
	this->c = c;
	// Set movement to nothing
	this->dR = 0;
	this->dC = 0;
	this->colour = colour;
	this->capacity = 1;
	this->dropped = 0;

	this->display = MAN_DISPLAY;
	this->hasBomb = 0;
	this->isDead = 0;
	init_bomb(&this->bomb, this);

	// Set attributes on square
	struct Square* sq = get_square(board, r, c);
	sq->type = PLAYER;
	sq->display = this->display;
	sq->data = this;

	clear_sides(board, r, c);
	return this;
}

void delete_man(struct Man* this, struct Board* board) {
	struct Square* sq = get_square(board, this->r, this->c);
	sq->type = EMPTY;
	sq->display = ' ';
	sq->data = NULL;

	free(this);
}

void man_up(struct Man* this) {
	this->dC=0;
	this->dR=-1;
}

void man_down(struct Man* this) {
	this->dC=0;
	this->dR=1;
}

void man_left(struct Man* this) {
	this->dR=0;
	this->dC=-1;
}

void man_right(struct Man* this) {
	this->dR=0;
	this->dC=1;
}

void get_bomb(struct Man* this) {
	if(this->dropped != this->capacity) {
		this->hasBomb = 1;
	}
}

int can_drop_bomb(struct Man* this) {
	if(this->hasBomb && this->dropped != this->capacity) {
		this->dropped++;
		return 1;
	}
	return 0;
}

void kill_man(struct Man* this) {
	this->isDead = 1;
	this->display = DEAD_DISPLAY;
}
