#include "game.h"
#include "nokia5110.h"

enum map_info {
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
	MAX_DIRECTION,
};

struct room_info {
	char *text;
};

struct game_info {
	struct room_info room[MAP_WIDTH][MAP_HEIGHT];
} game;

struct player_info {
	byte xloc;
	byte yloc;
} player;

static enum directions direction_choice;

/* Set up the rooms in the game map */
static void setup_game(void) {
	game.room[0][0].text = "Northwest room.";
	game.room[1][0].text = "North room.";
	game.room[2][0].text = "Northeast room.";
	game.room[0][1].text = "West room.";
	game.room[1][1].text = "Middle room.";
	game.room[2][1].text = "East room.";
	game.room[0][2].text = "Southwest room.";
	game.room[1][2].text = "South room.";
	game.room[2][2].text = "Southeast room.";

	player.xloc = 1;
	player.yloc = 1;
}

/* Show the available direction choices */
static void show_directions(void) {
	lcd_write("North", NORTH_X, NORTH_Y);
	lcd_write("East", EAST_X, EAST_Y);
	lcd_write("South", SOUTH_X, SOUTH_Y);
	lcd_write("West", WEST_X, WEST_Y);
}

/* Draw the cursor at the current direction choice */
static void curs_dir_choice(void) {
	lcd_write(" ", CURS_NORTH_X, CURS_NORTH_Y);
	lcd_write(" ", CURS_WEST_X, CURS_WEST_Y);
	lcd_write(" ", CURS_EAST_X, CURS_EAST_Y);
	lcd_write(" ", CURS_SOUTH_X, CURS_SOUTH_Y);

	switch (direction_choice) {
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
	direction_choice = NORTH;
	curs_dir_choice();
}

/* Display text for the current room */
static void show_room_text(void) {
	lcd_clear();
	game_text_anim(game.room[player.xloc][player.yloc].text);
	delay(2000);
}

/* The player cannot move in the current chosen direction */
static void bad_choice(void) {
	lcd_clear();
	game_text("You can't go that way.");
	delay(2000);
}

/* Intro for the game */
void game_intro(void) {
	lcd_clear();
	game_text("Welcome to SlimQuest");
	lcd_write(">Start", 20, 4);

	delay(2000);	///DEBUG (in place of button press)

	setup_game();

	lcd_clear();
	game_text_anim("Here's some basic story plot. Exciting, isn't it?!");
	delay(2000);

	show_room_text();
	travel_screen();
}

/* Move the cursor to the next direction option */
void next_dir_choice(void) {
	direction_choice = (direction_choice + 1) % MAX_DIRECTION;
	curs_dir_choice();
}

/* Walk in the direction of the current choice and display the new room's text */
void travel(void) {
	boolean valid = true;

	switch (direction_choice) {
	case NORTH:
		if (player.yloc == 0) {
			valid = false;
			break;
		}
		player.yloc--;
		break;
	case EAST:
		if (player.xloc >= MAP_WIDTH - 1) {
			valid = false;
			break;
		}
		player.xloc++;
		break;
	case SOUTH:
		if (player.yloc >= MAP_HEIGHT - 1) {
			valid = false;
			break;
		}
		player.yloc++;
		break;
	case WEST:
		if (player.xloc == 0) {
			valid = false;
			break;
		}
		player.xloc--;
		break;
	}

	if (valid) {
		show_room_text();
	} else {
		bad_choice();
	}

	travel_screen();
}
