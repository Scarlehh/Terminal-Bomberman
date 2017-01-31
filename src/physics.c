#include <pthread.h>

#include <stdlib.h>
#include "physics.h"
#include "bomb.h"
#include "man.h"
#include "board.h"

int valid_move(struct Board * board, struct Man * man);
int explode_bomb(struct Square* sq, struct Board* board);
void detonate_bomb(struct Board* board, int r, int c, struct Bomb* bomb);
void * physics_loop(void * arg);

pthread_t last_started;

struct Timer* init_timer(struct Square* nextSquare) {
	struct Timer* timer = malloc(sizeof(struct Timer));
	timer->timer = 0;
	timer->nextSquare = nextSquare;
	return timer;
}

void delete_timer(struct Timer* timer) {
	free(timer);
}

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
	// Moving too much
	if(man->dR > 1 || man->dR < -1 ||
	   man->dC > 1 || man->dC < -1) {
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

// Returns 1 if hits an obstacle
int explode_bomb(struct Square* sq, struct Board* board) {
	enum SquareType type = sq->type;

	// If block, stop flames
	if (type == BLOCK) {
		return 1;

	// If bomb, detonate and stop flames
	} else if (type == BOMB) {
		detonate_bomb(board, sq->r, sq->c, sq->data);
		return 1;
	}

	// If bombs flames overlap
	else if(type == MELTING || type == MELTING_OBJ) {
		struct Timer* timer = sq->data;
		timer->timer = 0;
		return 0;
	}

	if(sq->type == BREAKABLE) {
		sq->type = MELTING_OBJ;
	} else {
		sq->type = MELTING;
	}
	sq->data = init_timer(NULL);

	// If breakable, stop flames
	if (type == BREAKABLE){
		return 1;
	}

	// If player, kill
	else if (type == PLAYER) {
		kill_man(sq->data, board);
	}
	return 0;
}

void detonate_bomb(struct Board* board, int r, int c, struct Bomb* bomb) {
	struct Square* sq = get_square(board, r, c);
	sq->display = ' ';
	sq->type = MELTING;
	// Flames going up
	for(int st = 1; st <= bomb->strength && r-st >= 0; st++) {
		if(explode_bomb(get_square(board, r-st, c), board)) {
			break;
		}
	}
	// Flames going down
	for(int st = 1; st <= bomb->strength && r+st < board->height; st++) {
		if(explode_bomb(get_square(board, r+st, c), board)) {
			break;
		}
	}
	// Flames going left
	for(int st = 1; st <= bomb->strength && c-st >= 0; st++) {
		if(explode_bomb(get_square(board, r, c-st), board)) {
			break;
		}
	}
	// Flames going right
	for(int st = 1; st <= bomb->strength && c+st < board->width; st++) {
		if(explode_bomb(get_square(board, r, c+st), board)) {
			break;
		}
	}
	sq->data = init_timer(NULL);
	free_bomb(bomb);
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
				// If square is on fire
				if (sq->type == MELTING || sq->type == MELTING_OBJ) {
					struct Timer* flameTimer = sq->data;
					// Set square to empty
					if ((long) flameTimer->timer >= MELT_TIMER) {
						sq->type = EMPTY;
						sq->display = ' ';
						delete_timer(sq->data);
						sq->data = NULL;
					} else {
						flameTimer->timer++;
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
						detonate_bomb(board, r, c, bomb);
					} else {
						bomb->timer++;
					}
					break;
				case PLAYER:
					;
					struct Man * man = sq->data;

					// validate movement
					if (valid_move(board, man)) {
						if(can_drop_bomb(man)) {
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
						enum SquareType oldType = new_sq->type;
						new_sq->type = PLAYER;
						new_sq->display = man->display;
						new_sq->data = man;

						// Update man's position + movement
						man->r = newr;
						man->c = newc;

						if(oldType == MELTING) {
							kill_man(new_sq->data, board);
							new_sq->data = init_timer(NULL);
						}
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
