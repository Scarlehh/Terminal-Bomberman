#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "man.h"
#include "physics.h"

const int WIDTH = 21;
const int HEIGHT = 21;
const int DELAY = 100;

void init();
void end();
WINDOW *create_window(int height, int width, int starty, int startx, bool borders);
void destroy_window(WINDOW *local_win);

int main() {
	struct Board* board = new_board(HEIGHT, WIDTH);
	clear_board(board);
	generate_walls(board);
	start_physics(board);

	init();
	refresh();
	WINDOW* window = create_window(HEIGHT+2, WIDTH+2, 0, 0, 1);
	timeout(DELAY);

	struct Man* p1 = new_man(0, WIDTH-1, board);
	struct Man* p2 = new_man(0, 0, board);
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

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
				if(sq->type == MELTING) {
					wattron(window, COLOR_PAIR(1));
				} else if(sq->type == PLAYER) {
					wattron(window, COLOR_PAIR(2));
				}
				// Put into window
				mvwaddch(window, r+1, c+1, display);
				if(sq->type == MELTING) {
					wattroff(window, COLOR_PAIR(1));
				} else if(sq->type == PLAYER) {
					wattroff(window, COLOR_PAIR(2));
				}
			}
		}



		wrefresh(window);
	} while((ch = getch()) != 'q');

	delete_man(p1);
	delete_man(p2);

	destroy_window(window);
	endwin();
	stop_physics();
	clear_board(board);
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
