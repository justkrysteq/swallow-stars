#include "albatross_taxi.h"

ALBATROSS_TAXI *init_albatross_taxi(WIN *parent_window) {
	ALBATROSS_TAXI *taxi = (ALBATROSS_TAXI *) malloc(sizeof(ALBATROSS_TAXI));

	taxi->parent_window = parent_window;

	return taxi;
}

void spawn_taxi(ALBATROSS_TAXI *taxi, BIRD *bird) {
	taxi->y = taxi->parent_window->height/2 + 1;
	taxi->x = BORDER_SIZE + 3;
	taxi->exists = true;

	taxi->dest_y = bird->y;
	taxi->dest_x = bird->x + 1;
	taxi->speed = TAXI_SPEED;
	taxi->is_bird_inside = false;

	if (taxi->y < taxi->dest_y) {
		taxi->dest_y += 1;
	}
}

void move_taxi(ALBATROSS_TAXI *taxi) {
	int delta_y = taxi->dest_y - taxi->y;
	int delta_x = taxi->dest_x - taxi->x;

	float distance = calc_distance(delta_y, delta_x);

	if (distance != 0) {
		taxi->dir_y = delta_y / distance;
		taxi->dir_x = delta_x / distance;
	} else {
		taxi->dir_y = 0;
		taxi->dir_x = 0;

		taxi->is_bird_inside = true;

		int mid_y = taxi->parent_window->height/2 + 1;
		int mid_x = taxi->parent_window->width/2;

		if ((int) taxi->y != mid_y || (int) taxi->x != mid_x) {
			taxi->dest_y = mid_y + 1;
			taxi->dest_x = mid_x;
			taxi->speed *= 0.5;

			// Fixes position-related issues from casting floats to ints
			if (taxi->x < taxi->dest_x) {
				taxi->dest_x += 1;
			}
			if (taxi->y > taxi->dest_y) {
				taxi->dest_y -= 1;
			}
		} else {
			taxi->exists = false;
		}
	}

	taxi->y += taxi->dir_y * taxi->speed * SPEED_FACTOR;
	taxi->x += taxi->dir_x * taxi->speed * SPEED_FACTOR;
}

void draw_taxi(ALBATROSS_TAXI taxi) {
	wattron(taxi.parent_window->window, COLOR_PAIR(PAIR_ALBATROSS_TAXI));
	mvwprintw(taxi.parent_window->window, taxi.y, taxi.x-2, "     ");
	wattroff(taxi.parent_window->window, COLOR_PAIR(PAIR_ALBATROSS_TAXI));
	wattron(taxi.parent_window->window, COLOR_PAIR(PAIR_ALBATROSS_TAXI_TOP));
	mvwprintw(taxi.parent_window->window, taxi.y-1, taxi.x-1, "   ");
	wattroff(taxi.parent_window->window, COLOR_PAIR(PAIR_ALBATROSS_TAXI_TOP));
}
