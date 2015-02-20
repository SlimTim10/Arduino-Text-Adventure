#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

enum game_constants {
	MAP_WIDTH = 3,
	MAP_HEIGHT = 3,
	MAX_ENEMIES_PER_ROOM = 3,
};

struct player_info {
	uint8_t xloc;
	uint8_t yloc;
	int8_t hp;
};

extern struct player_info player;

void game_text(char const *str);
void game_text_anim(char const *str);
void setup_game(void);
void game_intro(void);
void next_dir_choice(void);
void travel(void);

#ifdef __cplusplus
}
#endif

#endif
