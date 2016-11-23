#include <pthread.h>

#include "physics.h"
#include "bomb.h"
#include "man.h"
#include "board.h"

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
		// run through and update MELTING
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				sq = get_square(board, r, c);
				switch (sq->type) {
					case BOMB:
						; // for fuck's sake C
						struct Bomb * bomb = sq->data;
						if (bomb->timer >= BOMB_TIMER_END) {
							// set blocks around to MELTING, clear one BREAKABLE
							// if PLAYER set to MELTING, send kill signal
						} else {
							bomb->timer++;
						}
						break;
					case PLAYER:
						;
						struct Man * man = sq->data;

						// validate movement
						if (valid_move(board, man)) {
							if (man->hasBomb && (man->dC != 0 || man->dR != 0)) {
								// place bomb
							}

							// perform move
						}
						break;
					default:
						break;
				}
			}
		}
	}
}