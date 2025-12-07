#include "../headers/config.h"

void load_player_to_config(CONFIG *config, const char *option, const char *value) {
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

void load_hunter_to_config(CONFIG *config, const char *option, const char *value, const unsigned int hunter_count) {
	if (!strcmp(option, "shape")) {
		strcpy(config->hunters[hunter_count].shape, value);
		config->hunters[hunter_count].shape[3] = '\0';
	} else if (!strcmp(option, "speed")) {
		config->hunters[hunter_count].speed = atof(value);
	} else if (!strcmp(option, "damage")) {
		config->hunters[hunter_count].damage = atoi(value);
	} else if (!strcmp(option, "initial_bounces")) {
		config->hunters[hunter_count].initial_bounces = atoi(value);
	} else if (!strcmp(option, "spawn_chance")) {
		config->hunters[hunter_count].spawn_chance = atof(value);
	}
}

void load_score_to_config(CONFIG *config, const char *option, const char *value) {
	if (!strcmp(option, "score_life_multiplier")) {
		config->score_life_multiplier = atof(value);
	} else if (!strcmp(option, "score_star_multiplier")) {
		config->score_star_multiplier = atof(value);
	} else if (!strcmp(option, "score_time_multiplier")) {
		config->score_time_multiplier = atof(value);
	} else if (!strcmp(option, "score_difficulty_multiplier")) {
		config->score_difficulty_multiplier = atof(value);
	}
}

void load_global_to_config(CONFIG *config, const char *option, const char *value) {
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
	} else if (!strcmp(option, "hunter_spawn_rate_escalation")) {
		config->hunter_spawn_rate_escalation = atof(value);
	} else if (!strcmp(option, "hunter_initial_bounces_escalation")) {
		config->hunter_initial_bounces_escalation = atof(value);
	} else {
		load_score_to_config(config, option, value);
	}
}

void load_to_config(CONFIG *config, const char *option, const char *value, const bool is_for_player, const bool is_for_hunter, const unsigned int hunter_count) {
	if (is_for_player) {
		load_player_to_config(config, option, value);
	} else if (is_for_hunter) {
		load_hunter_to_config(config, option, value, hunter_count);
	} else {
		load_global_to_config(config, option, value);
	}
}

void parse_line(CONFIG *config, char *line, const bool is_for_player, const bool is_for_hunter, const unsigned int hunter_count) {
	char *option = NULL;
	char *value = NULL;

	if (strchr(line, '=')) {
		option = strtok(line, "=");
		value = strtok(NULL, "=");

		trim(option);
		trim(value);

		load_to_config(config, option, value, is_for_player, is_for_hunter, hunter_count);
	}
}

CONFIG *init_config(char *file) {
	CONFIG *config = (CONFIG *) malloc(sizeof(CONFIG));
	FILE *config_file = fopen(file, "r");

	char line[256];
	bool is_for_player = false;
	bool is_for_hunter = false;
	unsigned int hunter_count = 0;
	load_to_config(config, "level_name", file, false, false, hunter_count);

	if (!config_file) {
		printf("Error: Could not open config file:\n");
		printf("%s\n", file);
		exit(EXIT_FAILURE);
	}

	while (fgets(line, sizeof(line), config_file)) {
		if (line[0] == '#' || line[0] == '\n' || line[1] == '#') {
			continue;
		}

		if (line[0] == '}') {
			if (is_for_hunter) {
				hunter_count++;
			}

			is_for_player = false;
			is_for_hunter = false;

			continue;
		}

		if (strchr(line, '{')) {
			if (strstr(line, "player")) {
				is_for_player = true;
			}

			if (strstr(line, "hunter")) {
				is_for_hunter = true;
			}
		}

		parse_line(config, line, is_for_player, is_for_hunter, hunter_count);
	}

	fclose(config_file);

	config->hunter_count = hunter_count;

	return config;
}

const CONFIG *get_config(void) {
	static CONFIG *config = NULL;

	if (config == NULL) {
		char file[20] = "level ?.conf";
		int *level = get_selected_level();

		if (level == NULL) {
			level = 0;
		}

		file[6] = *level + '0';
		if (fopen(file, "r") == NULL) {
			strcpy(file, DEFAULT_LEVEL);
			// file = DEFAULT_LEVEL;
		}

		config = init_config(file);
		free(level);
	}

	return config;
}
