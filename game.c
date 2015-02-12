#include "game.h"
#include "nokia5110.h"

enum game_info {
	MAP_WIDTH = 3,
	MAP_HEIGHT = 3,
};

enum text_loc {
	NORTH_X = 30,
	NORTH_Y = 3,
	EAST_X = 60,
	EAST_Y = 4,
	SOUTH_X = 30,
	SOUTH_Y = 5,
	WEST_X = 6,
	WEST_Y = 4,
};

enum curs_loc {
	CURS_NORTH_X = NORTH_X - 6,
	CURS_NORTH_Y = NORTH_Y,
	CURS_EAST_X = EAST_X - 6,
	CURS_EAST_Y = EAST_Y,
	CURS_SOUTH_X = SOUTH_X - 6,
	CURS_SOUTH_Y = SOUTH_Y,
	CURS_WEST_X = WEST_X - 6,
	CURS_WEST_Y = WEST_Y,
};

enum directions {
	NORTH,
	EAST,
	SOUTH,
	WEST,
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

/* Show the available direction choices */
static void show_directions(void) {
	lcd_write("North", NORTH_X, NORTH_Y);
	lcd_write("East", EAST_X, EAST_Y);
	lcd_write("South", SOUTH_X, SOUTH_Y);
	lcd_write("West", WEST_X, WEST_Y);
}

/* Draw the cursor at the current direction choice */
static void curs_dir_choice(enum directions choice) {
	lcd_write(" ", CURS_NORTH_X, CURS_NORTH_Y);
	lcd_write(" ", CURS_WEST_X, CURS_WEST_Y);
	lcd_write(" ", CURS_EAST_X, CURS_EAST_Y);
	lcd_write(" ", CURS_SOUTH_X, CURS_SOUTH_Y);

	switch (choice) {
	case NORTH:
		lcd_write(">", CURS_NORTH_X, CURS_NORTH_Y);
		break;
	case EAST:
		lcd_write(">", CURS_EAST_X, CURS_EAST_Y);
		break;
	case SOUTH:
		lcd_write(">", CURS_SOUTH_X, CURS_SOUTH_Y);
		break;
	case WEST:
		lcd_write(">", CURS_WEST_X, CURS_WEST_Y);
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

/* Display message asking which direction to go and show options */
static void travel_screen(void) {
	lcd_clear();
	game_text("Where do you want to walk?");
	show_directions();
	curs_dir_choice(NORTH);
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

	show_room_text();
	travel_screen();
}

/* Display text for the current room */
void show_room_text(void) {
	lcd_clear();
	game_text_anim(gm.text[gm.xloc][gm.yloc]);
	delay(2000);
}
