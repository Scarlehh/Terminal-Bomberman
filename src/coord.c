#include "coord.h"
#include <stdlib.h>

// Coord
struct Coord* new_coord(int r, int c) {
	struct Coord* coord = malloc(sizeof(struct Coord));
	coord->r = r;
	coord->c = c;
	return coord;
}

void delete_coord(struct Coord* coord) {
	free(coord);
}

void set_coord(struct Coord* coord, int r, int c) {
	coord->r = r;
	coord->c = c;
}

int get_r(struct Coord* coord) {
	return coord->r;
}

int get_c(struct Coord* coord) {
	return coord->c;
}
