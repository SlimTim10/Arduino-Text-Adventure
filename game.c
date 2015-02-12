#include "game.h"
#include "nokia5110.h"

enum game_info {
	MAP_WIDTH = 3,
	MAP_HEIGHT = 3,
};

enum text_loc {
	NORTH_X = 30,
	NORTH_Y = 3,
	WEST_X = 6,
	WEST_Y = 4,
	EAST_X = 60,
	EAST_Y = 4,
	SOUTH_X = 30,
	SOUTH_Y = 5,
};

enum curs_loc {
	CURS_NORTH_X = NORTH_X - 6,
	CURS_NORTH_Y = NORTH_Y,
	CURS_WEST_X = WEST_X - 6,
	CURS_WEST_Y = WEST_Y,
	CURS_EAST_X = EAST_X - 6,
	CURS_EAST_Y = EAST_Y,
	CURS_SOUTH_X = SOUTH_X - 6,
	CURS_SOUTH_Y = SOUTH_Y,
};

enum curs_choice {
	CURS_NORTH,
	CURS_WEST,
	CURS_EAST,
	CURS_SOUTH,
};

struct game_map {
	byte xloc;
	byte yloc;
	char *text[MAP_WIDTH][MAP_HEIGHT];
} gm;

/* Set up the rooms in the game map */
static void setup_map(void) {
	gm.xloc = 1;
	gm.yloc = 1;
	gm.text[0][0] = "";
	gm.text[1][0] = "North room.";
	gm.text[2][0] = "";
	gm.text[0][1] = "West room.";
	gm.text[1][1] = "Middle room.";
	gm.text[2][1] = "East room.";
	gm.text[0][2] = "";
	gm.text[1][2] = "South room.";
	gm.text[2][2] = "";
}

/* Show the available walking choices */
static void show_walk_choice(void) {
	lcd_write("North", NORTH_X, NORTH_Y);
	lcd_write("West", WEST_X, WEST_Y);
	lcd_write("East", EAST_X, EAST_Y);
	lcd_write("South", SOUTH_X, SOUTH_Y);
}

/* Draw the cursor at the current walking choice */
static void curs_walk_choice(enum curs_choice choice) {
	lcd_write(" ", CURS_NORTH_X, CURS_NORTH_Y);
	lcd_write(" ", CURS_WEST_X, CURS_WEST_Y);
	lcd_write(" ", CURS_EAST_X, CURS_EAST_Y);
	lcd_write(" ", CURS_SOUTH_X, CURS_SOUTH_Y);

	switch (choice) {
	case CURS_NORTH:
		lcd_write(">", CURS_NORTH_X, CURS_NORTH_Y);
		break;
	case CURS_WEST:
		lcd_write(">", CURS_WEST_X, CURS_WEST_Y);
		break;
	case CURS_EAST:
		lcd_write(">", CURS_EAST_X, CURS_EAST_Y);
		break;
	case CURS_SOUTH:
		lcd_write(">", CURS_SOUTH_X, CURS_SOUTH_Y);
		break;
	}
}

/* Display text on the screen starting from the top */
static void game_text(char const *str) {
	lcd_write_wrap(str, 0, 0);
}

/* Display text on the screen starting from the top, with writing animation */
static void game_text_anim(char const *str) {
	lcd_write_wrap_anim(str, 0, 0);
}

static void display_walk_choice(void) {
	lcd_clear();
	game_text("Where do you want to walk?");
	show_walk_choice();
	curs_walk_choice(CURS_NORTH);
}

/* Display text for the current room */
void game_room_text(void) {
	lcd_clear();
	game_text_anim(gm.text[gm.xloc][gm.yloc]);
	delay(2000);
}

/* Intro for the game */
void game_intro(void) {
	lcd_clear();
	game_text("Welcome to SlimQuest");
	lcd_write(">Start", 20, 4);

	delay(2000);	///DEBUG (in place of button press)

	setup_map();

	lcd_clear();
	game_text_anim("Here's some basic story plot. Exciting, isn't it?!");
	delay(2000);

	game_room_text();
	display_walk_choice();
}
