#ifndef MAN_H
#define MAN_H

#include "board.h"

struct Man {
	int r, c;
	char display;
};

struct Man* new_man(int r, int c);
void delete_man(struct Man* this);
void man_up(struct Man* this, struct Board* board);
void man_down(struct Man* this, struct Board* board);
void man_left(struct Man* this, struct Board* board);
void man_left(struct Man* this, struct Board* board);

#endif
