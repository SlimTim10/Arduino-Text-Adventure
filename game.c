#include "game.h"
#include "resources.h"
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

static struct player player;

static struct room {
	char *text;
	struct enemy enemies[MAX_ENEMIES_PER_ROOM];
};

static struct game {
	struct room room[MAP_WIDTH][MAP_HEIGHT];
} game;

static enum direction_choices direction_choice;

/* Show the available direction choices */
static void show_dir_choices(void) {
	lcd_write(STR_NORTH, NORTH_X, NORTH_Y);
	lcd_write(STR_EAST, EAST_X, EAST_Y);
	lcd_write(STR_SOUTH, SOUTH_X, SOUTH_Y);
	lcd_write(STR_WEST, WEST_X, WEST_Y);
}

/* Draw the cursor at the current direction choice */
static void curs_dir_choice(void) {
	lcd_write(STR_SPACE, CURS_NORTH_X, CURS_NORTH_Y);
	lcd_write(STR_SPACE, CURS_EAST_X, CURS_EAST_Y);
	lcd_write(STR_SPACE, CURS_SOUTH_X, CURS_SOUTH_Y);
	lcd_write(STR_SPACE, CURS_WEST_X, CURS_WEST_Y);

	switch (direction_choice) {
	case NORTH:
		lcd_write(STR_CURS, CURS_NORTH_X, CURS_NORTH_Y);
		break;
	case EAST:
		lcd_write(STR_CURS, CURS_EAST_X, CURS_EAST_Y);
		break;
	case SOUTH:
		lcd_write(STR_CURS, CURS_SOUTH_X, CURS_SOUTH_Y);
		break;
	case WEST:
		lcd_write(STR_CURS, CURS_WEST_X, CURS_WEST_Y);
		break;
	}
}

/* Display message asking which direction to go and show options */
static void travel_screen(void) {
	game_text(STR_TRAVEL_SCREEN);
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
	game_text(STR_INVALID_TRAVEL);
	delay(TEXT_DELAY);
}

static void add_enemy(uint8_t xloc, uint8_t yloc, char *name, int8_t hp, uint8_t lvl) {
	uint8_t i;
	for (i = 0; i < MAX_ENEMIES_PER_ROOM; i++) {
		if (game.room[xloc][yloc].enemies[i].hp == 0) {
			game.room[xloc][yloc].enemies[i].name = name;
			game.room[xloc][yloc].enemies[i].hp = hp;
			game.room[xloc][yloc].enemies[i].lvl = lvl;
			break;
		}
	}
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
	game.room[0][0].text = STR_ROOM_00;
	game.room[1][0].text = STR_ROOM_10;
	game.room[2][0].text = STR_ROOM_20;
	game.room[0][1].text = STR_ROOM_01;
	game.room[1][1].text = STR_ROOM_11;
	game.room[2][1].text = STR_ROOM_21;
	game.room[0][2].text = STR_ROOM_02;
	game.room[1][2].text = STR_ROOM_12;
	game.room[2][2].text = STR_ROOM_22;

	add_enemy(2, 1, STR_SNAIL, 3, 1);
	add_enemy(2, 1, STR_RAT, 5, 1);

	player.xloc = 1;
	player.yloc = 1;
	player.prev_xloc = player.xloc;
	player.prev_yloc = player.yloc;
	player.run = false;
	player.hp = 100;
	player.lvl = 1;
	player.xp = 0;
	player.xp_next_lvl = 20;
}

/* Intro for the game */
void game_intro(void) {
	game_text(STR_WELCOME);
	lcd_write(">Start", 20, 4);

	while (get_user_input() != B_SELECT);

	srand(millis());

	game_text_anim(STR_INTRO);
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
		/* Battle all the enemies in the current room before moving on */
		uint8_t i;
		for (i = 0; i < MAX_ENEMIES_PER_ROOM && !player.run; i++) {
			battle_enemy(&player, &game.room[player.xloc][player.yloc].enemies[i]);
		}
		if (player.run) {
			player.xloc = player.prev_xloc;
			player.yloc = player.prev_yloc;
			show_room_text();
			player.run = false;
		}
		player.prev_xloc = player.xloc;
		player.prev_yloc = player.yloc;
	} else {
		invalid_travel();
	}

	travel_screen();
}
