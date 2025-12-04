#include <math.h>
#include "bird.h"
#include "consts.h"

typedef struct {
	float y, x, dir_y, dir_x;
	int dest_y, dest_x;
	unsigned int speed, bounces, damage;
	char shape[8];
	// float spawn_chance;
	bool exists;
	WIN *parent_window;
} HUNTER;

HUNTER init_hunter(WIN *parent_window);

HUNTER *create_hunter_table(WIN *parent_window);

void spawn_hunter(HUNTER *hunters, BIRD *bird);

void draw_hunter(const HUNTER hunter);

void move_hunter(HUNTER *hunter);
