#include "../headers/bird.h"

BIRD *init_bird(WIN *parent_window, int y, int x) {
	BIRD *bird = (BIRD *) malloc(sizeof(BIRD));

	bird->parent_window = parent_window;
	bird->y = y;
	bird->x = x;
	bird->dir_y = UP_DIRECTION;
	bird->dir_x = 0;
	bird->speed = get_config()->player->initial_speed;
	bird->sprite = PLAYER_SPRITE_UP;
	bird->life_force = get_config()->player->life_force;

	return bird;
}

void draw_bird(BIRD *bird) {
	mvwprintw(bird->parent_window->window, bird->y, bird->x, "%c", bird->sprite);
}

void move_bird(BIRD *bird) {
	const float speed_factor = 1000 / (FRAMES_PER_SECOND * 50.0);
	float speed = bird->speed*speed_factor;

	if (bird->dir_y != 0) {
		speed *= 0.5;
	}

	if (bird->dir_y == UP_DIRECTION) {
		float new_y = bird->y + UP_DIRECTION * speed;
		if (new_y < 1) {
			new_y = 1;
			bird->dir_y = DOWN_DIRECTION;
			bird->sprite = PLAYER_SPRITE_DOWN;
		}
		bird->y = new_y;
	} else if (bird->dir_y == DOWN_DIRECTION) {
		float new_y = bird->y + DOWN_DIRECTION * speed;
		if (new_y > bird->parent_window->height - 2) {
			new_y = bird->parent_window->height - 2;
			bird->dir_y = UP_DIRECTION;
			bird->sprite = PLAYER_SPRITE_UP;
		}
		bird->y = new_y;
	}

	if (bird->dir_x == LEFT_DIRECTION) {
		float new_x = bird->x + LEFT_DIRECTION * speed;
		if (new_x < 1) {
			new_x = 1;
			bird->dir_x = RIGHT_DIRECTION;
			bird->sprite = PLAYER_SPRITE_RIGHT;
		}
		bird->x = new_x;
	} else if (bird->dir_x == RIGHT_DIRECTION) {
		float new_x = bird->x + RIGHT_DIRECTION * speed;
		if (new_x > bird->parent_window->width - 2) {
			new_x = bird->parent_window->width - 2;
			bird->dir_x = LEFT_DIRECTION;
			bird->sprite = PLAYER_SPRITE_LEFT;
		}
		bird->x = new_x;
	}

	wrefresh(bird->parent_window->window);
}

void handle_bird_input(char key, BIRD *bird) {
	if (key == MOVE_UP) {
		bird->dir_y = UP_DIRECTION;
		bird->dir_x = 0;
		bird->sprite = PLAYER_SPRITE_UP;
	} else if (key == MOVE_DOWN) {
		bird->dir_y = DOWN_DIRECTION;
		bird->dir_x = 0;
		bird->sprite = PLAYER_SPRITE_DOWN;
	} else if (key == MOVE_LEFT) {
		bird->dir_x = LEFT_DIRECTION;
		bird->dir_y = 0;
		bird->sprite = PLAYER_SPRITE_LEFT;
	} else if (key == MOVE_RIGHT) {
		bird->dir_x = RIGHT_DIRECTION;
		bird->dir_y = 0;
		bird->sprite = PLAYER_SPRITE_RIGHT;
	} else if (key == INCREASE_SPEED) {
		bird->speed++;
		if (bird->speed > get_config()->player->max_speed) {
			bird->speed = get_config()->player->max_speed;
		}
	} else if (key == DECREASE_SPEED) {
		bird->speed--;
		if (bird->speed < get_config()->player->min_speed) {
			bird->speed = get_config()->player->min_speed;
		}
	}
}
