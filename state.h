#pragma once

#include "consts.h"
#include "config.h"

typedef struct {
	bool running, in_albatross_taxi, in_menu;
	unsigned int score;
	unsigned int stars_collected;
	unsigned int time_left;
	float hunter_initial_bounces_escalation;
	float hunter_spawn_rate_escalation;
	int safe_zone_time_left;
	char player_name[MAX_PLAYER_NAME_LENGTH];
} STATE;

/**
 * **Initializes a new game state object**
 *
 * *Returns*: A pointer to the newly initialized state object
 */
STATE *init_state(void);
