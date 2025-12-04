#pragma once // TODO: change to include guards

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

// SECTION: CONFIG STRUCTS

typedef struct {
	unsigned int initial_speed, min_speed, max_speed;
	unsigned int life_force;
	char name[25];
} PLAYER_CONFIG;

typedef struct {
	char shape[8];
	float speed, spawn_chance;
	unsigned int damage, initial_bounces;
} HUNTER_CONFIG;

typedef struct {
	unsigned int star_quota;
	unsigned int time_limit;
	float hunter_spawn_rate, star_spawn_rate;
	unsigned int game_height, game_width;
	char level_name[100];
	unsigned int hunter_count;
	PLAYER_CONFIG player[200]; // TODO: change to dynamic allocation
	HUNTER_CONFIG hunters[500]; // TODO: change to dynamic allocation
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
 * - **hunter_count**: *hunter count*
 */
void load_to_config(CONFIG *config, const char *option, const char *value, const bool is_for_player, const bool is_for_hunter, const unsigned int hunter_count);

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
 * - **hunter_count**: *hunter count*
 */
void parse_line(CONFIG *config, char *line, const bool is_for_player, const bool is_for_hunter, const unsigned int hunter_count);

/** **Loads config from file**
 *
 * *Parameters:*
 * - **file**: *file to load config from*
 *
 * *Returns:* config struct
 */
CONFIG *init_config(char *file);

/**
 * **Accesses config struct**
 *
 * *Returns:* config struct
 */
const CONFIG *get_config(void);
