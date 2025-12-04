#pragma once

#include "consts.h"
#include "config.h"

typedef struct {
	bool running;
	unsigned int score;
	unsigned int stars_collected;
	unsigned int time_left;
} STATE;

/**
 * **Initializes a new game state object**
 *
 * *Returns*: A pointer to the newly initialized state object
 */
STATE *init_state(void);

/**
 * **Fetches the current game state**
 *
 * *Returns*: A pointer to the current game state
 */
// STATE *get_state(void);
