#include "../headers/window.h"

WINDOW *start_game() {
	WINDOW *win = initscr();

	curs_set(0); // makes cursor invisible
	noecho();

	return win;
}

WIN *init_window(WINDOW *parent_window, int height, int width, int start_y, int start_x, bool has_border, bool wait_for_input) {
	WIN *win = (WIN *) malloc(sizeof(WIN)); // malloc returns a void pointer, so to access the memory with the -> operator conversion is necessary

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

	// wrefresh(win->window);

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
	mvwprintw(status_window->window, 1, 1, "Player: %s", Player_Name);
	mvwprintw(status_window->window, 2, 1, "Level: %s", Level_Name);
	mvwprintw(status_window->window, 3, 1, "Time: %d", Time_Limit);
	mvwprintw(status_window->window, 4, 1, "Star left to collect: %d", Star_Quota);

	wrefresh(status_window->window);
}
