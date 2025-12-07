#pragma once

#include <unistd.h> // for usleep

#include "consts.h"
#include "window.h"
#include "state.h"

void handle_menu_input(WIN *menu_window, char key, STATE *game_state);
void show_menu_errors(WIN *menu_window);
void show_menu_title(WIN *menu_window);
void display_menu_button(WIN *menu_window, int iteration, bool *is_menu_button_selected);
void open_menu(WINDOW *screen, STATE *game_state, int screen_center_x);
void get_player_name(WINDOW *screen, STATE *game_state, int screen_center_x);
