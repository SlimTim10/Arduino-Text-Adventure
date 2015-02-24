#include "resources.h"
#include "nokia5110.h"

typedef const char RSRC;

char str_buffer[LCD_MAX_TEXT];

/* General */
RSRC STR_WELCOME[] PROGMEM = "Welcome to IcewireQuest";
RSRC STR_START[] PROGMEM = ">Start";
RSRC STR_INTRO[] PROGMEM = "You wake up in a dungeon.";
RSRC STR_SPACE[] PROGMEM = " ";
RSRC STR_CURS[] PROGMEM = ">";

/* Travel */
RSRC STR_NORTH[] PROGMEM = "North";
RSRC STR_EAST[] PROGMEM = "East";
RSRC STR_SOUTH[] PROGMEM = "South";
RSRC STR_WEST[] PROGMEM = "West";
RSRC STR_TRAVEL_SCREEN[] PROGMEM = "Where do you want to walk?";
RSRC STR_INVALID_TRAVEL[] PROGMEM = "You can't go that way.";

/* Map */
RSRC STR_ROOM_LOC[] PROGMEM = "[%d,%d]";
RSRC STR_ROOM_TEXT00[] PROGMEM = "There's a strange smell.";
RSRC STR_ROOM_TEXT01[] PROGMEM = "It's hard to breathe in here.";
RSRC STR_ROOM_TEXT02[] PROGMEM = "It's cold in here.";
RSRC STR_ROOM_TEXT03[] PROGMEM = "You feel scared.";
RSRC STR_ROOM_TEXT04[] PROGMEM = "It is very dark.";
RSRC STR_ROOM_TEXT05[] PROGMEM = "It's wet in here.";
RSRC STR_ROOM_TEXT06[] PROGMEM = "There's an odd green glow.";
RSRC STR_ROOM_TEXT07[] PROGMEM = "There's a strange sound.";
RSRC STR_ROOM_TEXT08[] PROGMEM = "You feel something watching you.";
RSRC STR_ROOM_TEXT09[] PROGMEM = "You hear water.";
RSRC STR_ROOM_TEXT10[] PROGMEM = "You hear footsteps.";
RSRC STR_ROOM_TEXT11[] PROGMEM = "You feel alone.";
RSRC STR_ROOM_TEXT12[] PROGMEM = "You feel invigorated.";
RSRC STR_ROOM_TEXT13[] PROGMEM = "Where's the way out?";
RSRC STR_ROOM_TEXT14[] PROGMEM = "A mouse runs by your feet.";
RSRC STR_ROOM_TEXT15[] PROGMEM = "There's a loud crash.";
RSRC STR_ROOM_TEXT16[] PROGMEM = "You hear laughter in the distance.";
RSRC STR_ROOM_TEXT17[] PROGMEM = "You hear chains clanging.";
RSRC STR_ROOM_TEXT18[] PROGMEM = "The wind is moaning.";
RSRC STR_ROOM_TEXT19[] PROGMEM = "You've lost your way.";
RSRC  *STR_ROOM_TEXT[STR_ROOM_TEXT_NUM] PROGMEM = {
	STR_ROOM_TEXT00,
	STR_ROOM_TEXT01,
	STR_ROOM_TEXT02,
	STR_ROOM_TEXT03,
	STR_ROOM_TEXT04,
	STR_ROOM_TEXT05,
	STR_ROOM_TEXT06,
	STR_ROOM_TEXT07,
	STR_ROOM_TEXT08,
	STR_ROOM_TEXT09,
	STR_ROOM_TEXT10,
	STR_ROOM_TEXT11,
	STR_ROOM_TEXT12,
	STR_ROOM_TEXT13,
	STR_ROOM_TEXT14,
	STR_ROOM_TEXT15,
	STR_ROOM_TEXT16,
	STR_ROOM_TEXT17,
	STR_ROOM_TEXT18,
	STR_ROOM_TEXT19,
};

/* Battle */
RSRC STR_ENEMY[] PROGMEM = "There's an angry level %d %s!";
RSRC STR_ATTACK[] PROGMEM = "Attack";
RSRC STR_RUN[] PROGMEM = "Run";
RSRC STR_PLAYER_HP[] PROGMEM = "You: %dHP";
RSRC STR_ENEMY_HP[] PROGMEM = "%s: %dHP";
RSRC STR_ENEMY_MISS[] PROGMEM = "The %s misses!";
RSRC STR_ENEMY_ATTACK[] PROGMEM = "The %s attacks for %d damage!";
RSRC STR_PLAYER_MISS[] PROGMEM = "Your attack misses...";
RSRC STR_PLAYER_ATTACK[] PROGMEM = "You attack viciously for %d damage!";
RSRC STR_CANT_ESCAPE[] PROGMEM = "Can't escape!";
RSRC STR_ESCAPE[] PROGMEM = "Got away safely!";
RSRC STR_BATTLE_WIN[] PROGMEM = "You defeated the %s!";
RSRC STR_XP_GAIN[] PROGMEM = "You gained %dXP!";
RSRC STR_LVL_GAIN[] PROGMEM = "You gained a level! You feel stronger...";
RSRC STR_LVL[] PROGMEM = "Level: %d";
RSRC STR_HP[] PROGMEM = "HP: %d";
RSRC STR_XP[] PROGMEM = "XP: %d";
RSRC STR_NEXT[] PROGMEM = "Next: %dXP";
RSRC STR_PLAYER_DEATH[] PROGMEM = "You died.";
