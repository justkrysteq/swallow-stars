#include "../headers/occupancy_map.h"

OCCUPANT **create_occupancy_map(const WIN *parent_window) {
	OCCUPANT **occupancy_map = malloc(parent_window->height * sizeof(OCCUPANT *));

	for (int i = 0; i < parent_window->height; i++) {
		occupancy_map[i] = malloc(parent_window->width * sizeof(OCCUPANT));
		for (int j = 0; j < parent_window->width; j++) {
			if (i == 0 || i == parent_window->height-1 || j == 0 || j == parent_window->width-1) {
				occupancy_map[i][j].type = WALL_TYPE;
				occupancy_map[i][j].entity = NULL;
			} else {
				occupancy_map[i][j].type = EMPTY_TYPE;
				occupancy_map[i][j].entity = NULL;
			}
		}
	}

	return occupancy_map;
}

// NOTE: I know that type and entity can be accessed via prev_y and prev_x
void update_occupancy_map(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, char type, void *entity, STATE *game_state) {
	if (x != prev_x || y != prev_y) {
		// TODO: resolve collisions here
		if (occupancy_map[y][x].type == EMPTY_TYPE) {
			occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
			occupancy_map[prev_y][prev_x].entity = NULL;

			mvprintw(get_config()->game_height+13, 0, "this is a test");

			occupancy_map[y][x].type = type;
			occupancy_map[y][x].entity = entity;
		} else if (type == BIRD_TYPE) {
			if (occupancy_map[y][x].type == STAR_TYPE) {
				occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
				occupancy_map[prev_y][prev_x].entity = NULL;

				STAR *star = (STAR *) occupancy_map[y][x].entity;
				star->exists = false;

				game_state->stars_collected++;

				// if (game_state->stars_collected == get_config()->star_quota) {
				// 	game_state->running = false;
				// }

				occupancy_map[y][x].type = type;
				occupancy_map[y][x].entity = entity;
			}

		} else if (type == STAR_TYPE) {
			if (occupancy_map[y][x].type == BIRD_TYPE) {
				occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
				occupancy_map[prev_y][prev_x].entity = NULL;

				STAR *star = (STAR *) entity;
				star->exists = false;

				game_state->stars_collected++;

				if (game_state->stars_collected == get_config()->star_quota) {
					game_state->running = false;
				}
			} else if (occupancy_map[y][x].type == STAR_TYPE) {
				occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
				occupancy_map[prev_y][prev_x].entity = NULL;

				STAR *star = (STAR *) entity;
				star->exists = false;

				STAR *star2 = (STAR *) occupancy_map[y][x].entity;
				star2->exists = false;

				occupancy_map[y][x].type = EMPTY_TYPE;
				occupancy_map[y][x].entity = NULL;
			} else if (occupancy_map[y][x].type == WALL_TYPE) {
				occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
				occupancy_map[prev_y][prev_x].entity = NULL;

				STAR *star = (STAR *) entity;
				star->exists = false;
			}
		}
	}
}

void free_occupancy_map(OCCUPANT **occupancy_map, WIN *parent_window) {
	for (int i = 0; i < parent_window->height; i++) {
		free(occupancy_map[i]);
	}

	free(occupancy_map);
}

void print_occupancy_map(OCCUPANT **occupancy_map, WIN *parent_window) {
	for (int i = 0; i < parent_window->height; i++) {
		for (int j = 0; j < parent_window->width; j++) {
			if (occupancy_map[i][j].type == EMPTY_TYPE) {
				mvwprintw(parent_window->window, i, j, " ");
				wrefresh(parent_window->window);
			} else {
				mvwprintw(parent_window->window, i, j, "%c", occupancy_map[i][j].type);
				wrefresh(parent_window->window);
			}
		}
	}
}
