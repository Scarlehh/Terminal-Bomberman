#ifndef BOMB_H
#define BOMB_H

#include "physics.h"

#define BOMB_STRENGTH_START 3
#define BOMB_TIMER_START 0 * TICKS_PER_SECOND
#define BOMB_TIMER_END 3 * TICKS_PER_SECOND
#define BOMB_DISPLAY '@'

struct Bomb {
	int strength;
	int timer;
	struct Man* owner;
};

void init_bomb(struct Bomb* bomb, struct Man* owner);
struct Bomb* clone_bomb(struct Bomb* toClone);
void free_bomb(struct Bomb* bomb);

#endif
