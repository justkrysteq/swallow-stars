#include "headers/main.h"

int main(int argc, char *argv[]) {
	WINDOW *screen = start_game();

	// TODO: Tu jest potrzebne wczytanie z plików height i width
	WIN *game_window = init_window(screen, 10, 40, 0, 0, true, false);
	WIN *status_window = init_window(screen, 3, 40, game_window->height, 0, true, true);
	BIRD *bird = init_bird(game_window, 5, 5);
	draw_bird(bird);

	char key;

	while (true) {
		key = getch(); // don't know if it freezes the game atm

		if (key == QUIT) {
			break;
		}


	}

	delwin(game_window->window);
	delwin(status_window->window);
	delwin(screen);

	endwin();

	free(game_window);
	free(status_window);
	free(bird);

	return EXIT_SUCCESS;
}
