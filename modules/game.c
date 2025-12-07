#include "../headers/game.h"

void handle_taxi_state(WIN *game_window, BIRD *bird, STATE *game_state, ALBATROSS_TAXI *taxi, STAR *stars, HUNTER *hunters, OCCUPANT **occupancy_map) {
	if (taxi->exists) {
		move_taxi(taxi);
		clear_window(game_window);
		if (!taxi->is_bird_inside) {
			draw_bird(bird, true);
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

void handle_time_pass(STATE *game_state, int iteration) {
	if (iteration % (FRAMES_PER_SECOND) == 0) {
		game_state->time_left--;
		game_state->safe_zone_time_left--;
		game_state->hunter_spawn_rate_escalation += get_config()->hunter_spawn_rate_escalation;
		game_state->hunter_initial_bounces_escalation += get_config()->hunter_initial_bounces_escalation;
	}
}

void spawn_entities(STATE *game_state, BIRD *bird, STAR *stars, HUNTER *hunters, ALBATROSS_TAXI *taxi, char key, int iteration) {
	if (key == CALL_TAXI) {
		game_state->in_albatross_taxi = true;
		spawn_taxi(taxi, bird);
	}

	if (iteration % (int) (FRAMES_PER_SECOND/get_config()->star_spawn_rate) == 0) {
		spawn_star(stars);
	}

	if (iteration % (int) (FRAMES_PER_SECOND/get_config()->hunter_spawn_rate + ((int) (1 * game_state->hunter_spawn_rate_escalation))) == 0 && game_state->safe_zone_time_left <= 0) {
		spawn_hunter(hunters, bird, game_state->hunter_initial_bounces_escalation);
	}
}

void move_entities(STATE *game_state, BIRD *bird, STAR *stars, HUNTER *hunters, OCCUPANT **occupancy_map) {
	int bird_y = bird->y;
	int bird_x = bird->x;
	move_bird(bird);
	update_occupancy_map(occupancy_map, bird_y, bird_x, bird->y, bird->x, BIRD_TYPE, bird, game_state);

	for (int i = 0; i < MAX_STARS; i++) {
		int star_y = stars[i].y;
		int star_x = stars[i].x;
		move_star(&stars[i]);
		update_occupancy_map(occupancy_map, star_y, star_x, stars[i].y, stars[i].x, STAR_TYPE, &stars[i], game_state);
	}

	for (int i = 0; i < MAX_HUNTERS; i++) {
		int hunter_y = hunters[i].y;
		int hunter_x = hunters[i].x;
		move_hunter(&hunters[i], bird);
		update_occupancy_map(occupancy_map, hunter_y, hunter_x, hunters[i].y, hunters[i].x, HUNTER_TYPE, &hunters[i], game_state);
	}
}

void draw_entities(WIN *game_window, BIRD *bird, STAR *stars, HUNTER *hunters, int iteration) {
	clear_window(game_window);
	draw_bird(bird, (iteration % (int) ((FRAMES_PER_SECOND/get_config()->star_spawn_rate)/2) == 0));

	for (int i = 0; i < MAX_STARS; i++) {
		draw_star(&stars[i], (iteration % (int) ((FRAMES_PER_SECOND/get_config()->star_spawn_rate)/2) == 0));
	}

	for (int i = 0; i < MAX_HUNTERS; i++) {
		draw_hunter(hunters[i]);
	}
}

void handle_game_flow(WIN *game_window, BIRD *bird, STATE *game_state, ALBATROSS_TAXI *taxi, STAR *stars, HUNTER *hunters, OCCUPANT **occupancy_map, char key, int iteration) {
	spawn_entities(game_state, bird, stars, hunters, taxi, key, iteration);

	move_entities(game_state, bird, stars, hunters, occupancy_map);

	draw_entities(game_window, bird, stars, hunters, iteration);
}

void game_loop(WIN *game_window, WIN *status_window, BIRD *bird, STAR *stars, HUNTER *hunters, OCCUPANT **occupancy_map, ALBATROSS_TAXI *taxi, STATE *game_state) {
	int iteration = 0;
	char key = 0;

	while (game_state->running) {
		key = (char) wgetch(game_window->window);

		if (key == QUIT || game_state->time_left == 0) {
			game_state->running = false;
		}

		handle_bird_input(key, bird);

		update_status(status_window, game_state->time_left, game_state->stars_collected, bird->life_force, game_state->player_name);

		if (!game_state->in_albatross_taxi) {
			handle_game_flow(game_window, bird, game_state, taxi, stars, hunters, occupancy_map, key, iteration);
		} else {
			handle_taxi_state(game_window, bird, game_state, taxi, stars, hunters, occupancy_map);
		}

		// NOTE: temp
		// if (key == 'm' || key == 'b') {
		// 	print_occupancy_map(occupancy_map, occupancy_window);
		// }


		handle_time_pass(game_state, iteration);

		iteration++;
		flushinp(); // avoids key press accumulation
		usleep(1000000 / FRAMES_PER_SECOND);
	}
}

void calculate_score(STATE *game_state, BIRD *bird) {
	game_state->score += get_config()->score_life_multiplier * bird->life_force;
	game_state->score += get_config()->score_star_multiplier * game_state->stars_collected;
	game_state->score += get_config()->score_time_multiplier * game_state->time_left;
	game_state->score += get_config()->score_difficulty_multiplier * game_state->hunter_spawn_rate_escalation;
}

void handle_game_exit(WIN *game_window, WIN *status_window, BIRD *bird, HUNTER *hunters, STAR *stars, OCCUPANT **occupancy_map, ALBATROSS_TAXI *taxi) {
	werase(status_window->window);
	wrefresh(status_window->window);

	delwin(game_window->window);
	delwin(status_window->window);

	free_occupancy_map(occupancy_map, game_window);
	free(game_window);
	free(status_window);
	// free(occupancy_window);
	free(bird);
	free(hunters);
	free(stars);
	free(taxi);
}

void open_game(WINDOW *screen, STATE *game_state, int screen_center_x) {
	WIN *game_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, false, PAIR_GAME_DEFAULT);
	WIN *status_window = init_window(screen, 7, get_config()->game_width, game_window->height, screen_center_x, true, true, PAIR_STATUS);

	// NOTE: TEMP
	// WIN *occupancy_window = init_window(screen, get_config()->game_height, get_config()->game_width, game_window->height+15, 0, false, false, PAIR_GAME_DEFAULT);

	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);
	STAR *stars = create_star_table(game_window);
	HUNTER *hunters = create_hunter_table(game_window);
	OCCUPANT **occupancy_map = create_occupancy_map(game_window);
	ALBATROSS_TAXI *taxi = init_albatross_taxi(game_window);

	game_loop(game_window, status_window, bird, stars, hunters, occupancy_map, taxi, game_state);

	calculate_score(game_state, bird);
	save_score(game_state);

	handle_game_exit(game_window, status_window, bird, hunters, stars, occupancy_map, taxi);
}

void display_game_over_text(WIN *over_window) {
	wattron(over_window->window, COLOR_PAIR(PAIR_STAR));

	mvwprintw(over_window->window, 2, (over_window->width-45)/2, GAME_OVER_LINE_1);
	mvwprintw(over_window->window, 3, (over_window->width-45)/2, GAME_OVER_LINE_2);
	mvwprintw(over_window->window, 4, (over_window->width-45)/2, GAME_OVER_LINE_3);
	mvwprintw(over_window->window, 5, (over_window->width-45)/2, GAME_OVER_LINE_4);

	wattroff(over_window->window, COLOR_PAIR(PAIR_STAR));
}

void display_player_score(WIN *over_window, STATE *game_state) {
	wattron(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_LAST));

	mvwprintw(over_window->window, 8, (over_window->width-15)/2, "Your score: %d", game_state->score);

	wattroff(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_LAST));
}

