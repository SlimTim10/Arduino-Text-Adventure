#include "game.h"
#include "const.h"
#include "nokia5110.h"
#include "control.h"
#include "battle.h"

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

enum direction_choices {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	MAX_DIRECTION_CHOICE,
};

struct player player;

struct room {
	char *text;
	struct enemy enemies[MAX_ENEMIES_PER_ROOM];
};

struct game {
	struct room room[MAP_WIDTH][MAP_HEIGHT];
} game;

static enum direction_choices direction_choice;

/* Show the available direction choices */
static void show_dir_choices(void) {
	lcd_write("North", NORTH_X, NORTH_Y);
	lcd_write("East", EAST_X, EAST_Y);
	lcd_write("South", SOUTH_X, SOUTH_Y);
	lcd_write("West", WEST_X, WEST_Y);
}

/* Draw the cursor at the current direction choice */
static void curs_dir_choice(void) {
	lcd_write(" ", CURS_NORTH_X, CURS_NORTH_Y);
	lcd_write(" ", CURS_EAST_X, CURS_EAST_Y);
	lcd_write(" ", CURS_SOUTH_X, CURS_SOUTH_Y);
	lcd_write(" ", CURS_WEST_X, CURS_WEST_Y);

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

/* Display message asking which direction to go and show options */
static void travel_screen(void) {
	game_text("Where do you want to walk?");
	show_dir_choices();
	direction_choice = NORTH;
	curs_dir_choice();
}

/* Display text for the current room */
static void show_room_text(void) {
	game_text_anim(game.room[player.xloc][player.yloc].text);
	delay(TEXT_DELAY);
}

/* The player cannot move in the current chosen direction */
static void invalid_travel(void) {
	game_text("You can't go that way.");
	delay(TEXT_DELAY);
}

/* Display text on the screen starting from the top */
void game_text(char const *str) {
	lcd_clear();
	lcd_write_wrap(str, 0, 0);
}

/* Display text on the screen starting from the top, with writing animation */
void game_text_anim(char const *str) {
	lcd_clear();
	lcd_write_wrap_anim(str, 0, 0);
}



/* Initialize the game settings */
void setup_game(void) {
	game.room[0][0].text = "Northwest room.";
	game.room[1][0].text = "North room.";
	game.room[2][0].text = "Northeast room.";
	game.room[0][1].text = "West room.";
	game.room[1][1].text = "Middle room.";
	game.room[2][1].text = "East room.";
	game.room[0][2].text = "Southwest room.";
	game.room[1][2].text = "South room.";
	game.room[2][2].text = "Southeast room.";

	game.room[2][1].enemies[0].name = "rat";
	game.room[2][1].enemies[0].hp = 3;
	game.room[2][1].enemies[0].lvl = 1;

	player.xloc = 1;
	player.yloc = 1;
	player.hp = 100;
	player.lvl = 1;
}

/* Intro for the game */
void game_intro(void) {
	game_text("Welcome to SlimQuest");
	lcd_write(">Start", 20, 4);

	while (get_user_input() != B_SELECT);

	srand(millis());

	game_text_anim("You are in a dungeon.");
	delay(TEXT_DELAY);

	show_room_text();
	travel_screen();
}

/* Move the cursor to the next direction option */
void next_dir_choice(void) {
	direction_choice = (direction_choice + 1) % MAX_DIRECTION_CHOICE;
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
		invalid_travel();
	}

	/* Battle all the enemies in the current room before moving on */
	uint8_t i;
	for (i = 0; i < MAX_ENEMIES_PER_ROOM; i++) {
		battle_enemy(&player, &game.room[player.xloc][player.yloc].enemies[0]);
	}

	///TODO fix battle_enemies()
	/* battle_enemies(&player, &game.room[player.xloc][player.yloc].enemies); */

	travel_screen();
}
