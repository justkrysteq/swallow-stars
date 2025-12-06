#include "../headers/ranking.h"

int compare_scores(const void *a, const void *b) {
	RANKING *playerA = (RANKING *)a;
	RANKING *playerB = (RANKING *)b;
	return playerB->score - playerA->score;
}

void display_rankings(WINDOW *window, const char *current_player_name) {
	FILE *ranking_file_read = fopen("ranking.txt", "r");

	RANKING rankings[MAX_RANKINGS];
	int line_count = 0;

	char line[128];

	while (fgets(line, sizeof(line), ranking_file_read) && line_count < MAX_RANKINGS) {
		strcpy(rankings[line_count].player_name, strtok(line, "\t"));
		rankings[line_count].score = atoi(strtok(NULL, "\t"));
		line_count++;
	}

	fclose(ranking_file_read);

	qsort(rankings, line_count, sizeof(RANKING), compare_scores);

	for (int i = 0; i < line_count && i < 5; i++) {
		if (strcmp(rankings[i].player_name, current_player_name) == 0) {
			wattron(window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_HIGH));
		} else {
			wattron(window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
		}
		mvwprintw(window, 13 + i, 1, "%s\t%d", rankings[i].player_name, rankings[i].score);
		wattroff(window, COLOR_PAIR(PAIR_HUNTER_DAMAGE_LOW));
	}
}
