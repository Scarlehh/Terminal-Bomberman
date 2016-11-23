#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "board.h"
#include "man.h"

const int WIDTH = 50;
const int HEIGHT = 50;
const int DELAY = 100;

void init();
void end();
WINDOW *create_window(int height, int width, int starty, int startx, bool borders);
void destroy_window(WINDOW *local_win);

int main() {
	struct Board* board = new_board(HEIGHT, WIDTH);
	clear_board(board);
	
	init();
	refresh();
	WINDOW* window = create_window(HEIGHT+2, WIDTH+2, 0, 0, 1);
	timeout(DELAY);

	struct Man* p1 = new_man(1, 1, board);
	
	int ch = '\0';
	struct Square* sq = NULL;
	do {
		switch(ch) {
		case KEY_DOWN:
			man_down(p1, board);
			break;
		case KEY_UP:
			man_up(p1, board);
			break;
		case KEY_RIGHT:
			man_right(p1, board);
			break;
		case KEY_LEFT:
			man_left(p1, board);
			break;
		}
		
		for(int r = 0; r < HEIGHT; r++) {
			for(int c = 0; c < WIDTH; c++) {
				// Get board squarw
				sq = get_square(board, r, c);
				char display = sq->display;
				// Put into window
				mvwaddch(window, r+1, c+1, display);
			}
		}

		
		
		wrefresh(window);
	} while((ch = getch()) != 'q');

	delete_man(p1);
	
	destroy_window(window);
	endwin();
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
