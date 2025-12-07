#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>

#include "consts.h"
#include "bird.h"
#include "config.h"
#include "utils.h"
#include "state.h"
#include "occupancy_map.h"
#include "albatross_taxi.h"
#include "ranking.h"
#include "menu.h"
#include "colors.h"

void run_game(void);
