#include "headers/main.h"

void run_game(void) {
	WINDOW *screen = init_screen();

	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, 0, true, false);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, 0, true, true);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	char key;
	int iteration = 0;

	// TODO: implement stars
	int rnd = get_random(1, game_window->width-2);
	STAR *star = init_star(game_window, rnd);

	while (true) {
		key = (char) wgetch(game_window->window);
		
		if (key == QUIT || get_config()->time_limit == 0) {
			break;
		}

		handle_bird_input(key, bird);

		update_status(status_window);

		// TODO: implement updating whole game window, atm this is here:
		move_bird(bird);
		clear_window(game_window);
		draw_bird(bird);
		draw_star(star);


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
	free(star);
}

// int main(int argc, char *argv[]) {
int main(void) {
	run_game();

	return EXIT_SUCCESS;
}
