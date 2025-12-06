#include "headers/main.h"

void color_setup(void) {
	start_color();

	init_color(COLOR_GAME_BACKGROUND, 12, 0, 240);
	init_color(COLOR_GAME_FOREGROUND, 247, 0, 619);
	init_color(COLOR_STATUS_BACKGROUND, 0, 0, 0);
	init_color(COLOR_STATUS_FOREGROUND, 447, 0, 819);
	init_color(COLOR_STAR, 999, 905, 0);
	init_color(COLOR_BIRD_LIFE_FORCE_FULL, 117, 999, 0);
	init_color(COLOR_BIRD_LIFE_FORCE_HALF, 999, 624, 0);
	init_color(COLOR_BIRD_LIFE_FORCE_LAST, 999, 200, 0);
	init_color(COLOR_HUNTER_DAMAGE_HIGH, 999, 0, 0);
	init_color(COLOR_HUNTER_DAMAGE_MEDIUM, 700, 0, 999);
	init_color(COLOR_HUNTER_DAMAGE_LOW, 400, 800, 999);

	init_pair(PAIR_GAME_DEFAULT, COLOR_GAME_FOREGROUND, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_STATUS, COLOR_STATUS_FOREGROUND, COLOR_STATUS_BACKGROUND);
	init_pair(PAIR_STAR, COLOR_STAR, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_BIRD_LIFE_FORCE_FULL, COLOR_BIRD_LIFE_FORCE_FULL, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_BIRD_LIFE_FORCE_HALF, COLOR_BIRD_LIFE_FORCE_HALF, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_BIRD_LIFE_FORCE_LAST, COLOR_BIRD_LIFE_FORCE_LAST, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_HUNTER_DAMAGE_HIGH, COLOR_HUNTER_DAMAGE_HIGH, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_HUNTER_DAMAGE_MEDIUM, COLOR_HUNTER_DAMAGE_MEDIUM, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_HUNTER_DAMAGE_LOW, COLOR_HUNTER_DAMAGE_LOW, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_ALBATROSS_TAXI, COLOR_YELLOW, COLOR_STAR);
	init_pair(PAIR_ALBATROSS_TAXI_TOP, COLOR_CYAN, COLOR_HUNTER_DAMAGE_LOW);
	init_pair(PAIR_HUNTER_LABEL, COLOR_WHITE, COLOR_BLACK);
	init_pair(PAIR_MENU_BUTTON, COLOR_BLACK, COLOR_WHITE);
	init_pair(PAIR_MENU_BUTTON_SELECTED, COLOR_WHITE, COLOR_BLACK);
}

