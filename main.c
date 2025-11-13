#include <curses.h>

#define EXIT_SUCCESS 0

int main(int argc, char *argv[]) {
	initscr();

	move(10, 10);
	printw("Hello, world!\n");

	getch();

	endwin();

	return EXIT_SUCCESS;
}
