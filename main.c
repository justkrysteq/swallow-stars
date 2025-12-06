#include "headers/main.h"

void color_setup(void) {
	if (!has_colors()) {
		printf("[!] Your terminal does not support colors\n");
	}

	if (!can_change_color()) {
		printf("[!] Your terminal does not support changing colors\n");
	}

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
}

void run_game(void) {
	WINDOW *screen = init_screen();

	color_setup();

	int screen_center_x = (COLS - get_config()->game_width) / 2;
	STATE *game_state = init_state();

	// WIN *menu_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, false, PAIR_GAME_DEFAULT);
	//
	// while (game_state->in_menu) {
	// 	draw_menu(menu_window);
	// 	wrefresh(menu_window->window);
	// 	usleep(1000000 / FRAMES_PER_SECOND);
	// }

	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, false, PAIR_GAME_DEFAULT);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, screen_center_x, true, true, PAIR_STATUS);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	// NOTE: TEMP
	WIN *occupancy_window = init_window(screen, get_config()->game_height, get_config()->game_width, game_window->height+15, 0, false, false, PAIR_GAME_DEFAULT);

	char key = 0;
	int iteration = 0;

	STAR *stars = create_star_table(game_window);
	HUNTER *hunters = create_hunter_table(game_window);
	OCCUPANT **occupancy_map = create_occupancy_map(game_window);
	ALBATROSS_TAXI *taxi = init_albatross_taxi(game_window);

	while (game_state->running) {
		key = (char) wgetch(game_window->window);

		if (key == QUIT || game_state->time_left == 0) {
			game_state->running = false;
		}

		update_status(status_window, game_state->time_left, game_state->stars_collected, bird->life_force);

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
	// 	game_over(GAME_LOST);
	// }
	//
	// if (bird->life_force <= 0) {
	// 	game_over(GAME_LOST);
	// }
	//
	// if (game_state->stars_collected == get_config()->star_quota) {
	// 	game_over(GAME_WON);
	// }

	delwin(game_window->window);
	delwin(status_window->window);
	delwin(screen);

	endwin();

	free_occupancy_map(occupancy_map, game_window);
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
