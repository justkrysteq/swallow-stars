#include "stars.h"

typedef struct {
	bool running;
	int score;
	int stars_collected;
	int time_left;
	// TODO: occupancy map
	STAR *stars;
} STATE;
