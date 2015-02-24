#include "resources.h"

typedef const PROGMEM char RSRC;

/* General */
RSRC STR_WELCOME[] = "Welcome to SlimQuest";
RSRC STR_START[] = ">Start";
RSRC STR_INTRO[] = "You wake up in a dungeon.";
RSRC STR_SPACE[] = " ";
RSRC STR_CURS[] = ">";

/* Travel */
RSRC STR_NORTH[] = "North";
RSRC STR_EAST[] = "East";
RSRC STR_SOUTH[] = "South";
RSRC STR_WEST[] = "West";
RSRC STR_TRAVEL_SCREEN[] = "Where do you want to walk?";
RSRC STR_INVALID_TRAVEL[] = "You can't go that way.";

/* Map */
RSRC STR_ROOM_00[] = "Room [0,0].";
RSRC STR_ROOM_10[] = "Room [1,0].";
RSRC STR_ROOM_20[] = "Room [2,0].";
RSRC STR_ROOM_30[] = "Room [3,0].";
RSRC STR_ROOM_01[] = "Room [0,1].";
RSRC STR_ROOM_11[] = "Room [1,1].";
RSRC STR_ROOM_21[] = "Room [2,1].";
RSRC STR_ROOM_31[] = "Room [3,1].";
RSRC STR_ROOM_02[] = "Room [0,2].";
RSRC STR_ROOM_12[] = "Room [1,2].";
RSRC STR_ROOM_22[] = "Room [2,2].";
RSRC STR_ROOM_32[] = "Room [3,2].";
RSRC STR_ROOM_03[] = "Room [0,3].";
RSRC STR_ROOM_13[] = "Room [1,3].";
RSRC STR_ROOM_23[] = "Room [2,3].";
RSRC STR_ROOM_33[] = "Room [3,3].";

/* Battle */
RSRC STR_ENEMY[] = "There's an angry level %d %s!";
RSRC STR_ATTACK[] = "Attack";
RSRC STR_RUN[] = "Run";
RSRC STR_PLAYER_HP[] = "You: %dHP";
RSRC STR_ENEMY_HP[] = "%s: %dHP";
RSRC STR_ENEMY_MISS[] = "The %s misses!";
RSRC STR_ENEMY_ATTACK[] = "The %s attacks for %d damage!";
RSRC STR_PLAYER_MISS[] = "Your attack misses...";
RSRC STR_PLAYER_ATTACK[] = "You attack viciously for %d damage!";
RSRC STR_CANT_ESCAPE[] = "Can't escape!";
RSRC STR_ESCAPE[] = "Got away safely!";
RSRC STR_BATTLE_WIN[] = "You defeated the %s!";
RSRC STR_XP_GAIN[] = "You gained %dXP!";
RSRC STR_LVL_GAIN[] = "You gained a level! You feel stronger...";
RSRC STR_LVL[] = "Level: %d";
RSRC STR_HP[] = "HP: %d";
RSRC STR_XP[] = "XP: %d";
RSRC STR_NEXT[] = "Next: %dXP";
RSRC STR_PLAYER_DEATH[] = "You died.";
