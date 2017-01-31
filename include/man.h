#ifndef MAN_H
#define MAN_H

#include "board.h"
#include "bomb.h"

#define MAN_DISPLAY 'M'
#define DEAD_DISPLAY 'X'

struct Man {
	int r, c;
	int dR, dC;
	int hasBomb, isDead;
	struct Bomb bomb;
	char display;
	short colour;
	short capacity, dropped;
};

struct Man* new_man(int r, int c, struct Board* board, short colour);
void delete_man(struct Man* this, struct Board* board);
void man_up(struct Man* this);
void man_down(struct Man* this);
void man_left(struct Man* this);
void man_right(struct Man* this);
void get_bomb(struct Man* this);
int can_drop_bomb(struct Man* this);
void kill_man(struct Man* this);

#endif
