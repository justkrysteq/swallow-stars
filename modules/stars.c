#include "../headers/stars.h"

void draw_star(STAR *star) {
	mvwprintw(star->parent_window->window, 1, star->x, "%c", star->sprite);
}

STAR *init_star(WIN *parent_window, int x) {
	STAR *star = (STAR *) malloc(sizeof(STAR));

	star->parent_window = parent_window;
	star->x = x;
	star->y = 0;
	star->speed = get_config()->player->initial_speed;
	star->sprite = '*';

	return star;
}
