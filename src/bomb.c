#include <stdlib.h>
#include "bomb.h"
#include "man.h"

void init_bomb(struct Bomb* bomb, struct Man* owner) {
	bomb->strength = BOMB_STRENGTH_START;
	bomb->timer = BOMB_TIMER_START;
	bomb->owner = owner;
}

struct Bomb* clone_bomb(struct Bomb* toClone) {
	struct Bomb* clone = malloc(sizeof(struct Bomb));

	clone->strength = toClone->strength;
	clone->timer = toClone->timer;
	clone->owner = toClone->owner;

	return clone;
}

void free_bomb(struct Bomb* bomb) {
	bomb->owner->dropped--;
	free(bomb);
}
