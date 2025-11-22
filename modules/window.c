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

	if (has_border) {
		box(win->window, 0, 0);
	}

	if (!wait_for_input) {
		nodelay(win->window, true);
	}

	// wrefresh(win->window);

	return win;
}
