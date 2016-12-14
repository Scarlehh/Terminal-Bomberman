#include <pthread.h>

#include "physics.h"
#include "bomb.h"
#include "man.h"
#include "board.h"

int valid_move(struct Board * board, struct Man * man);
int explode_bomb(struct Square* sq, struct Board* board);
void * physics_loop(void * arg);

pthread_t last_started;

int start_physics(struct Board * board) {
	return pthread_create(&last_started, NULL, physics_loop, board);
}

int stop_physics() {
	int ret;

	if (!(ret = pthread_cancel(last_started))) {
		pthread_join(last_started, NULL);
	}

	return ret;
}

int valid_move(struct Board * board, struct Man * man) {
	// Not moving
	if(man->dR == 0 && man->dC == 0) {
		return 0;
	}
	// Check if moving diagonally
	if(man->dR != 0 && man->dC != 0) {
		return 0;
	}
	int newr = man->r + man->dR;
	int newc = man->c + man->dC;
	if(newr < 0 || newc < 0 || newr >= board->height
	   || newc >= board->width) {
		return 0;
	}

	struct Square* sq = get_square(board, newr, newc);
	enum SquareType sq_type = sq->type;
	if(sq_type == EMPTY || sq_type == MELTING) {
		return 1;
	}

	return 0;
}

int explode_bomb(struct Square* sq, struct Board* board) {
	enum SquareType type = sq->type;
	if (type == BLOCK) {
		return 1;
	}
	sq->type = MELTING;
	if (type == BREAKABLE){
		sq->data = 0;
		return 1;
	}
	else if (type == PLAYER) {
		kill_man(sq->data, board);
		sq->data = 0;
	}
	return 0;
}

void * physics_loop(void * arg) {
	struct Board * board = arg;
	struct timespec t;
	struct Square * sq;

	int width = board->width;
	int height = board->height;
	t.tv_sec = 0;
	t.tv_nsec = NANOS_PER_TICK;

	while (1) {
		nanosleep(&t, NULL);
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				sq = get_square(board, r, c);
				if (sq->type == MELTING) {
					if ((long) sq->data >= MELT_TIMER) {
						sq->type = EMPTY;
						sq->display = ' ';
						sq->data = NULL;
					} else {
						sq->data++;
					}
				}
			}
		}

		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				sq = get_square(board, r, c);
				switch (sq->type) {
				case BOMB:
					; // for fuck's sake C
					struct Bomb * bomb = sq->data;
					if (bomb->timer >= BOMB_TIMER_END) {
						struct Square * sq1;
						for (int dR = 0; dR < bomb->strength && r + dR < board->width; dR++) {
							if(explode_bomb(get_square(board, r + dR, c), board)) {
								break;
							}
						}

						for (int dR = 1; dR < bomb->strength && r - dR >= 0; dR++) {
							if(explode_bomb(get_square(board, r - dR, c), board)) {
								break;
							}
						}

						for (int dC = 0; dC < bomb->strength && c + dC < board->height; dC++) {
							if(explode_bomb(get_square(board, r, c + dC), board)) {
								break;
							}
						}

						for (int dC = 1; dC < bomb->strength && c - dC >= 0; dC++) {
							if(explode_bomb(get_square(board, r, c - dC), board)) {
								break;
							}
						}
					} else {
						bomb->timer++;
					}
					break;
				case PLAYER:
					;
					struct Man * man = sq->data;

					// validate movement
					if (valid_move(board, man)) {
						if (man->hasBomb) {
							sq->data = clone_bomb(&man->bomb);
							sq->display = BOMB_DISPLAY;
							sq->type = BOMB;

							man->hasBomb = 0;
						} else {
							// Replace square with empty
							sq->type = EMPTY;
							sq->display = ' ';
							sq->data = NULL;
						}
						int newr = man->r + man->dR;
						int newc = man->c + man->dC;

						// Redraw man
						struct Square* new_sq = get_square(board, newr, newc);
						new_sq->type = PLAYER;
						new_sq->display = man->display;
						new_sq->data = man;

						// Update man's position + movement
						man->r = newr;
						man->c = newc;
					}
					man->dR = 0;
					man->dC = 0;
					break;
				default:
					break;
				}
			}
		}
	}
}
