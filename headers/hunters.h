#include "bird.h"
#include "consts.h"

typedef struct {
	float y, x, dir_y, dir_x;
	int dest_y, dest_x;
	unsigned int speed, damage;
	int bounces;
	unsigned int height, width;
	bool exists, is_dashing, is_waiting, in_bounce_state;
	WIN *parent_window;
} HUNTER;

HUNTER init_hunter(WIN *parent_window);

HUNTER *create_hunter_table(WIN *parent_window);

void spawn_hunter(HUNTER *hunters, const BIRD *bird, const float hunter_initial_bounces_escalation);

void handle_hunter_spawn(HUNTER *hunter, const BIRD *bird, const float initial_bounces_escalation, const int hunter_template_id);

void draw_hunter(const HUNTER hunter);

void move_hunter(HUNTER *hunter, const BIRD *bird);

void handle_hunter_movement(HUNTER *hunter, const BIRD *bird, int *function_calls);

void handle_hunter_bounce(HUNTER *hunter);

void hunter_bounce_back(HUNTER *hunter);
