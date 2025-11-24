#include "headers/main.h"

void handle_bird_input(WIN *game_window, char key, BIRD *bird) {
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
		if (bird->speed > Player_Max_Speed) {
			bird->speed = Player_Max_Speed;
		}
	} else if (key == DECREASE_SPEED) {
		bird->speed--;
		if (bird->speed < Player_Min_Speed) {
			bird->speed = Player_Min_Speed;
		}
	}
};

void run_game() {
	WINDOW *screen = start_game();

	WIN *game_window = init_window(screen, Game_Height, Game_Width, 0, 0, true, false);
	WIN *status_window = init_window(screen, 7, Game_Width, game_window->height, 0, true, true);
	BIRD *bird = init_bird(game_window, game_window->height - 2, game_window->width / 2);

	char key;
	int iteration = 0;

	while (true) {
		key = wgetch(game_window->window);
		
		if (key == QUIT || Time_Limit == 0) {
			break;
		}

		handle_bird_input(game_window, key, bird);

		update_status(status_window);

		// TODO: implement updating whole game window, atm this is here:
		move_bird(bird);
		clear_window(game_window);
		draw_bird(bird);

		if (iteration % 10 == 0) {
			Time_Limit--;
		}

		iteration++;

		flushinp(); // avoids key press accumulation

    	usleep(FRAME_TIME * 1000); // receives value in microseconds
	}

	delwin(game_window->window);
	delwin(status_window->window);
	delwin(screen);

	endwin();

	free(game_window);
	free(status_window);
	free(bird);
}

int main(int argc, char *argv[]) {
	get_config("game.conf");
	run_game();

	return EXIT_SUCCESS;
}
