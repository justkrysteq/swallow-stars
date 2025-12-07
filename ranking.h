#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "consts.h"
#include "window.h"
#include "state.h"

typedef struct {
	char player_name[MAX_PLAYER_NAME_LENGTH];
	int score;
} RANKING;

void display_top_scores(WINDOW *window, const char *current_player_name);

void save_score(STATE *game_state);
