#include "../headers/config.h"

void load_to_config(CONFIG *config, const char *option, const char *value, const bool is_for_player, const bool is_for_hunter) {
	if (is_for_player) {
		// if (config->player == NULL) {
		// 	config->player = (PLAYER_CONFIG *) malloc(sizeof(PLAYER_CONFIG));
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
		} else if (!strcmp(option, "hunter_spawn_rate")) {
			config->hunter_spawn_rate = atof(value);
		} else if (!strcmp(option, "star_spawn_rate")) {
			config->star_spawn_rate = atof(value);
		} else if (!strcmp(option, "game_height")) {
			config->game_height = atoi(value);
		} else if (!strcmp(option, "game_width")) {
			config->game_width = atoi(value);
		} else if (!strcmp(option, "level_name")) {
			strcpy(config->level_name, value);
		}
	}
}

void parse_line(CONFIG *config, char *line, const bool is_for_player, const bool is_for_hunter) {
	char *option;
	char *value;

	if (strchr(line, '=')) {
		option = strtok(line, "=");
		value = strtok(NULL, "=");

		trim(option);
		trim(value);

		load_to_config(config, option, value, is_for_player, is_for_hunter);
	}
}

CONFIG *init_config(char *file) {
	CONFIG *config = (CONFIG *) malloc(sizeof(CONFIG));
	FILE *config_file = fopen(file, "r");

	load_to_config(config, "level_name", file, false, false);

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

	return config;
}

const CONFIG *get_config(void) {
	char *file = "game.conf";

	static CONFIG *config = NULL;

	if (config == NULL) {
		config = init_config(file);
	}

	return config;
}
