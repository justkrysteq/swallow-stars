#include "hunters.h"

HUNTER init_hunter(WIN *parent_window) {
	HUNTER hunter;

	hunter.parent_window = parent_window;
	hunter.exists = false;

	return hunter;
}

HUNTER *create_hunter_table(WIN *parent_window) {
	HUNTER *hunters = (HUNTER *) malloc(MAX_HUNTERS * sizeof(HUNTER));

	for (int i = 0; i < MAX_HUNTERS; i++) {
		hunters[i] = init_hunter(parent_window);
	}

	return hunters;
}

void spawn_hunter(HUNTER *hunters, const BIRD *bird, const float initial_bounces_escalation) {
	for (int i = 0; i < MAX_HUNTERS; i++) {
		if (!hunters[i].exists) {
			int hunter_template_id = get_random(0, get_config()->hunter_count - 1);
			bool will_spawn = (bool) ((int) get_random(1, 100)) <= (get_config()->hunters[hunter_template_id].spawn_chance * 100);

			if (will_spawn) {
				handle_hunter_spawn(&hunters[i], bird, initial_bounces_escalation, hunter_template_id);

				// Fixes position-related issues from casting floats to ints
				if (hunters[i].x < bird->x) {
					hunters[i].dest_x += 1;
				} else {
					hunters[i].x -= hunters[i].width + 1;
				}

				if (hunters[i].y < bird->y) {
					hunters[i].dest_y += 1;
				}
			
				return;
			}
		}
	}
}

void handle_hunter_spawn(HUNTER *hunter, const BIRD *bird, const float initial_bounces_escalation, const int hunter_template_id) {
	bool spawns_on_left = (bool) get_random(0, 1);

	hunter->exists = true;
	hunter->y = get_random(BORDER_SIZE, hunter->parent_window->height - BORDER_SIZE - hunter->height);
	hunter->x = spawns_on_left ? BORDER_SIZE : hunter->parent_window->width - BORDER_SIZE - hunter->width;


	hunter->bounces = get_config()->hunters[hunter_template_id].initial_bounces + ((int) (1 * initial_bounces_escalation));
	hunter->damage = get_config()->hunters[hunter_template_id].damage;
	hunter->speed = get_config()->hunters[hunter_template_id].speed;
	hunter->is_dashing = false;
	hunter->is_waiting = false;
	hunter->in_bounce_state = false;

	hunter->height = get_config()->hunters[hunter_template_id].shape[0] - '0';
	hunter->width = get_config()->hunters[hunter_template_id].shape[2] - '0';

	hunter->dest_y = bird->y;
	hunter->dest_x = bird->x;
}

void draw_hunter_sprite(const HUNTER hunter) {
	if (hunter.height == 2 && hunter.width == 2) {
		mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "\\/");
		mvwprintw(hunter.parent_window->window, hunter.y+1, hunter.x, "/\\");
	} else if (hunter.height == 1 && hunter.width == 2) {
		mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "[]");
	} else if (hunter.height == 2 && hunter.width == 1) {
		mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "#");
		mvwprintw(hunter.parent_window->window, hunter.y+1, hunter.x, "#");
	} else if (hunter.height == 1 && hunter.width == 3) {
		mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "<=>");
	} else {
		for (unsigned int i = 0; i < hunter.height; i++) {
			for (unsigned int j = 0; j < hunter.width; j++) {
				mvwprintw(hunter.parent_window->window, hunter.y+i, hunter.x+j, "H");
			}
		}
	}
}

void draw_hunter(const HUNTER hunter) {
	if (hunter.exists) {
		if (hunter.damage >= HUNTER_DAMAGE_HIGH) {
			wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_HIGH));
		} else if (hunter.damage >= HUNTER_DAMAGE_MEDIUM) {
			wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_MEDIUM));
		} else {
			wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
		}

		draw_hunter_sprite(hunter);

		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_MEDIUM));
		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_HIGH));

		wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_LABEL));
		mvwprintw(hunter.parent_window->window, hunter.y, hunter.x+hunter.width, "%d", hunter.bounces);
		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_HUNTER_LABEL));
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

			if (hunter->is_dashing && function_calls > HUNTER_DASH_TIME) {
				hunter->is_dashing = false;
				function_calls = 0;
			}

			if (!hunter->is_waiting) {
				handle_hunter_movement(hunter, bird, &function_calls);
			}

			function_calls++;
		} else {
			hunter->y += hunter->dir_y * hunter->speed * SPEED_FACTOR;
			hunter->x += hunter->dir_x * hunter->speed * SPEED_FACTOR;
		}

		if (hunter->height == 3) {
			hunter->y += UP_DIRECTION * hunter->speed * SPEED_FACTOR;
		}

		handle_hunter_bounce(hunter);
	}
}

void handle_hunter_movement(HUNTER *hunter, const BIRD *bird, int *function_calls) {
	int dash_speed_multiplier = hunter->is_dashing ? DASH_SPEED_MULTIPLIER : 1;

	int delta_y = hunter->dest_y - hunter->y;
	int delta_x = hunter->dest_x - hunter->x;

	float distance = calc_distance(delta_y, delta_x);

	if (distance != 0) {
		hunter->dir_y = delta_y / distance;
		hunter->dir_x = delta_x / distance;
	} else {
		hunter->dir_y = 0;
		hunter->dir_x = 0;

		hunter->dest_y = bird->y;
		hunter->dest_x = bird->x;

		hunter->is_waiting = true;

		*function_calls = 0;

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

void handle_hunter_bounce(HUNTER *hunter) {
	bool bounce_back = false;

	if (hunter->y < BORDER_SIZE) {
		hunter->y = BORDER_SIZE;
		bounce_back = true;
	} else if (hunter->y > hunter->parent_window->height - BORDER_SIZE - 1) {
		hunter->y = hunter->parent_window->height - BORDER_SIZE - hunter->height;
		bounce_back = true;
	}

	if (hunter->x < BORDER_SIZE) {
		hunter->x = BORDER_SIZE;
		bounce_back = true;
	} else if (hunter->x > hunter->parent_window->width - BORDER_SIZE - 1) {
		hunter->x = hunter->parent_window->width - BORDER_SIZE - hunter->width;
		bounce_back = true;
	}

	if (bounce_back) {
		hunter_bounce_back(hunter);
		bounce_back = false;
	}
}

void hunter_bounce_back(HUNTER *hunter) {
	if (hunter->exists) {
		hunter->dir_y *= -1;
		hunter->dir_x *= -1;
		hunter->in_bounce_state = true;
		hunter->bounces--;

		if (hunter->dir_x == 0 && hunter->dir_y == 0) {
			hunter->dir_y = DOWN_DIRECTION;
			hunter->dir_x = RIGHT_DIRECTION;
		}

		if (hunter->bounces <= 0) {
			hunter->exists = false;
			hunter->y = 0;
			hunter->x = 0;
			hunter->dir_y = 0;
			hunter->dir_x = 0;
		}
	}
}
