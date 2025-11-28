#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

#pragma once // TODO: change to include guards

// SECTION: CONFIG STRUCTS

typedef struct {
	unsigned int initial_speed;
	unsigned int min_speed;
	unsigned int max_speed;
	unsigned int life_force;
	char name[25];
} PLAYER_CONFIG;

typedef struct {
	unsigned int star_quota;
	unsigned int time_limit;
	float spawn_rate;
	unsigned int game_height;
	unsigned int game_width;
	char level_name[100];
	PLAYER_CONFIG player[200]; // TODO: change to dynamic allocation
} CONFIG;


// SECTION: CONFIG FILE PARSING

/**
 * **Updates config value with the provided value**
 *
 * *Parameters:*
 * - **option**: *name of the config option*
 * - **value**: *new value*
 * - **is_for_player**: *whether or not this is a player option*
 * - **is_for_hunter**: *whether or not this is a hunter option*
 */
void load_to_config(CONFIG *config, const char *option, const char *value, const bool is_for_player, const bool is_for_hunter);

/**
 * **Splits a line into option and value and loads it into config**
 *
 * If the line contains '=' character, the line will be split into option and value
 * If the line does not contain '=' character, the line will be ignored
 *
 * *Parameters:*
 * - **line**: *line to be parsed*
 * - **is_for_player**: *whether or not this line is for player config*
 * - **is_for_hunter**: *whether or not this line is for hunter config*
 */
void parse_line(CONFIG *config, char *line, const bool is_for_player, const bool is_for_hunter);

/**
 * **Accesses config struct**
 *
 * *Returns:* config struct
 */
const CONFIG *get_config(void);
