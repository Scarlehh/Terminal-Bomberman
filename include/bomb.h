#ifndef BOMB_H
#define BOMB_H

#include "physics.h"

const int BOMB_STRENGTH_START = 3;
const int BOMB_TIMER_START = 0 * TICKS_PER_SECOND;
const int BOMB_TIMER_END = 3 * TICKS_PER_SECOND;
const char BOMB_DISPLAY = '@';

struct Bomb {
	int strength;
	int timer;
};

void init_bomb(struct Bomb *);
struct Bomb * clone_bomb(struct Bomb *);
void free_bomb(struct Bomb *);

#endif
