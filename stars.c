#include "stars.h"

void draw_star(STAR *star, const bool change_sprite) {
	if (star->exists) {
		bool blinks = star->y > star->parent_window->height*3/4;

		if (blinks) {
			if (star->sprite == '+') {
				wattron(star->parent_window->window, COLOR_PAIR(PAIR_STAR_BLINK));
			} else {
				wattron(star->parent_window->window, COLOR_PAIR(PAIR_STAR));
			}
		} else {
			wattron(star->parent_window->window, COLOR_PAIR(PAIR_STAR));
		}

		if (change_sprite) {
			if (star->sprite == STAR_SPRITE) {
				star->sprite = STAR_SPRITE_BLINK;
			} else if (star->sprite == STAR_SPRITE_BLINK) {
				star->sprite = STAR_SPRITE;
			}
		}

		mvwprintw(star->parent_window->window, star->y, star->x, "%c", star->sprite);

		wattroff(star->parent_window->window, COLOR_PAIR(PAIR_STAR));
		wattroff(star->parent_window->window, COLOR_PAIR(PAIR_STAR_BLINK));
	}
}

STAR init_star(WIN *parent_window) {
	STAR star;

	star.parent_window = parent_window;
	star.x = 0;
	star.y = BORDER_SIZE;
	star.speed = get_random(1, 5) * 0.1;
	star.sprite = STAR_SPRITE;
	star.exists = false;

	return star;
}

void move_star(STAR *star) {
	if (star->exists) {
		star->y += DOWN_DIRECTION * star->speed * SPEED_FACTOR;
	}
}

STAR *create_star_table(WIN *parent_window) {
	STAR *stars = (STAR *) malloc(MAX_STARS * sizeof(STAR));

	for (int i = 0; i < MAX_STARS; i++) {
		stars[i] = init_star(parent_window);
	}

	return stars;
}

void spawn_star(STAR *stars) {
	for (int i = 0; i < MAX_STARS; i++) {
		if (!stars[i].exists) {
			stars[i].exists = true;
			stars[i].y = BORDER_SIZE;
			stars[i].x = get_random(BORDER_SIZE, stars[i].parent_window->width - BORDER_SIZE - 1);

			return;
		}
	}
}
