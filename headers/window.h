#include <curses.h>
#include <stdlib.h>

/**
 * **ncurses window struct with attributes for later use**
 *
 * *Attributes:*
 * - **window**: *pointer to this window*
 * - **height**: *height of window*
 * - **width**: *width of window*
 * - **start_y**: *y coordinate of top left corner*
 * - **start_x**: *x coordinate of top left corner*
 */
typedef struct {
	WINDOW *window;
	int height, width;
	int start_y, start_x;
	// int color;
} WIN;

/**
 * **Initializes game screen**
 *
 * *Returns:* game screen
 */
WINDOW *start_game();

/**
 * **Initializes a window**
 *
 * *Parameters:*
 * - **parent_window**: *pointer to parent window*
 * - **height**: *height of window*
 * - **width**: *width of window*
 * - **start_y**: *y coordinate of top left corner*
 * - **start_x**: *x coordinate of top left corner*
 * - **has_border**: *whether or not to have a border*
 * - **wait_for_input**: *whether or not to freeze the screen until input is received*
 *
 * *Returns:* pointer to a window
 */
WIN *init_window(WINDOW *parent_window, int height, int width, int start_y, int start_x, bool has_border, bool wait_for_input);
