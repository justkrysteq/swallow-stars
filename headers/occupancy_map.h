#pragma once

#include "consts.h"
#include "bird.h"
#include "state.h"

typedef struct {
	void *entity;
	char type;
} OCCUPANT;


OCCUPANT **create_occupancy_map(const WIN *parent_window);

void update_occupancy_map(OCCUPANT **occupancy_map, const unsigned int prev_y, const unsigned int prev_x, const unsigned int y, const unsigned int x, char type, void *entity, STATE *game_state);

void free_occupancy_map(OCCUPANT **occupancy_map, WIN *parent_window);

void print_occupancy_map(OCCUPANT **occupancy_map, WIN *parent_window);
