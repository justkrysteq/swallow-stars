#include "../headers/window.h"

WINDOW *init_screen(void) {
	WINDOW *win = initscr();

	curs_set(0); // makes cursor invisible
	noecho();

	cbreak();
	// nonl();

	return win;
}

WIN *init_window(WINDOW *parent_window, int height, int width, int start_y, int start_x, bool has_border, bool wait_for_input, int color_pair) {
	WIN *win = (WIN *) malloc(sizeof(WIN));

	win->window = subwin(parent_window, height, width, start_y, start_x);
	win->start_y = start_y;
	win->start_x = start_x;
	win->height = height;
	win->width = width;
	win->has_border = has_border;
	win->color_pair = color_pair;

	if (has_border) {
		box(win->window, 0, 0);
	}

	if (!wait_for_input) {
		nodelay(win->window, true);
	}

	return win;
}

void clear_window(WIN *window) {
	wattron(window->window, COLOR_PAIR(window->color_pair));
	// werase(window->window);
	if (window->has_border) {
		box(window->window, 0, 0);
	}
	for (int i = 1; i < window->height-1; i++) {
		for (int j = 1; j < window->width-1; j++) {
			mvwaddch(window->window, i, j, ' ');
		}
	}
	wattroff(window->window, COLOR_PAIR(window->color_pair));
}

void update_status(WIN *status_window, const unsigned int time_left, const unsigned int stars_collected, const unsigned int bird_life_force, const char *player_name) {
	clear_window(status_window);

	wattron(status_window->window, COLOR_PAIR(status_window->color_pair));

	mvwprintw(status_window->window, 0, 1, "Status");
	mvwprintw(status_window->window, 1, 1, "Player: %s", player_name);
	mvwprintw(status_window->window, 2, 1, "Level: %s", get_config()->level_name);
	mvwprintw(status_window->window, 3, 1, "Time left: %ds", time_left);
	mvwprintw(status_window->window, 4, 1, "Stars left to collect: %d", get_config()->star_quota - stars_collected);
	mvwprintw(status_window->window, 5, 1, "Life force: %d", bird_life_force);

	wattroff(status_window->window, COLOR_PAIR(status_window->color_pair));

	wrefresh(status_window->window);
}
