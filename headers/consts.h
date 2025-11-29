#pragma once

// ---- CONTROL KEYS ----
#define QUIT 'q'
#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_LEFT 'a'
#define MOVE_RIGHT 'd'
#define INCREASE_SPEED 'p'
#define DECREASE_SPEED 'o'

#define UP_DIRECTION -1
#define DOWN_DIRECTION 1
#define LEFT_DIRECTION -1
#define RIGHT_DIRECTION 1

#define PLAYER_SPRITE_UP '^'
#define PLAYER_SPRITE_DOWN 'v'
#define PLAYER_SPRITE_LEFT '<'
#define PLAYER_SPRITE_RIGHT '>'

#define FRAMES_PER_SECOND 200
#define SPEED_FACTOR (1000/(FRAMES_PER_SECOND*50.0))

#define BORDER_SIZE 1
#define MAX_STARS 25
