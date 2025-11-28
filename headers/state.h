#include "stars.h"

typedef struct {
	bool running;
	int score;
	int stars_collected;
	int time_left;
	// TODO: occupancy map
	STAR *stars;
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
STATE *get_state(void);
