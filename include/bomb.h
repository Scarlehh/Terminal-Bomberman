#ifndef BOMB_H
#define BOMB_H

#define BOMB_STRENGTH_START 3
#define BOMB_TIMER_START 0

struct Bomb {
	int strength;
	int timer;
};

void init_bomb(struct Bomb *);

#endif
