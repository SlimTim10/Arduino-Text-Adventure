#ifndef RESOURCES_H
#define RESOURCES_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

extern char str_buffer[];

#define STR_TO_RAM(S)	(strcpy_P(str_buffer, S))

/* General */
extern const char STR_WELCOME[];
extern const char STR_START[];
extern const char STR_INTRO[];
extern const char STR_SPACE[];
extern const char STR_CURS[];
extern const char STR_WIN[];

/* Travel */
extern const char STR_STATUS[];
extern const char STR_NORTH[];
extern const char STR_EAST[];
extern const char STR_SOUTH[];
extern const char STR_WEST[];
extern const char STR_TRAVEL_SCREEN[];
extern const char STR_INVALID_TRAVEL[];

/* Map */
extern const char STR_ROOM_MAP[];
extern const char STR_ROOM_LOC[];
enum { STR_ROOM_TEXT_NUM = 20 };
extern PGM_P const STR_ROOM_TEXT[STR_ROOM_TEXT_NUM];

/* Battle */
extern const char STR_ENEMY[];
extern const char STR_ATTACK[];
extern const char STR_RUN[];
extern const char STR_PLAYER_HP[];
extern const char STR_ENEMY_HP[];
extern const char STR_ENEMY_MISS[];
extern const char STR_ENEMY_ATTACK[];
extern const char STR_PLAYER_MISS[];
extern const char STR_PLAYER_ATTACK[];
extern const char STR_CANT_ESCAPE[];
extern const char STR_ESCAPE[];
extern const char STR_BATTLE_WIN[];
extern const char STR_XP_GAIN[];
extern const char STR_LVL_GAIN[];
extern const char STR_LVL[];
extern const char STR_HP[];
extern const char STR_XP[];
extern const char STR_NEXT[];
extern const char STR_PLAYER_DEATH[];
extern const char STR_OK[];

#ifdef __cplusplus
}
#endif

#endif
