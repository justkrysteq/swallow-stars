#include "../headers/config.h"

int Star_Quota = 10;
int Time_Limit = 120;
float Spawn_Rate;
char Player_Sprite = '^';
int Player_Initial_Speed;
int Player_Min_Speed;
int Player_Max_Speed;
int Player_Life_Force;
char *Player_Name;
char *Level_Name;
int Game_Height = 10;
int Game_Width = 50;

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

void load_to_globals(char *option, char *value, bool is_for_player, bool is_for_hunter) {
	if (is_for_player) {
		if (!strcmp(option, "initial_speed")) {
			Player_Initial_Speed = atoi(value);
		} else if (!strcmp(option, "min_speed")) {
			Player_Min_Speed = atoi(value);
		} else if (!strcmp(option, "max_speed")) {
			Player_Max_Speed = atoi(value);
		} else if (!strcmp(option, "life_force")) {
			Player_Life_Force = atoi(value);
		} else if (!strcmp(option, "name")) {
			// strcpy(Player_Name, value);
			Player_Name = value;
		}
	}
	else if (is_for_hunter) {
		// TODO: implement hunter config
		printf("hunter config\n");
	}
	else {
		if (!strcmp(option, "star_quota")) {
			Star_Quota = atoi(value);
		} else if (!strcmp(option, "time_limit")) {
			Time_Limit = atoi(value);
		} else if (!strcmp(option, "spawn_rate")) {
			Spawn_Rate = atof(value);
		} else if (!strcmp(option, "game_height")) {
			Game_Height = atoi(value);
		} else if (!strcmp(option, "game_width")) {
			Game_Width = atoi(value);
		}
	}
}

void parse_line(char *line, bool is_for_player, bool is_for_hunter) {
	char *option;
	char *value;

	if (strchr(line, '=')) {
		option = strtok(line, "=");
		value = strtok(NULL, "=");

		trim(option);
		trim(value);

		load_to_globals(option, value, is_for_player, is_for_hunter);
	}
}

void get_config(char *file) {
	FILE *config_file = fopen(file, "r");

	Level_Name = file;

	if (!config_file) {
		printf("Error: Could not open config file\n");
		exit(EXIT_FAILURE);
	}

	char line[256];
	bool is_for_player = false;
	bool is_for_hunter = false;

	// while (fscanf(config_file, "%m[^\n]\n", &line) != EOF) { // %m means match everything until the first = and \n and EOF means End Of File
	while (fgets(line, sizeof(line), config_file)) { // %m means match everything until the first = and \n and EOF means End Of File

		// TODO: this makes parsing stop, change to continue after implementing the rest
		if (line[0] == '#' || line[0] == '\0') {
			// continue;
			break;
		}

		if (line[0] == '}') {
			is_for_player = false;
			continue;
		}

		if (strchr(line, '{')) {
			if (strstr(line, "player")) {
				is_for_player = true;
			}

			// TODO: implement hunter config
		}

		parse_line(line, is_for_player, is_for_hunter);
	}

	fclose(config_file);
}
