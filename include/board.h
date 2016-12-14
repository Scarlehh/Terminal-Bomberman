#ifndef BOARD_H
#define BOARD_H

enum SquareType { BOMB, MELTING, BREAKABLE, BLOCK, PLAYER, EMPTY };

struct Square {
	int r, c;
	char display;
	enum SquareType type;
	void * data;
};

struct Board {
	int width;
	int height;
	struct Square * board;
};

struct Board * new_board(int width, int height);
void clear_board(struct Board * board);
void generate_walls(struct Board* board);
void clear_sides(struct Board* board, int r, int c);

struct Square * get_square(struct Board * board, int row, int col);

#endif
