#ifndef GAME_H
#define GAME_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

enum game_constants {
	MAP_WIDTH = 4,
	MAP_HEIGHT = 4,
	MAX_ENEMIES_PER_ROOM = 3,
	MAX_HP = 100,
	MAX_LVL = 10,
	XP_NEXT_INC = 20,			/* XP to next level increase */
	XP_GAIN = 10,				/* Multiply enemy level by this for player XP gain */
};

struct player {
	uint8_t xloc;				/* Current X location */
	uint8_t yloc;				/* Current Y location */
	uint8_t prev_xloc;			/* Previous X location */
	uint8_t prev_yloc;			/* Previous Y location */
	boolean run;				/* Currently running from enemy */
	int8_t hp;					/* Hit points */
	uint8_t lvl;				/* Level */
	uint16_t xp;					/* Experience */
	uint16_t xp_next_lvl;			/* Required experience to gain next level */
};

struct enemy {
	int8_t hp;
	uint8_t lvl;
	char *name;
};

void make_wall(uint8_t, uint8_t);
void add_enemy(uint8_t, uint8_t, char *, int8_t, uint8_t);
boolean is_player_dead(void);
void set_player_location(uint8_t, uint8_t);
void set_player_hp(int8_t);
void set_player_level(uint8_t);
void game_text(char const *);
void game_text_anim(char const *);
void setup_game(void);
void game_intro(void);
void next_dir_choice(void);
void travel(void);

#ifdef __cplusplus
}
#endif

#endif
