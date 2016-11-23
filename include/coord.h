#ifndef COORD_H
#define COORD_H

struct Coord {
	int r, c;
};

// Coord
struct Coord* new_coord();
void delete_coord(struct Coord* coord);
void set_coord(struct Coord* coord, int r, int c);
int get_r(struct Coord* coord);
int get_c(struct Coord* coord);

#endif
