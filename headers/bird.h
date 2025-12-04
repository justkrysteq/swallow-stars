#pragma once

#include "window.h"
#include "consts.h"
#include "config.h"

/**
 * **ncurses bird struct with attributes for later use**
 *
 * *Attributes:*
 * - **y**: *y coordinate of bird*
 * - **x**: *x coordinate of bird*
 * - **speed**: *speed of bird*
 * - **sprite**: *character to be displayed*
 * - **life_force**: *bird's hp*
 * - **parent_window**: *pointer to parent window*
 */
typedef struct {
	float y, x;
	int dir_y, dir_x;
	unsigned int speed; // speed of movement 1-5
	char sprite;
	unsigned int life_force;
	WIN *parent_window;
} BIRD;

/**
 * **Initializes a bird**
 *
 * *Parameters:*
 * - **parent_window**: *pointer to parent window*
 * - **y**: *y coordinate of top left corner*
 * - **x**: *x coordinate of top left corner*
 *
 * *Returns:* pointer to a bird
 */
BIRD *init_bird(WIN *parent_window, int y, int x);

/**
 * **Draws a bird**
 *
 * *Parameters:*
 * - **bird**: *pointer to a bird*
 */
void draw_bird(BIRD *bird);

/**
 * **Moves a bird**
 *
 * Moves the bird in the direction specified by the bird's dir_x and dir_y
 * If the bird hits a border, it will bounce back
 *
 * *Parameters:*
 * - **bird**: *pointer to a bird*
 */
void move_bird(BIRD *bird);

/**
 * **Handles bird input**
 *
 * Handles input from the user and updates the bird's direction and speed
 *
 * *Parameters:*
 * - **key**: *key pressed*
 * - **bird**: *pointer to a bird*
 */
void handle_bird_input(char key, BIRD *bird);
