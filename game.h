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

struct player {
	uint8_t xloc;				/* Current X location */
	uint8_t yloc;				/* Current Y location */
	uint8_t prev_xloc;			/* Previous X location */
	uint8_t prev_yloc;			/* Previous Y location */
	boolean run;				/* Currently running from enemy */
	int8_t hp;					/* Hit points */
	uint8_t lvl;				/* Level */
};

struct enemy {
	int8_t hp;
	uint8_t lvl;
	char *name;
};

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