void run_game(void) {
	WINDOW *screen = init_screen();

	color_setup();

	int screen_center_x = (COLS - get_config()->game_width) / 2;
	STATE *game_state = init_state();

	WIN *menu_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, false, PAIR_GAME_DEFAULT);

	int iteration = 0;
	char key = 0;
	bool is_menu_button_selected = false;

	while (game_state->in_menu) {
		key = (char) wgetch(menu_window->window);
		
		if (key == ENTER) {
			game_state->in_menu = false;
		}

		if (key == QUIT) {
			game_state->in_menu = false;
			game_state->running = false;
		}

		clear_window(menu_window);
		if (!has_colors()) {
			mvwprintw(menu_window->window, menu_window->height-3, 1, "[!] Your terminal does not support colors");
		}

		if (!can_change_color()) {
			mvwprintw(menu_window->window, menu_window->height-2, 1, "[!] Your terminal does not support changing colors");
		}

		wattron(menu_window->window, COLOR_PAIR(PAIR_STAR));
		mvwprintw(menu_window->window, 2, (menu_window->width-64)/2, " ____               _ _                 ____  _                 ");
		mvwprintw(menu_window->window, 3, (menu_window->width-64)/2, "/ ___|_      ____ _| | | _____      __ / ___|| |_ __ _ _ __ ___ ");
		mvwprintw(menu_window->window, 4, (menu_window->width-64)/2, "\\___ \\ \\ /\\ / / _` | | |/ _ \\ \\ /\\ / / \\___ \\| __/ _` | '__/ __|");
		mvwprintw(menu_window->window, 5, (menu_window->width-64)/2, " ___) \\ V  V / (_| | | | (_) \\ V  V /   ___) | || (_| | |  \\__ \\");
		mvwprintw(menu_window->window, 6, (menu_window->width-64)/2, "|____/ \\_/\\_/ \\__,_|_|_|\\___/ \\_/\\_/   |____/ \\__\\__,_|_|  |___/");
		wattroff(menu_window->window, COLOR_PAIR(PAIR_STAR));

		if (is_menu_button_selected) {
			wattron(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON_SELECTED));
		} else {
			wattron(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON));
		}
		mvwprintw(menu_window->window, 10, (menu_window->width-12)/2, "    Play    ");
		wattroff(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON_SELECTED));
		wattroff(menu_window->window, COLOR_PAIR(PAIR_MENU_BUTTON));

		iteration++;
		if (iteration % (FRAMES_PER_SECOND) == 0) {
			if (is_menu_button_selected) {
				is_menu_button_selected = false;
			} else {
				is_menu_button_selected = true;
			}
		}

		usleep(1000000 / FRAMES_PER_SECOND);
	}

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

	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, false, PAIR_GAME_DEFAULT);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, screen_center_x, true, true, PAIR_STATUS);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	// NOTE: TEMP
	WIN *occupancy_window = init_window(screen, get_config()->game_height, get_config()->game_width, game_window->height+15, 0, false, false, PAIR_GAME_DEFAULT);

	iteration = 0;

	STAR *stars = create_star_table(game_window);
	HUNTER *hunters = create_hunter_table(game_window);
	OCCUPANT **occupancy_map = create_occupancy_map(game_window);
	ALBATROSS_TAXI *taxi = init_albatross_taxi(game_window);

	while (game_state->running) {
		key = (char) wgetch(game_window->window);

		if (key == QUIT || game_state->time_left == 0) {
			game_state->running = false;
		}

		update_status(status_window, game_state->time_left, game_state->stars_collected, bird->life_force, game_state->player_name);

		if (!game_state->in_albatross_taxi) {
			if (key == CALL_TAXI) {
				game_state->in_albatross_taxi = true;
				spawn_taxi(taxi, bird);
			}

			handle_bird_input(key, bird);

			// TODO: implement updating whole game window, atm this is here:
			int bird_y = bird->y;
			int bird_x = bird->x;
			move_bird(bird);
			update_occupancy_map(occupancy_map, bird_y, bird_x, bird->y, bird->x, BIRD_TYPE, bird, game_state);

			if (iteration % (int) (FRAMES_PER_SECOND/get_config()->star_spawn_rate) == 0) {
				spawn_star(stars);
			}

			if (iteration % (int) (FRAMES_PER_SECOND/get_config()->hunter_spawn_rate + ((int) (1 * game_state->hunter_spawn_rate_escalation))) == 0 && game_state->safe_zone_time_left <= 0) {
			// if (iteration % (int) (FRAMES_PER_SECOND/get_config()->hunter_spawn_rate) == 0 && game_state->safe_zone_time_left <= 0) {
				spawn_hunter(hunters, bird, game_state->hunter_initial_bounces_escalation);
			}

			for (int i = 0; i < MAX_STARS; i++) {
				int star_y = stars[i].y;
				int star_x = stars[i].x;
				move_star(&stars[i], (iteration % (int) ((FRAMES_PER_SECOND/get_config()->star_spawn_rate)/2) == 0));
				update_occupancy_map(occupancy_map, star_y, star_x, stars[i].y, stars[i].x, STAR_TYPE, &stars[i], game_state);
			}

			for (int i = 0; i < MAX_HUNTERS; i++) {
				int hunter_y = hunters[i].y;
				int hunter_x = hunters[i].x;
				move_hunter(&hunters[i], bird);
				update_occupancy_map(occupancy_map, hunter_y, hunter_x, hunters[i].y, hunters[i].x, HUNTER_TYPE, &hunters[i], game_state);
			}
			
			clear_window(game_window);
			draw_bird(bird);

			for (int i = 0; i < MAX_STARS; i++) {
				draw_star(stars[i]);
			}

			for (int i = 0; i < MAX_HUNTERS; i++) {
				draw_hunter(hunters[i]);
			}
		} else {
			if (taxi->exists) {
				move_taxi(taxi);
				clear_window(game_window);
				if (!taxi->is_bird_inside) {
					draw_bird(bird);
				}
				draw_taxi(*taxi);
				wrefresh(game_window->window);
			} else {
				for (int i = 0; i < MAX_STARS; i++) {
					if (stars[i].exists) {
						stars[i].exists = false;
					}
				}

				for (int i = 0; i < MAX_HUNTERS; i++) {
					if (hunters[i].exists) {
						hunters[i].exists = false;
					}
				}

				game_state->in_albatross_taxi = false;
				game_state->safe_zone_time_left = SAFE_ZONE_TIME;

				clear_occupancy_map(occupancy_map, game_window);

				bird->y = taxi->y;
				bird->x = taxi->x;
			}
		}

		// NOTE: temp
		if (key == 'm' || key == 'b') {
			print_occupancy_map(occupancy_map, occupancy_window);
		}

		iteration++;
		if (iteration % (FRAMES_PER_SECOND) == 0) {
			game_state->time_left--;
			game_state->safe_zone_time_left--;
			game_state->hunter_spawn_rate_escalation += get_config()->hunter_spawn_rate_escalation;
			game_state->hunter_initial_bounces_escalation += get_config()->hunter_initial_bounces_escalation;
		}

		flushinp(); // avoids key press accumulation
		usleep(1000000 / FRAMES_PER_SECOND);
	}

	// TODO: implement game over screen
	// if (game_state->time_left == 0) {
	// 	game_over(false);
	// }
	//
	// if (bird->life_force <= 0) {
	// 	game_over(false);
	// }
	//
	// if (game_state->stars_collected == get_config()->star_quota) {
	// 	game_over(true);
	// }

	// TODO: Count score
	game_state->score += get_config()->score_life_multiplier * bird->life_force;
	game_state->score += get_config()->score_star_multiplier * game_state->stars_collected;
	game_state->score += get_config()->score_time_multiplier * game_state->time_left;
	game_state->score += get_config()->score_difficulty_multiplier * game_state->hunter_spawn_rate_escalation;

	FILE *ranking_file = fopen("ranking.txt", "a");
	if (ranking_file == NULL) {
		ranking_file = fopen("ranking.txt", "w");
		fprintf(ranking_file, "%s\t%d\n", game_state->player_name, game_state->score);
		fclose(ranking_file);
	} else {
		fprintf(ranking_file, "%s\t%d\n", game_state->player_name, game_state->score);
	}
	fclose(ranking_file);

	WIN *over_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, true, PAIR_GAME_DEFAULT);
	clear_window(over_window);
	werase(status_window->window);
	wrefresh(status_window->window);

	wattron(over_window->window, COLOR_PAIR(PAIR_STAR));
	mvwprintw(over_window->window, 2, (over_window->width-45)/2, "  ________   __  _______  ____ _   _________ ");
	mvwprintw(over_window->window, 3, (over_window->width-45)/2, " / ___/ _ | /  |/  / __/ / __ \\ | / / __/ _ \\");
	mvwprintw(over_window->window, 4, (over_window->width-45)/2, "/ (_ / __ |/ /|_/ / _/  / /_/ / |/ / _// , _/");
	mvwprintw(over_window->window, 5, (over_window->width-45)/2, "\\___/_/ |_/_/  /_/___/  \\____/|___/___/_/|_| ");
	wattroff(over_window->window, COLOR_PAIR(PAIR_STAR));

	wattron(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_LAST));
	mvwprintw(over_window->window, 8, (over_window->width-15)/2, "Your score: %d", game_state->score);
	wattroff(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_LAST));

	wattron(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_HALF));
	mvwprintw(over_window->window, 10, (over_window->width-15)/2, "RANKING (TOP 5)");
	wattroff(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_HALF));
	wattron(over_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
	mvwprintw(over_window->window, 11, 1, "Player\tScore");
	wattroff(over_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));

	display_rankings(over_window->window, game_state->player_name);

	wgetch(over_window->window);




	delwin(over_window->window);
	delwin(menu_window->window); // TODO: move higher
	delwin(enter_name_window->window);
	delwin(game_window->window);
	delwin(status_window->window);
	delwin(screen);

	endwin();

	free_occupancy_map(occupancy_map, game_window);
	free(over_window);
	free(menu_window);
	free(enter_name_window);
	free(game_window);
	free(status_window);
	free(occupancy_window);
	free(bird);
	free(hunters);
	free((void *) get_config());
	free(stars);
	free(game_state);
	free(taxi);
}

// int main(int argc, char *argv[]) {
int main(void) {
	run_game();

	return EXIT_SUCCESS;
}
