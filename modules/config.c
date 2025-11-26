#include "../headers/config.h"

// int Star_Quota = 10;
// int Time_Limit = 120;
// float Spawn_Rate;
// char Player_Sprite = '^';
// int Player_Initial_Speed;
// int Player_Min_Speed;
// int Player_Max_Speed;
// int Player_Life_Force;
// char *Player_Name;
// char *Level_Name;
// int Game_Height = 10;
// int Game_Width = 50;

void trim(char *string) {
	int count = 0;
	while (string[count] == ' ' || string[count] == '\t') {
		count++;
	}

	int i = 0;
	while (string[i + count] != ' ' && string[i + count] != '\t' && string[i + count] != '#' && string[i + count] != '\0') {
		string[i] = string[i + count];
		i++;
	}

	string[i] = '\0';
}

void load_to_globals(CONFIG *config, char *option, char *value, bool is_for_player, bool is_for_hunter) {
	if (is_for_player) {
		// if (config->player == NULL) {
		// 	config->player = (PLAYER *) malloc(sizeof(PLAYER));
		// }
		if (!strcmp(option, "initial_speed")) {
			config->player->initial_speed = atoi(value);
		} else if (!strcmp(option, "min_speed")) {
			config->player->min_speed = atoi(value);
		} else if (!strcmp(option, "max_speed")) {
			config->player->max_speed = atoi(value);
		} else if (!strcmp(option, "life_force")) {
			config->player->life_force = atoi(value);
		} else if (!strcmp(option, "name")) {
			strcpy(config->player->name, value);
		}
	}
	else if (is_for_hunter) {
		// TODO: implement hunter config
		printf("hunter config\n");
	}
	else {
		if (!strcmp(option, "star_quota")) {
			config->star_quota = atoi(value);
		} else if (!strcmp(option, "time_limit")) {
			config->time_limit = atoi(value);
		} else if (!strcmp(option, "spawn_rate")) {
			config->spawn_rate = atof(value);
		} else if (!strcmp(option, "game_height")) {
			config->game_height = atoi(value);
		} else if (!strcmp(option, "game_width")) {
			config->game_width = atoi(value);
		} else if (!strcmp(option, "level_name")) {
			strcpy(config->level_name, value);
		}
	}
}

void parse_line(CONFIG *config, char *line, bool is_for_player, bool is_for_hunter) {
	char *option;
	char *value;

	if (strchr(line, '=')) {
		option = strtok(line, "=");
		value = strtok(NULL, "=");

		trim(option);
		trim(value);

		load_to_globals(config, option, value, is_for_player, is_for_hunter);
	}
}

CONFIG *get_config(void) {
	char *file = "game.conf";

	static CONFIG *config = NULL;

	if (config == NULL) {
		config = (CONFIG *) malloc(sizeof(CONFIG));
		FILE *config_file = fopen(file, "r");

		load_to_globals(config, "level_name", file, false, false);

		if (!config_file) {
			printf("Error: Could not open config file\n");
			exit(EXIT_FAILURE);
		}

		char line[256];
		bool is_for_player = false;
		bool is_for_hunter = false;

		while (fgets(line, sizeof(line), config_file)) {

			// TODO: this makes parsing stop, change to continue after implementing the rest
			if (line[0] == '#' || line[0] == '\0') { // TODO: change \0 to \n
				// continue;
				break;
			}

			if (line[0] == '}') {
				is_for_player = false;
				is_for_hunter = false;
				continue;
			}

			if (strchr(line, '{')) {
				if (strstr(line, "player")) {
					is_for_player = true;
				}

				// TODO: implement hunter config
			}

			parse_line(config, line, is_for_player, is_for_hunter);
		}

		fclose(config_file);
	}

	return config;
}
