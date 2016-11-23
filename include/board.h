#ifndef BOARD_H
#define BOARD_H

enum SquareType { BOMB, BREAKABLE, BLOCK, PLAYER, EMPTY };

struct Square {
	int x, y;
	char display;
	enum SquareType type;
	void * data;
};

struct Board {
	int width;
	int height;
	struct Square * board;
};

struct * Board new_board(int width, int height);

#endif
