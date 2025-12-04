#include "../headers/hunters.h"

HUNTER init_hunter(WIN *parent_window) {
	HUNTER hunter;

	hunter.parent_window = parent_window;
	hunter.exists = false;

	return hunter;
}

HUNTER *create_hunter_table(WIN *parent_window) {
	HUNTER *hunters = malloc(MAX_HUNTERS * sizeof(HUNTER));

	for (int i = 0; i < MAX_HUNTERS; i++) {
		hunters[i] = init_hunter(parent_window);
	}

	return hunters;
}

void spawn_hunter(HUNTER *hunters, const BIRD *bird) {
	for (int i = 0; i < MAX_HUNTERS; i++) {
		if (!hunters[i].exists) {
			int hunter_template_id = get_random(0, get_config()->hunter_count - 1);
			bool will_spawn = (bool) ((int) get_random(1, 100)) <= (get_config()->hunters[hunter_template_id].spawn_chance * 100);

			if (will_spawn) {
				bool spawns_on_left = (bool) get_random(0, 1);

				hunters[i].exists = true;
				hunters[i].y = get_random(BORDER_SIZE, hunters[i].parent_window->height - BORDER_SIZE - 1);
				hunters[i].x = spawns_on_left ? BORDER_SIZE : hunters[i].parent_window->width - BORDER_SIZE - 1;


				hunters[i].bounces = get_config()->hunters[hunter_template_id].initial_bounces;
				hunters[i].damage = get_config()->hunters[hunter_template_id].damage;
				hunters[i].speed = get_config()->hunters[hunter_template_id].speed;
				hunters[i].is_dashing = false;
				hunters[i].is_waiting = false;
				hunters[i].in_bounce_state = false;
				// hunters[i].spawn_chance = get_config()->hunters[hunter_template_id].spawn_chance;
				strcpy(hunters[i].shape, get_config()->hunters[hunter_template_id].shape);

				hunters[i].dest_y = bird->y;
				hunters[i].dest_x = bird->x;

				// TODO: move hunter spawn based on shape ??

				// Fixes position-related issues from casting floats to ints
				if (spawns_on_left) {
					hunters[i].dest_x += 1;
				}

				if (hunters[i].y < bird->y) {
					hunters[i].dest_y += 1;
				}
			
				return;
			}
		}
	}
}

void draw_hunter(const HUNTER hunter) { // TODO: implement drawing based on shape
	if (hunter.exists) {
		if (hunter.damage >= HUNTER_DAMAGE_HIGH) {
			wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_HIGH));
		} else if (hunter.damage >= HUNTER_DAMAGE_MEDIUM) {
			wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_MEDIUM));
		} else {
			wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
		}

		// TODO: implement drawing based on shape
		// mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "H");

		if (strcmp(hunter.shape, "2x2") == 0) {
			mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "/\\");
			mvwprintw(hunter.parent_window->window, hunter.y+1, hunter.x, "/\\");
		}

		if (strcmp(hunter.shape, "1x2") == 0) {
			mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "H");
			mvwprintw(hunter.parent_window->window, hunter.y+1, hunter.x, "H");
		}

		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_MEDIUM));
		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_HIGH));
	}
}

void move_hunter(HUNTER *hunter, const BIRD *bird) {
	if (hunter->exists) {
		if (!hunter->in_bounce_state) {
			static int function_calls = 0;

			if (hunter->is_waiting && function_calls > HUNTER_WAIT_TIME) {
				hunter->is_waiting = false;
				hunter->is_dashing = true;
				function_calls = 0;
			}

			if (hunter->is_dashing && function_calls > HUNTER_DASH_TIME) { // TODO: maybe base that on tick rate or tiles or seconds
				hunter->is_dashing = false;
				function_calls = 0;
			}

			if (!hunter->is_waiting) {
				int dash_speed_multiplier = hunter->is_dashing ? DASH_SPEED_MULTIPLIER : 1;

				int delta_y = hunter->dest_y - hunter->y;
				int delta_x = hunter->dest_x - hunter->x;

				float distance = sqrt(pow(delta_y, 2) + pow(delta_x, 2));

				if (distance != 0) {
					hunter->dir_y = delta_y / distance;
					hunter->dir_x = delta_x / distance;
				} else {
					hunter->dir_y = 0;
					hunter->dir_x = 0;

					hunter->dest_y = bird->y;
					hunter->dest_x = bird->x;

					hunter->is_waiting = true;

					function_calls = 0;

					// Fixes position-related issues from casting floats to ints
					if (hunter->x < bird->x) {
						hunter->dest_x += 1;
					}

					if (hunter->y < bird->y) {
						hunter->dest_y += 1;
					}
				}

				hunter->y += hunter->dir_y * hunter->speed * SPEED_FACTOR * dash_speed_multiplier;
				hunter->x += hunter->dir_x * hunter->speed * SPEED_FACTOR * dash_speed_multiplier;
			}

			function_calls++;
		} else {
			hunter->y += hunter->dir_y * hunter->speed * SPEED_FACTOR;
			hunter->x += hunter->dir_x * hunter->speed * SPEED_FACTOR;
		}
	}
}
