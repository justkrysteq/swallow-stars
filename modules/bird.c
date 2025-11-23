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
		float new_y = bird->y + UP_DIRECTION * bird->speed*0.5;
		if (new_y < 1) {
			new_y = 2;
			bird->dir_y = DOWN_DIRECTION;
			bird->sprite = PLAYER_SPRITE_DOWN;
		}
		bird->y = new_y;
	}
	else if (bird->dir_y == DOWN_DIRECTION) {
		float new_y = bird->y + DOWN_DIRECTION * bird->speed*0.5;
		if (new_y > Game_Height - 2) {
			new_y = Game_Height - 2.5;
			bird->dir_y = UP_DIRECTION;
			bird->sprite = PLAYER_SPRITE_UP;
		}
		bird->y = new_y;
	}

	if (bird->dir_x == LEFT_DIRECTION) {
		float new_x = bird->x + LEFT_DIRECTION * bird->speed;
		if (new_x < 1) {
			new_x = 2;
			bird->dir_x = RIGHT_DIRECTION;
			bird->sprite = PLAYER_SPRITE_RIGHT;
		}
		bird->x = new_x;
	}
	else if (bird->dir_x == RIGHT_DIRECTION) {
		float new_x = bird->x + RIGHT_DIRECTION * bird->speed;
		if (new_x > Game_Width - 2) {
			new_x = Game_Width - 3;
			bird->dir_x = LEFT_DIRECTION;
			bird->sprite = PLAYER_SPRITE_LEFT;
		}
		bird->x = new_x;
	}

	wrefresh(bird->parent_window->window);
}
