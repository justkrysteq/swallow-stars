#include <stdlib.h>
#include "../headers/bird.h"

BIRD *init_bird(WIN *parent_window, int y, int x) {
	BIRD *bird = (BIRD *) malloc(sizeof(BIRD));

	bird->parent_window = parent_window;
	bird->y = y;
	bird->x = x;
	bird->speed = BIRD_INITIAL_SPEED;
	bird->sprite = BIRD_SPRITE;
	bird->life_force = BIRD_INITIAL_LIFE_FORCE;

	return bird;
}

void draw_bird(BIRD *bird) {
	mvwprintw(bird->parent_window->window, bird->y, bird->x, "%c", bird->sprite);
}
