#include "../headers/stars.h"

void draw_star(const STAR star) {
	if (star.exists) {
		mvwprintw(star.parent_window->window, star.y, star.x, "%c", star.sprite);
	// } else {
	// 	free(star);
	}
}

STAR *init_star(WIN *parent_window, int x) {
	STAR *star = (STAR *) malloc(sizeof(STAR));

	star->parent_window = parent_window;
	star->x = x;
	star->y = BORDER_SIZE;
	star->speed = get_config()->player->initial_speed;
	star->sprite = '*';
	star->exists = true;

	return star;
}

void move_star(STAR *star) {
	star->y += DOWN_DIRECTION * star->speed * SPEED_FACTOR;
	if (star->y > star->parent_window->height - BORDER_SIZE) {
		star->exists = false;
	}
}