void display_ranking(WIN *over_window, STATE *game_state) {
	wattron(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_HALF));
	mvwprintw(over_window->window, 10, (over_window->width-15)/2, "RANKING (TOP 5)");
	wattroff(over_window->window, COLOR_PAIR(PAIR_BIRD_LIFE_FORCE_HALF));
	wattron(over_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
	mvwprintw(over_window->window, 11, 1, "Player\tScore");
	wattroff(over_window->window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));

	display_top_scores(over_window->window, game_state->player_name);
}

void show_game_over(WINDOW *screen, STATE *game_state, int screen_center_x) {
	WIN *over_window = init_window(screen, get_config()->game_height, get_config()->game_width, 0, screen_center_x, true, true, PAIR_GAME_DEFAULT);

	clear_window(over_window);

	display_game_over_text(over_window);
	display_player_score(over_window, game_state);
	display_ranking(over_window, game_state);

	wgetch(over_window->window);

	delwin(over_window->window);
	free(over_window);
}

void run_game(void) {
	WINDOW *screen = init_screen();

	color_setup();

	int screen_center_x = (COLS - get_config()->game_width) / 2;
	STATE *game_state = init_state();

	open_menu(screen, game_state, screen_center_x);
	get_player_name(screen, game_state, screen_center_x);
	// TODO: select level
	open_game(screen, game_state, screen_center_x);
	show_game_over(screen, game_state, screen_center_x);

	delwin(screen);
	endwin();

	free((void *) get_config());
	free(game_state);
}
