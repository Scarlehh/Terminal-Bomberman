#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "man.h"
#include "physics.h"

#define WIDTH 21
#define HEIGHT 21
#define DELAY 100

enum COLOUR_PAIRS { PLAYER_ONE=1, PLAYER_TWO, FLAMES };

void init();
void end();
WINDOW *create_window(int height, int width, int starty, int startx, bool borders);
void destroy_window(WINDOW *local_win);
void init_colours();

int main() {
	struct Board* board = new_board(HEIGHT, WIDTH);
	clear_board(board);
	generate_walls(board);
	start_physics(board);

	init();
	refresh();
	WINDOW* window = create_window(HEIGHT+2, WIDTH+2, 0, 0, 1);
	timeout(DELAY);

	init_colours();

	struct Man* p1 = new_man(0, WIDTH-1, board, PLAYER_ONE);
	struct Man* p2 = new_man(0, 0, board, PLAYER_TWO);

	int ch = '\0';
	struct Square* sq = NULL;
	do {
		switch(ch) {
		case KEY_DOWN:
			man_down(p1);
			break;
		case KEY_UP:
			man_up(p1);
			break;
		case KEY_RIGHT:
			man_right(p1);
			break;
		case KEY_LEFT:
			man_left(p1);
			break;
		case '\n':
			get_bomb(p1);
			break;

		case 's':
			man_down(p2);
			break;
		case 'w':
			man_up(p2);
			break;
		case 'd':
			man_right(p2);
			break;
		case 'a':
			man_left(p2);
			break;
		case ' ':
			get_bomb(p2);
			break;
		}

		for(int r = 0; r < HEIGHT; r++) {
			for(int c = 0; c < WIDTH; c++) {
				// Get board square
				sq = get_square(board, r, c);
				char display = sq->display;
				if(sq->type == MELTING || sq->type == MELTING_OBJ) {
					wattron(window, COLOR_PAIR(FLAMES));
				} else if(sq->type == PLAYER) {
					struct Man* man = sq->data;
					wattron(window, COLOR_PAIR(man->colour));
				} else if(sq->type == BLOCK) {
					wattron(window, WA_BOLD);
				}
				// Put into window
				mvwaddch(window, r+1, c+1, display);
				if(sq->type == MELTING || sq->type == MELTING_OBJ) {
					wattroff(window, COLOR_PAIR(FLAMES));
				} else if(sq->type == PLAYER) {
					struct Man* man = sq->data;
					wattroff(window, COLOR_PAIR(man->colour));
				} else if(sq->type == BLOCK) {
					wattroff(window, WA_BOLD);
				}
			}
		}

		refresh();
		wrefresh(window);
	} while((ch = getch()) != 'q');

	delete_man(p1, board);
	delete_man(p2, board);

	destroy_window(window);
	endwin();
	stop_physics();
	clear_board(board);
	delete_board(board);
	return 0;
}

void init() {
	initscr();
	cbreak(); // Pass characters with generating signals
	noecho(); // Don't echo characters
	keypad(stdscr, TRUE); // Enable keypad function/arrow keys
	start_color();
}

void end() {
	endwin();
}

WINDOW *create_window(int height, int width, int starty, int startx, bool borders) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	if (borders) {
		box(local_win, 0, 0);
	}
	wrefresh(local_win);

	return local_win;
}

void destroy_window(WINDOW *local_win) {
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}

void init_colours() {
	init_pair(FLAMES, COLOR_YELLOW, COLOR_RED);
	init_pair(PLAYER_ONE, COLOR_GREEN, COLOR_BLACK);
	init_pair(PLAYER_TWO, COLOR_CYAN, COLOR_BLACK);
}
