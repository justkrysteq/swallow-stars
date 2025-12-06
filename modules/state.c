#include "../headers/state.h"

STATE *init_state(void) {
	STATE *state = (STATE *) malloc(sizeof(STATE));

	state->running = true;
	state->in_albatross_taxi = false;
	state->score = 0;
	state->stars_collected = 0;
	state->time_left = get_config()->time_limit;
	state->safe_zone_time_left = 0;
	state->hunter_initial_bounces_escalation = get_config()->hunter_initial_bounces_escalation;
	state->hunter_spawn_rate_escalation = get_config()->hunter_spawn_rate_escalation;

	// state->game_window = game_window;
	// state->status_window = status_window;
	// state->stars = create_star_table(game_window);
	// state->occupancy_map = create_occupancy_map(game_window);

	return state;
}

// STATE *get_state(void) {
// 	static STATE *state = NULL;
// 	
// 	if (state == NULL) {
// 		state = init_state();
// 	}
//
// 	return state;
// }
