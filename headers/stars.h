#pragma once

#include "window.h"
#include "consts.h"
// #include "state.h"

typedef struct {
	float x, y;
	float speed;
	char sprite;
	bool exists;
	WIN *parent_window;
} STAR;

/**
 * **Draws a star**
 *
 * *Parameters:*
 * - **star**: *star to be drawn*
 */
void draw_star(const STAR star);

/**
 * **Initializes a star**
 *
 * *Parameters:*
 * - **parent_window**: *pointer to parent window*
 *
 * *Returns:* pointer to a star
 */
STAR init_star(WIN *parent_window);

/**
 * **Moves a star**
 *
 * *Parameters:*
 * - **star**: *star to be moved*
 */
void move_star(STAR *star, bool change_sprite);

STAR *create_star_table(WIN *parent_window);

void spawn_star(STAR *stars);
