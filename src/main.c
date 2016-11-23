#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>

void init();
void end();
WINDOW *create_board(int height, int width, int starty, int startx, bool borders);
void destroy_board(WINDOW *local_win);

int main() {
	init();
	refresh();
	
	WINDOW* board = create_board(50, 50, 0, 0, 1);
	getch();
	destroy_board(board);
	
	endwin();
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

WINDOW *create_board(int height, int width, int starty, int startx, bool borders) {
	WINDOW *local_win;

	local_win = newwin(height, width, starty, startx);
	if(borders) {
		box(local_win, 0, 0);
	}
	wrefresh(local_win);

	return local_win;
}


void destroy_board(WINDOW *local_win) {	
	wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	wrefresh(local_win);
	delwin(local_win);
}
