#include "../headers/utils.h"

int get_random(int min, int max) {
	int random_value;

	FILE *dev_urandom = fopen("/dev/urandom", "rb");

	// NOTE: if dev_urandom is not available using srand(time(NULL)) might be neccessary
	if (dev_urandom == NULL) {
		printf("Error opening /dev/urandom\n");
		return -1;
	}

	if (fread(&random_value, sizeof(char), 1, dev_urandom) != 1) {
		printf("Error reading from /dev/urandom\n");
		return -1;
	}
		
	fclose(dev_urandom);

	return min + random_value % (max+1 - min);
}

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

float calc_distance(const float delta_y, const float delta_x) {
	return sqrt(pow(delta_y, 2) + pow(delta_x, 2));
}
