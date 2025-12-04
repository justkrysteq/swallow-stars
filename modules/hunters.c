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

void spawn_hunter(HUNTER *hunters, BIRD *bird) {
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
				// hunters[i].spawn_chance = get_config()->hunters[hunter_template_id].spawn_chance;
				strcpy(hunters[i].shape, get_config()->hunters[hunter_template_id].shape);
				hunters[i].dest_y = bird->y;
				hunters[i].dest_x = bird->x;

				// TODO: handle directions and speeds and spawn chance
			
				return;
			}
		}
	}
}

void draw_hunter(const HUNTER hunter) { // TODO: implement drawing based on shape
	if (hunter.exists) {
		wattron(hunter.parent_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_LAST));
		mvwprintw(hunter.parent_window->window, hunter.y, hunter.x, "H");
		wattroff(hunter.parent_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_LAST));
	}
}

// TODO: add move hunter

void move_hunter(HUNTER *hunter) {
	if (hunter->exists) {
		int delta_y = hunter->dest_y - hunter->y;
		int delta_x = hunter->dest_x - hunter->x;

		float distance = sqrt(pow(delta_y, 2) + pow(delta_x, 2));

		if (distance != 0) {
			hunter->dir_y = delta_y / distance;
			hunter->dir_x = delta_x / distance;
		} else {
			hunter->dir_y = 0;
			hunter->dir_x = 0;
		}

		hunter->y += hunter->dir_y * hunter->speed * SPEED_FACTOR;
		hunter->x += hunter->dir_x * hunter->speed * SPEED_FACTOR;

		if ((int) hunter->y == hunter->dest_y) {
			hunter->y = hunter->dest_y;
		}

		if ((int) hunter->x == hunter->dest_x) {
			hunter->x = hunter->dest_x;
		}

		hunter->y += hunter->dir_y * hunter->speed * SPEED_FACTOR;
		hunter->x += hunter->dir_x * hunter->speed * SPEED_FACTOR;
	}
}
