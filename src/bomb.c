#include <stdlib.h>
#include "bomb.h"

void init_bomb(struct Bomb * bomb) {
	bomb->strength = BOMB_STRENGTH_START;
	bomb->timer = BOMB_TIMER_START;
}

struct Bomb * clone_bomb(struct Bomb * toClone) {
	struct Bomb * clone = malloc(sizeof(struct Bomb));

	clone->strength = toClone->strength;
	clone->timer = toClone->timer;

	return clone;
}

void free_bomb(struct Bomb * bomb) {
	free(bomb);
}
