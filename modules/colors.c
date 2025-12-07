#include "../headers/colors.h"

void init_colors(void) {
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
}

void init_color_pairs_global(void) {
	init_pair(PAIR_GAME_DEFAULT, COLOR_GAME_FOREGROUND, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_STATUS, COLOR_STATUS_FOREGROUND, COLOR_STATUS_BACKGROUND);
	init_pair(PAIR_MENU_BUTTON, COLOR_BLACK, COLOR_WHITE);
	init_pair(PAIR_MENU_BUTTON_SELECTED, COLOR_WHITE, COLOR_BLACK);
}

void init_color_pairs_bird(void) {
	init_pair(PAIR_BIRD_LIFE_FORCE_FULL, COLOR_BIRD_LIFE_FORCE_FULL, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_BIRD_LIFE_FORCE_HALF, COLOR_BIRD_LIFE_FORCE_HALF, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_BIRD_LIFE_FORCE_LAST, COLOR_BIRD_LIFE_FORCE_LAST, COLOR_GAME_BACKGROUND);
}

void init_color_pairs_hunter(void) {
	init_pair(PAIR_HUNTER_DAMAGE_HIGH, COLOR_HUNTER_DAMAGE_HIGH, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_HUNTER_DAMAGE_MEDIUM, COLOR_HUNTER_DAMAGE_MEDIUM, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_HUNTER_DAMAGE_LOW, COLOR_HUNTER_DAMAGE_LOW, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_HUNTER_LABEL, COLOR_WHITE, COLOR_BLACK);
}

void init_color_pairs_star(void) {
	init_pair(PAIR_STAR, COLOR_STAR, COLOR_GAME_BACKGROUND);
	init_pair(PAIR_STAR_BLINK, COLOR_WHITE, COLOR_GAME_BACKGROUND);
}

void init_color_pairs_taxi(void) {
	init_pair(PAIR_ALBATROSS_TAXI, COLOR_YELLOW, COLOR_STAR);
	init_pair(PAIR_ALBATROSS_TAXI_TOP, COLOR_CYAN, COLOR_HUNTER_DAMAGE_LOW);
}

void init_color_pairs(void) {
	init_color_pairs_global();
	init_color_pairs_bird();
	init_color_pairs_hunter();
	init_color_pairs_star();
	init_color_pairs_taxi();
}

void color_setup(void) {
	start_color();

	init_colors();

	init_color_pairs();
}
