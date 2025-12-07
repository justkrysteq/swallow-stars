#pragma once

// ---- CONTROL KEYS ----
#define QUIT 'q'
#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_LEFT 'a'
#define MOVE_RIGHT 'd'
#define INCREASE_SPEED 'p'
#define DECREASE_SPEED 'o'
#define CALL_TAXI 't'
#define ENTER '\n'

#define UP_DIRECTION -1
#define DOWN_DIRECTION 1
#define LEFT_DIRECTION -1
#define RIGHT_DIRECTION 1

#define PLAYER_SPRITE_UP '^'
#define PLAYER_SPRITE_DOWN 'v'
#define PLAYER_SPRITE_LEFT '<'
#define PLAYER_SPRITE_RIGHT '>'
#define PLAYER_SPRITE_UP_FLAPPING 'A'
#define PLAYER_SPRITE_DOWN_FLAPPING '|'
#define PLAYER_SPRITE_LEFT_FLAPPING '{'
#define PLAYER_SPRITE_RIGHT_FLAPPING '}'

#define STAR_SPRITE '*'
#define STAR_SPRITE_BLINK '+'

#define FRAMES_PER_SECOND 200
#define SPEED_FACTOR (1000/(FRAMES_PER_SECOND*100.0))

#define BORDER_SIZE 1
#define MAX_STARS 25
#define MAX_HUNTERS 10
#define HUNTER_WAIT_TIME 200
#define HUNTER_DASH_TIME 150
#define DASH_SPEED_MULTIPLIER 3
#define SAFE_ZONE_TIME 5
#define MAX_PLAYER_NAME_LENGTH 20
#define MAX_RANKINGS 100
#define MAX_LEVEL_LENGTH 25
#define MAX_LEVELS 5
#define DEFAULT_LEVEL "default.conf"
#define TAXI_SPEED 6

#define HUNTER_DAMAGE_HIGH 5
#define HUNTER_DAMAGE_MEDIUM 3
#define HUNTER_DAMAGE_LOW 1

#define BIRD_TYPE 'b'
#define HUNTER_TYPE 'h'
#define STAR_TYPE 's'
#define EMPTY_TYPE 'e'
#define WALL_TYPE 'w'

#define COLOR_GAME_BACKGROUND 16
#define COLOR_GAME_FOREGROUND 17
#define COLOR_STATUS_BACKGROUND 18
#define COLOR_STATUS_FOREGROUND 19
#define COLOR_STAR 20
#define COLOR_BIRD_LIFE_FORCE_FULL 21
#define COLOR_BIRD_LIFE_FORCE_HALF 22
#define COLOR_BIRD_LIFE_FORCE_LAST 23
#define COLOR_HUNTER_DAMAGE_HIGH 24
#define COLOR_HUNTER_DAMAGE_MEDIUM 25
#define COLOR_HUNTER_DAMAGE_LOW 26

#define PAIR_GAME_DEFAULT 1
#define PAIR_STATUS 2
#define PAIR_STAR 3
#define PAIR_BIRD_LIFE_FORCE_FULL 4
#define PAIR_BIRD_LIFE_FORCE_HALF 5
#define PAIR_BIRD_LIFE_FORCE_LAST 6
#define PAIR_HUNTER_DAMAGE_HIGH 7
#define PAIR_HUNTER_DAMAGE_MEDIUM 8
#define PAIR_HUNTER_DAMAGE_LOW 9
#define PAIR_ALBATROSS_TAXI 10
#define PAIR_ALBATROSS_TAXI_TOP 11
#define PAIR_HUNTER_LABEL 12
#define PAIR_MENU_BUTTON 13
#define PAIR_MENU_BUTTON_SELECTED 14
#define PAIR_STAR_BLINK 15

#define MENU_TITLE_LINE_1 " ____               _ _                 ____  _                 "
#define MENU_TITLE_LINE_2 "/ ___|_      ____ _| | | _____      __ / ___|| |_ __ _ _ __ ___ "
#define MENU_TITLE_LINE_3 "\\___ \\ \\ /\\ / / _` | | |/ _ \\ \\ /\\ / / \\___ \\| __/ _` | '__/ __|"
#define MENU_TITLE_LINE_4 " ___) \\ V  V / (_| | | | (_) \\ V  V /   ___) | || (_| | |  \\__ \\"
#define MENU_TITLE_LINE_5 "|____/ \\_/\\_/ \\__,_|_|_|\\___/ \\_/\\_/   |____/ \\__\\__,_|_|  |___/"

#define RANKING_FILE "ranking.txt"

#define GAME_OVER_LINE_1 "  ________   __  _______  ____ _   _________ "
#define GAME_OVER_LINE_2 " / ___/ _ | /  |/  / __/ / __ \\ | / / __/ _ \\"
#define GAME_OVER_LINE_3 "/ (_ / __ |/ /|_/ / _/  / /_/ / |/ / _// , _/"
#define GAME_OVER_LINE_4 "\\___/_/ |_/_/  /_/___/  \\____/|___/___/_/|_| "
