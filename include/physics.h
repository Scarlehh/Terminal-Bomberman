#ifndef PHYSICS_H
#define PHYSICS_H

#include "board.h"

#define TICKS_PER_SECOND 20
#define NANOS_PER_SECOND 1000000000
#define NANOS_PER_TICK NANOS_PER_SECOND / TICKS_PER_SECOND
#define MELT_TIMER 1 * TICKS_PER_SECOND

struct Timer {
	int timer;
	struct Square* nextSquare;
};

struct Timer* init_timer(struct Square* nextSquare);
void delete_timer(struct Timer* timer);
int start_physics(struct Board * board);
int stop_physics();

#endif
