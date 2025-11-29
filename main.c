#include "headers/main.h"

void run_game(void) {
	WINDOW *screen = init_screen();

	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, 0, true, false);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, 0, true, true);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	char key;
	int iteration = 0;

	get_state()->stars = create_star_table(game_window); // TODO: move to init_state

	while (get_state()->running) {
		key = (char) wgetch(game_window->window);

		if (key == QUIT) {
			get_state()->running = false;
		}

		handle_bird_input(key, bird);

		update_status(status_window);

		// TODO: implement updating whole game window, atm this is here:
		move_bird(bird);

		if (iteration % (int) (FRAMES_PER_SECOND/get_config()->star_spawn_rate) == 0) {
			spawn_star(get_state()->stars);
		}

		for (int i = 0; i < MAX_STARS; i++) {
			move_star(&get_state()->stars[i]);
		}
		
		clear_window(game_window);
		draw_bird(bird);

		for (int i = 0; i < MAX_STARS; i++) {
			draw_star(get_state()->stars[i]);
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
	free(get_state()->stars);
	free((void *) get_state());
}

// int main(int argc, char *argv[]) {
int main(void) {
	run_game();

	return EXIT_SUCCESS;
}
