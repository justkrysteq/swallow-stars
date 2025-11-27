#include "../headers/window.h"

WINDOW *init_screen(void) {
	WINDOW *win = initscr();

	curs_set(0); // makes cursor invisible
	noecho();

	cbreak();
	nonl();

	return win;
}

WIN *init_window(WINDOW *parent_window, int height, int width, int start_y, int start_x, bool has_border, bool wait_for_input) {
	WIN *win = (WIN *) malloc(sizeof(WIN));

	win->window = subwin(parent_window, height, width, start_y, start_x);
	win->start_y = start_y;
	win->start_x = start_x;
	win->height = height;
	win->width = width;
	win->has_border = has_border;

	if (has_border) {
		box(win->window, 0, 0);
	}

	if (!wait_for_input) {
		nodelay(win->window, true);
	}

	return win;
}

void clear_window(WIN *window) {
	werase(window->window);
	if (window->has_border) {
		box(window->window, 0, 0);
	}
}

void update_status(WIN *status_window) {
	clear_window(status_window);

	mvwprintw(status_window->window, 0, 1, "Status");
	mvwprintw(status_window->window, 1, 1, "Player: %s", "krysteq");
	mvwprintw(status_window->window, 2, 1, "Level: %s", get_config()->level_name);
	mvwprintw(status_window->window, 3, 1, "Time left: %ds", get_config()->time_limit);
	mvwprintw(status_window->window, 4, 1, "Stars left to collect: %d", get_config()->star_quota);
	mvwprintw(status_window->window, 5, 1, "Life force: %d", get_config()->player->life_force);

	wrefresh(status_window->window);
}
