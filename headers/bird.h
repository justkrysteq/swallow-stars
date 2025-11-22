#include "window.h"
#include "consts.h"

/**
 * **ncurses bird struct with attributes for later use**
 *
 * *Attributes:*
 * - **parent_window**: *pointer to parent window*
 * - **y**: *y coordinate of bird*
 * - **x**: *x coordinate of bird*
 * - **speed**: *speed of bird*
 * - **sprite**: *character to be displayed*
 * - **life_force**: *bird's hp*
 */
typedef struct {
	WIN *parent_window;
	int y, x;
	int speed; // speed of movement 1-5
	char sprite;
	int life_force;
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
 * **draws a bird**
 *
 * *Parameters:*
 * - **bird**: *pointer to a bird*
 */
void draw_bird(BIRD *bird);
