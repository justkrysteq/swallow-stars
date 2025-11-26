#include "headers/main.h"

// TODO: Move to utils.c
/**
 * **Generates a random number between min and max**
 *
 * Uses /dev/urandom to generate a random number between min and max (inclusive)
 *
 * *Parameters:*
 * - **min**: *minimum value that the random number can be*
 * - **max**: *maximum value that the random number can be*
 *
 * *Returns:* random number
 */
int get_random(int min, int max) {
	int random_value;

	FILE *dev_urandom = fopen("/dev/urandom", "rb");

	// NOTE: if dev_urandom is not available using srand(time(NULL)) might be neccessary
	if (dev_urandom == NULL) {
		printf("Error opening /dev/urandom\n");
		return -1;
	}

	if (fread(&random_value, sizeof(char), 1, dev_urandom) != 1) {
		printf("Error reading from /dev/urandom\n");
		return -1;
	}
		
	fclose(dev_urandom);

	return min + random_value % (max+1 - min);
}

// TODO: Move to utils.c
bool contains(char array[], int array_size, char element) {
	for (int i = 0; i < array_size; i++) {
		if (array[i] == element) {
			return true;
		}
	}

	return false;
}

// TODO: Move to stars.c with whole logic and struct
void draw_star(WIN *parent_window, int x) {
	mvwprintw(parent_window->window, 1, x, "%c", '*');
}

void run_game(void) {
	WINDOW *screen = start_game();

	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, 0, true, false);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, 0, true, true);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	char key;
	// char *keys_pressed[KEY_PRESS_LIMIT]; // TODO: IMPLEMENT IN LOOP
	int iteration = 0;

	while (true) {
		key = wgetch(game_window->window);
		
		if (key == QUIT || get_config()->time_limit == 0) {
			break;
		}

		handle_bird_input(key, bird);

		update_status(status_window);

		// TODO: implement updating whole game window, atm this is here:
		move_bird(bird);
		clear_window(game_window);
		draw_bird(bird);



		// TODO: implement stars
		int rnd = get_random(1, get_config()->game_width-1);
		draw_star(game_window, rnd);


		iteration++;
		// if (iteration % (FRAMES_PER_SECOND) == 0) {
		// 	Time_Limit--;
		// }

		flushinp(); // avoids key press accumulation
    	// usleep(FRAME_TIME * 1000); // receives value in microseconds
		usleep(1000 / FRAMES_PER_SECOND * 1000); // NOTE: To to samo co 1 / FRAMES_PER_SECOND xD
	}

	delwin(game_window->window);
	delwin(status_window->window);
	delwin(screen);

	endwin();

	free(game_window);
	free(status_window);
	free(bird);
	free(get_config());
}

// int main(int argc, char *argv[]) {
int main(void) {
	run_game();

	return EXIT_SUCCESS;
}
