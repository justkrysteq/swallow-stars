#include "../headers/stars.h"

void draw_star(const STAR star) {
	if (star.exists) {
		mvwprintw(star.parent_window->window, star.y, star.x, "%c", star.sprite);
	// } else {
	// 	free(star);
	}
}

STAR init_star(WIN *parent_window) {
	STAR star;

	star.parent_window = parent_window;
	star.x = 0;
	star.y = BORDER_SIZE;
	star.speed = get_random(1, 5) * 0.1;
	star.sprite = '*';
	star.exists = false;

	return star;
}

void move_star(STAR *star) {
	if (star->exists) {
		star->y += DOWN_DIRECTION * star->speed * SPEED_FACTOR;
		if (star->y > star->parent_window->height - BORDER_SIZE) {
			star->exists = false;
			star->y = BORDER_SIZE;
		}
	}
}

STAR *create_star_table(WIN *parent_window) {
	STAR *stars = malloc(MAX_STARS * sizeof(STAR));

	for (int i = 0; i < MAX_STARS; i++) {
		stars[i] = init_star(parent_window);
	}

	return stars;
}

void spawn_star(STAR *stars) {
	for (int i = 0; i < MAX_STARS; i++) {
		if (!stars[i].exists) {
			stars[i].exists = true;
			stars[i].x = get_random(BORDER_SIZE, stars[i].parent_window->width - BORDER_SIZE - 1);

			return;
		}
	}
}
