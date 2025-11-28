#include "window.h"
#include "consts.h"

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
 * - **x**: *x coordinate of star*
 *
 * *Returns:* pointer to a star
 */
STAR *init_star(WIN *parent_window, int x);

/**
 * **Moves a star**
 *
 * *Parameters:*
 * - **star**: *star to be moved*
 */
void move_star(STAR *star);
