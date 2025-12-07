#include "occupancy_map.h"

OCCUPANT **create_occupancy_map(const WIN *parent_window) {
	OCCUPANT **occupancy_map = (OCCUPANT **) malloc(parent_window->height * sizeof(OCCUPANT *));

	for (int i = 0; i < parent_window->height; i++) {
		occupancy_map[i] = (OCCUPANT *) malloc(parent_window->width * sizeof(OCCUPANT));
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

void handle_bird_collision(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, char type, void *entity, STATE *game_state) {
	if (occupancy_map[y][x].type == STAR_TYPE) {
		occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
		occupancy_map[prev_y][prev_x].entity = NULL;

		STAR *star = (STAR *) occupancy_map[y][x].entity;
		star->exists = false;

		game_state->stars_collected++;

		if (game_state->stars_collected == get_config()->star_quota) {
			game_state->running = false;
		}

		occupancy_map[y][x].type = type;
		occupancy_map[y][x].entity = entity;
	} else if (occupancy_map[y][x].type == HUNTER_TYPE) {
		occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
		occupancy_map[prev_y][prev_x].entity = NULL;

		BIRD *bird = (BIRD *) entity;
		HUNTER *hunter = (HUNTER *) occupancy_map[y][x].entity;

		bird->life_force -= hunter->damage;
		bird->dir_y *= -1;
		bird->dir_x *= -1;

		if (bird->life_force <= 0) {
			game_state->running = false;
		}

		hunter_bounce_back(hunter);

		occupancy_map[y][x].type = type;
		occupancy_map[y][x].entity = entity;
	}
}

void handle_star_collision(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, void *entity, STATE *game_state) {
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
	} else if (occupancy_map[y][x].type == WALL_TYPE || occupancy_map[y][x].type == HUNTER_TYPE) {
		occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
		occupancy_map[prev_y][prev_x].entity = NULL;

		STAR *star = (STAR *) entity;
		star->exists = false;
	}
}

void handle_hunter_collision_with_bird(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, void *entity, STATE *game_state) {
	occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
	occupancy_map[prev_y][prev_x].entity = NULL;

	HUNTER *hunter = (HUNTER *) entity;
	BIRD *bird = (BIRD *) occupancy_map[y][x].entity;

	bird->life_force -= hunter->damage;
	bird->dir_y *= -1;
	bird->dir_x *= -1;

	if (bird->life_force <= 0) {
		game_state->running = false;
	}

	hunter_bounce_back(hunter);
}

void handle_hunter_collision_with_hunter(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, void *entity) {
	HUNTER *hunter = (HUNTER *) entity;

	if (occupancy_map[y][x].entity != entity) {
		HUNTER *hunter2 = (HUNTER *) occupancy_map[y][x].entity;

		occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
		occupancy_map[prev_y][prev_x].entity = NULL;

		occupancy_map[y][x].type = EMPTY_TYPE;
		occupancy_map[y][x].entity = NULL;

		hunter_bounce_back(hunter);
		hunter_bounce_back(hunter2);
	}
}

void handle_hunter_collision(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, void *entity, STATE *game_state) {
	occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
	occupancy_map[prev_y][prev_x].entity = NULL;

	if (occupancy_map[y][x].type == WALL_TYPE) {
		occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
		occupancy_map[prev_y][prev_x].entity = NULL;
		occupancy_map[y][x].type = EMPTY_TYPE;
		occupancy_map[y][x].entity = NULL;

		occupancy_map[0][0].type = WALL_TYPE;
		occupancy_map[0][0].entity = NULL;
	} else if (occupancy_map[y][x].type == BIRD_TYPE) {
		handle_hunter_collision_with_bird(occupancy_map, prev_y, prev_x, y, x, entity, game_state);
	} else if (occupancy_map[y][x].type == HUNTER_TYPE) {
		handle_hunter_collision_with_hunter(occupancy_map, prev_y, prev_x, y, x, entity);
	}
}

void update_occupancy_map(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, char type, void *entity, STATE *game_state) {
	if (x < get_config()->game_width && y < get_config()->game_height) {
		if (x != prev_x || y != prev_y) {
			if (occupancy_map[y][x].type == EMPTY_TYPE) {
				occupancy_map[prev_y][prev_x].type = EMPTY_TYPE;
				occupancy_map[prev_y][prev_x].entity = NULL;
				occupancy_map[y][x].type = type;
				occupancy_map[y][x].entity = entity;
			} else if (type == BIRD_TYPE) {
				handle_bird_collision(occupancy_map, prev_y, prev_x, y, x, type, entity, game_state);
			} else if (type == STAR_TYPE) {
				handle_star_collision(occupancy_map, prev_y, prev_x, y, x, entity, game_state);
			} else if (type == HUNTER_TYPE) {
				handle_hunter_collision(occupancy_map, prev_y, prev_x, y, x, entity, game_state);
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

void print_occupancy_map(OCCUPANT **occupancy_map, const WIN *parent_window) {
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

void clear_occupancy_map(OCCUPANT **occupancy_map, const WIN *parent_window) {
	for (int i = 0; i < parent_window->height; i++) {
		for (int j = 0; j < parent_window->width; j++) {
			if (occupancy_map[i][j].type != WALL_TYPE && occupancy_map[i][j].type != EMPTY_TYPE) {
				occupancy_map[i][j].type = EMPTY_TYPE;
				occupancy_map[i][j].entity = NULL;
			}
		}
	}
}
