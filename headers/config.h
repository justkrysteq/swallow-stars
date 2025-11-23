#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// SECTION: GAME GLOBALS

// **Number of stars required to win**
extern int Star_Quota;
// **Time (in seconds) left to collect stars**
extern int Time_Limit;
// **Hunter spawn rate per second**
extern float Spawn_Rate;
// **Game window height**
extern int Game_Height;
// **Game window width**
extern int Game_Width;
// **Name of the level**
extern char *Level_Name;

// SECTION: PLAYER GLOBALS

extern char Player_Sprite;
extern int Player_Initial_Speed;
extern int Player_Min_Speed;
extern int Player_Max_Speed;
extern int Player_Life_Force;
extern char *Player_Name;


// SECTION: CONFIG FILE PARSING

/**
 * **Trims a string**
 *
 * By removing all spaces and tabs from the beginning
 * If the string contains a space, tab, # or newline, everything after it will be removed
 *
 * *Parameters:*
 * - **string**: *string to be trimmed*
 */
void trim(char *string);

/**
 * **Updates a global variable with value provided**
 *
 * *Parameters:*
 * - **option**: *name of the global variable*
 * - **value**: *new value*
 * - **is_for_player**: *whether or not this is a player variable*
 * - **is_for_hunter**: *whether or not this is a hunter variable*
 */
void load_to_globals(char *option, char *value, bool is_for_player, bool is_for_hunter);

/**
 * **Splits a line into option and value and updates globals**
 *
 * If the line contains '=' character, the line will be split into option and value
 * If the line does not contain '=' character, the line will be ignored
 *
 * *Parameters:*
 * - **line**: *line to be parsed*
 * - **is_for_player**: *whether or not this line is for player config*
 * - **is_for_hunter**: *whether or not this line is for hunter config*
 */
void parse_line(char *line, bool is_for_player, bool is_for_hunter);

/**
 * **Updates global variables with values from provided file**
 *
 * *Parameters:*
 * - **file**: *name of the config file*
 */
void get_config(char *file);
