#include "headers/main.h"

void run_game(void) {
	WINDOW *screen = init_screen();

	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, 0, true, false);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, 0, true, true);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	char key;
	int iteration = 0;

	// TODO: implement stars
	STAR *stars[MAX_STARS];
	int stars_count = 0;

	while (true) {
		key = (char) wgetch(game_window->window);

		if (key == QUIT || get_config()->time_limit == 0) {
			break;
		}

		handle_bird_input(key, bird);

		update_status(status_window);

		// TODO: implement updating whole game window, atm this is here:
		move_bird(bird);

		// TODO: load star spawn rate from config
		// if (iteration % (int) (FRAMES_PER_SECOND/get_config()->star_spawn_rate) == 0) {
		if (iteration % (FRAMES_PER_SECOND/2) == 0) {
			if (stars_count < MAX_STARS) {
				// NOTE: This has to init a star to the first one that does not exist
				// If a star has exists set to false, nullify it and free it, then init
				stars[stars_count] = init_star(game_window, get_random(BORDER_SIZE, game_window->width - BORDER_SIZE - 1)); // TODO: needs to be freed later on
				stars_count++;
			}
		}

		for (int i = 0; i < stars_count; i++) {
			move_star(stars[i]);
		}
		
		clear_window(game_window);
		draw_bird(bird);

		for (int i = 0; i < stars_count; i++) {
			draw_star(*stars[i]);
			// if (!stars[i]->exists) {
			// 	free(stars[i]);
			// 	stars_count--;
			// }
		}

		iteration++;
		// if (iteration % (FRAMES_PER_SECOND) == 0) {
		// 	Time_Limit--;
		// }

		flushinp(); // avoids key press accumulation
		usleep(1000000 / FRAMES_PER_SECOND);
	}

	delwin(game_window->window);
	delwin(status_window->window);
	delwin(screen);

	endwin();

	free(game_window);
	free(status_window);
	free(bird);
	free((void *) get_config());

	for (int i = 0; i < stars_count; i++) {
		free(stars[i]);
	}
}

// int main(int argc, char *argv[]) {
int main(void) {
	run_game();

	return EXIT_SUCCESS;
}
