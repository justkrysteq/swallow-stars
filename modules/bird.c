#include "../headers/bird.h"

BIRD *init_bird(WIN *parent_window, int y, int x) {
	BIRD *bird = (BIRD *) malloc(sizeof(BIRD));

	bird->parent_window = parent_window;
	bird->y = y;
	bird->x = x;
	bird->dir_y = UP_DIRECTION;
	bird->dir_x = 0;
	bird->speed = Player_Initial_Speed;
	bird->sprite = Player_Sprite;
	bird->life_force = Player_Life_Force;

	return bird;
}

void draw_bird(BIRD *bird) {
	mvwprintw(bird->parent_window->window, bird->y, bird->x, "%c", bird->sprite);
}

void move_bird(BIRD *bird) {
	if (bird->dir_y == UP_DIRECTION) {
		bird->y += UP_DIRECTION * bird->speed*0.5;
	}
	else if (bird->dir_y == DOWN_DIRECTION) {
		bird->y += DOWN_DIRECTION * bird->speed*0.5;
	}

	if (bird->dir_x == LEFT_DIRECTION) {
		bird->x += LEFT_DIRECTION * bird->speed;
	}
	else if (bird->dir_x == RIGHT_DIRECTION) {
		bird->x += RIGHT_DIRECTION * bird->speed;
	}

	wrefresh(bird->parent_window->window);
}
