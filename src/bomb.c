#include "bomb.h"

void init_bomb(struct Bomb * bomb) {
	bomb->strength = BOMB_STRENGTH_START;
	bomb->timer = BOMB_TIMER_START;
}
