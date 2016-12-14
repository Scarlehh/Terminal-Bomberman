#ifndef PHYSICS_H
#define PHYSICS_H

#include <time.h>
#include "board.h"

const int TICKS_PER_SECOND = 20;
const int NANOS_PER_SECOND = 1000000000;
const int NANOS_PER_TICK = NANOS_PER_SECOND / TICKS_PER_SECOND;
const int MELT_TIMER = 1 * TICKS_PER_SECOND;

int start_physics(struct Board * board);
int stop_physics();

#endif
