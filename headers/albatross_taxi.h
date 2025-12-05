#include "bird.h"
#include "consts.h"
#include "utils.h"

typedef struct {
	float y, x, dir_y, dir_x;
	int dest_y, dest_x;
	int speed;
	bool exists, is_bird_inside;
	WIN *parent_window;
} ALBATROSS_TAXI;

ALBATROSS_TAXI *init_albatross_taxi(WIN *parent_window);

void spawn_taxi(ALBATROSS_TAXI *taxi, BIRD *bird);

void move_taxi(ALBATROSS_TAXI *taxi);

void draw_taxi(const ALBATROSS_TAXI taxi);
