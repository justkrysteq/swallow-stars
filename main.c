#include "headers/main.h"

void run_game(void) {
	WINDOW *screen = init_screen();

	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, 0, true, false);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, 0, true, true);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	// NOTE: TEMP
	WIN *occupancy_window = init_window(screen, get_config()->game_height, get_config()->game_width, game_window->height+15, 0, false, false);

	char key;
	int iteration = 0;

	// get_state()->stars = create_star_table(game_window);
	STATE *game_state = init_state();
	STAR *stars = create_star_table(game_window); // TODO: move to init_state
	OCCUPANT **occupancy_map = create_occupancy_map(game_window);

	while (game_state->running) {
		key = (char) wgetch(game_window->window);

		if (key == QUIT || game_state->time_left == 0) {
			game_state->running = false;
		}

		handle_bird_input(key, bird);

		update_status(status_window, game_state->time_left, game_state->stars_collected, bird->life_force);

		// TODO: implement updating whole game window, atm this is here:
		int bird_y = bird->y;
		int bird_x = bird->x;
		move_bird(bird);
		update_occupancy_map(occupancy_map, bird_y, bird_x, bird->y, bird->x, BIRD_TYPE, bird, game_state);

		if (iteration % (int) (FRAMES_PER_SECOND/get_config()->star_spawn_rate) == 0) {
			spawn_star(stars);
		}

		for (int i = 0; i < MAX_STARS; i++) {
			int star_y = stars[i].y;
			int star_x = stars[i].x;
			move_star(&stars[i], (iteration % (int) ((FRAMES_PER_SECOND/get_config()->star_spawn_rate)/2) == 0));
			update_occupancy_map(occupancy_map, star_y, star_x, stars[i].y, stars[i].x, STAR_TYPE, &stars[i], game_state);
		}
		
		clear_window(game_window);
		draw_bird(bird);

		for (int i = 0; i < MAX_STARS; i++) {
			draw_star(stars[i]);
		}

		if (key == 'm' || key == 'b') {
			print_occupancy_map(occupancy_map, occupancy_window);
		}

		iteration++;
		if (iteration % (FRAMES_PER_SECOND) == 0) {
			game_state->time_left--;
		}

		flushinp(); // avoids key press accumulation
		usleep(1000000 / FRAMES_PER_SECOND);
	}

	delwin(game_window->window);
	delwin(status_window->window);
	delwin(screen);

	endwin();

	free_occupancy_map(occupancy_map, game_window);
	free(game_window);
	free(status_window);
	free(occupancy_window);
	free(bird);
	free((void *) get_config());
	free(stars);
	free(game_state);
}

// int main(int argc, char *argv[]) {
int main(void) {
	run_game();

	return EXIT_SUCCESS;
}
