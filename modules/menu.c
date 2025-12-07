#include "../headers/menu.h"

void handle_menu_input(WIN *menu_window, char key, STATE *game_state) {
	key = (char) wgetch(menu_window->window);
	
	if (key == ENTER) {
		game_state->in_menu = false;
	}

	if (key == QUIT) {
		game_state->in_menu = false;
		game_state->running = false;
	}
}

void show_menu_errors(WIN *menu_window) {
	if (!has_colors()) {
		mvwprintw(menu_window->window, menu_window->height-3, 1, "[!] Your terminal does not support colors");
	}

	if (!can_change_color()) {
		mvwprintw(menu_window->window, menu_window->height-2, 1, "[!] Your terminal does not support changing colors");
	}
}

void show_menu_title(WIN *menu_window) {
	wattron(menu_window->window, COLOR_PAIR(PAIR_STAR));

	mvwprintw(menu_window->window, 2, (menu_window->width-64)/2, MENU_TITLE_LINE_1);
	mvwprintw(menu_window->window, 3, (menu_window->width-64)/2, MENU_TITLE_LINE_2);
	mvwprintw(menu_window->window, 4, (menu_window->width-64)/2, MENU_TITLE_LINE_3);
	mvwprintw(menu_window->window, 5, (menu_window->width-64)/2, MENU_TITLE_LINE_4);
	mvwprintw(menu_window->window, 6, (menu_window->width-64)/2, MENU_TITLE_LINE_5);

	wattroff(menu_window->window, COLOR_PAIR(PAIR_STAR));
}

void display_menu_button(WIN *menu_window, int iteration, bool *is_menu_button_selected) {
	if (*is_menu_button_selected) {
		wattron(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON_SELECTED));
	} else {
		wattron(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON));
	}

	mvwprintw(menu_window->window, 10, (menu_window->width-12)/2, "    Play    ");

	wattroff(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON_SELECTED));
	wattroff(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON));

	if (iteration % (FRAMES_PER_SECOND) == 0) {
		if (*is_menu_button_selected) {
			*is_menu_button_selected = false;
		} else {
			*is_menu_button_selected = true;
		}
	}
}

void open_menu(WINDOW *screen, STATE *game_state, int screen_center_x) {
	WIN *menu_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, false, PAIR_GAME_DEFAULT);

	int iteration = 0;
	char key = 0;

	bool is_menu_button_selected = false;

	clear_window(menu_window);

	while (game_state->in_menu) {
		handle_menu_input(menu_window, key, game_state);

		show_menu_errors(menu_window);
		show_menu_title(menu_window);
		display_menu_button(menu_window, iteration, &is_menu_button_selected);

		iteration++;
		usleep(1000000 / FRAMES_PER_SECOND);
	}

	delwin(menu_window->window);
	free(menu_window);
}

void get_player_name(WINDOW *screen, STATE *game_state, int screen_center_x) {
	WIN *enter_name_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, true, PAIR_GAME_DEFAULT);

	clear_window(enter_name_window);

	echo();

	wattron(enter_name_window->window, COLOR_PAIR(PAIR_STAR));
	mvwprintw(enter_name_window->window, 5, (enter_name_window->width-16)/2, "Enter your name:");
	wattroff(enter_name_window->window, COLOR_PAIR(PAIR_STAR));

	wattron(enter_name_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_FULL));
	mvwgetnstr(enter_name_window->window, 6, (enter_name_window->width-16)/2, game_state->player_name, MAX_PLAYER_NAME_LENGTH);
	wattroff(enter_name_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_FULL));

	noecho();
	
	delwin(enter_name_window->window);
	free(enter_name_window);
}
