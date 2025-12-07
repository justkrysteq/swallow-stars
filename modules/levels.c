#include "../headers/levels.h"

int *get_selected_level(void) {
	static int *selected_level = NULL;

	if (selected_level == NULL) {
		selected_level = select_level();
	}

	return selected_level;
}


int *select_level(void) {
	int *selected_level = (int *) malloc(sizeof(int));

	attron(COLOR_PAIR(PAIR_STAR));
	mvprintw(5, (COLS - 17) / 2, "  Select level:  ");
	attroff(COLOR_PAIR(PAIR_STAR));

	char key = 0;
	*selected_level = 0;

	while (true) {
		for (int i = 0; i < MAX_LEVELS; i++) {
			if (i != *selected_level) {
				attron(COLOR_PAIR(PAIR_MENU_BUTTON_SELECTED));
			} else {
				attron(COLOR_PAIR(PAIR_MENU_BUTTON));
			}

			mvprintw(10 + i, (COLS - 7) / 2, "Level %d", i);

			attroff(COLOR_PAIR(PAIR_MENU_BUTTON_SELECTED));
			attroff(COLOR_PAIR(PAIR_MENU_BUTTON));
		}

		key = (char) getch();

		if (key == QUIT) {
			break;
		}

		if (key == ENTER) {
			break;
		}

		if (key == MOVE_UP) {
			(*selected_level)--;
			if (*selected_level < 0) {
				*selected_level = MAX_LEVELS - 1;
			}
		}

		if (key == MOVE_DOWN) {
			(*selected_level)++;
			if (*selected_level > MAX_LEVELS - 1) {
				*selected_level = 0;
			}
		}
	}

	return selected_level;
}
