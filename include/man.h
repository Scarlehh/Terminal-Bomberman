#ifndef MAN_H
#define MAN_H

#include "board.h"
#include "bomb.h"

struct Man {
	int r, c;
	int dR, dC;
	int hasBomb;
	struct Bomb bomb;
	char display;
};

struct Man* new_man(int r, int c, struct Board* board);
void delete_man(struct Man* this);
void man_up(struct Man* this, struct Board* board);
void man_down(struct Man* this, struct Board* board);
void man_left(struct Man* this, struct Board* board);
void man_right(struct Man* this, struct Board* board);
void get_bomb(struct Man* this);

#endif
