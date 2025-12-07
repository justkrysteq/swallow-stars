#include "ranking.h"

int compare_scores(const void *a, const void *b) {
	RANKING *playerA = (RANKING *)a;
	RANKING *playerB = (RANKING *)b;
	return playerB->score - playerA->score;
}

void display_top_scores(WINDOW *window, const char *current_player_name) {
	FILE *ranking_file_read = fopen(RANKING_FILE, "r");

	RANKING rankings[MAX_RANKINGS];
	int line_count = 0;

	char line[128];

	while (fgets(line, sizeof(line), ranking_file_read) && line_count < MAX_RANKINGS) {
		if (line[0] == '\t') {
			strcpy(rankings[line_count].player_name, "unnamed player");
			rankings[line_count].score = atoi(line);
		} else {
			strcpy(rankings[line_count].player_name, strtok(line, "\t"));
			rankings[line_count].score = atoi(strtok(NULL, "\t"));
		}
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

void save_score(STATE *game_state) {
	FILE *ranking_file = fopen(RANKING_FILE, "a");

	if (ranking_file == NULL) {
		ranking_file = fopen(RANKING_FILE, "w");
		fprintf(ranking_file, "%s\t%d\n", game_state->player_name, game_state->score);
		fclose(ranking_file);
	} else {
		fprintf(ranking_file, "%s\t%d\n", game_state->player_name, game_state->score);
	}

	fclose(ranking_file);
}
