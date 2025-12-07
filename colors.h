#pragma once

#include <curses.h>

#include "consts.h"

void init_colors(void);
void init_color_pairs_global(void);
void init_color_pairs_bird(void);
void init_color_pairs_hunter(void);
void init_color_pairs_star(void);
void init_color_pairs_taxi(void);
void init_color_pairs(void);
void color_setup(void);
