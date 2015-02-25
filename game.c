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
	boolean iswall;
	struct enemy enemies[MAX_ENEMIES_PER_ROOM];
};

static struct game {
	uint8_t map_width;
	uint8_t map_height;
	uint8_t xgoal;
	uint8_t ygoal;
	struct room room[MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
} game;

static enum direction_choices direction_choice;

/* Show the available direction choices */
static void show_dir_choices(void) {
	lcd_write(STR_TO_RAM(STR_NORTH), NORTH_X, NORTH_Y);
	lcd_write(STR_TO_RAM(STR_EAST), EAST_X, EAST_Y);
	lcd_write(STR_TO_RAM(STR_SOUTH), SOUTH_X, SOUTH_Y);
	lcd_write(STR_TO_RAM(STR_WEST), WEST_X, WEST_Y);
}

/* Draw the cursor at the current direction choice */
static void curs_dir_choice(void) {
	lcd_write(STR_TO_RAM(STR_SPACE), CURS_NORTH_X, CURS_NORTH_Y);
	lcd_write(STR_TO_RAM(STR_SPACE), CURS_EAST_X, CURS_EAST_Y);
	lcd_write(STR_TO_RAM(STR_SPACE), CURS_SOUTH_X, CURS_SOUTH_Y);
	lcd_write(STR_TO_RAM(STR_SPACE), CURS_WEST_X, CURS_WEST_Y);

	switch (direction_choice) {
	case NORTH:
		lcd_write(STR_TO_RAM(STR_CURS), CURS_NORTH_X, CURS_NORTH_Y);
		break;
	case EAST:
		lcd_write(STR_TO_RAM(STR_CURS), CURS_EAST_X, CURS_EAST_Y);
		break;
	case SOUTH:
		lcd_write(STR_TO_RAM(STR_CURS), CURS_SOUTH_X, CURS_SOUTH_Y);
		break;
	case WEST:
		lcd_write(STR_TO_RAM(STR_CURS), CURS_WEST_X, CURS_WEST_Y);
		break;
	}
}

/* Display message asking which direction to go and show options */
static void travel_screen(void) {
	game_text(STR_TO_RAM(STR_TRAVEL_SCREEN));
	show_dir_choices();
	direction_choice = NORTH;
	curs_dir_choice();
}

/* Display text for the current room */
static void show_room_text(void) {
	char loc[LCD_MAX_TEXT];
	sprintf(loc, "[%d,%d]", player.xloc, player.yloc);
	lcd_clear();
	lcd_write_wrap(loc, 0, 0);
	lcd_write_wrap_anim(STR_TO_RAM(game.room[player.xloc][player.yloc].text), 0, 1);
	delay(TEXT_DELAY);
}

/* The player cannot move in the current chosen direction */
static void invalid_travel(void) {
	game_text(STR_TO_RAM(STR_INVALID_TRAVEL));
	delay(TEXT_DELAY);
}

/* Set the width of the map */
void set_map_width(uint8_t w) {
	game.map_width = w;
}

/* Set the height of the map */
void set_map_height(uint8_t h) {
	game.map_height = h;
}

/* Make a room into a wall */
void make_wall(uint8_t xloc, uint8_t yloc) {
	game.room[xloc][yloc].iswall = true;
}

/* Add an enemy in room at [xloc,yloc] with name, HP, and level */
void add_enemy(uint8_t xloc, uint8_t yloc, char *name, int8_t hp, uint8_t lvl) {
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

/* Has the player died? */
boolean is_player_dead(void) {
	return (player.hp <= 0);
}

/* Put the player in room [xloc,yloc] */
void set_player_location(uint8_t xloc, uint8_t yloc) {
	player.xloc = xloc;
	player.yloc = yloc;
	player.prev_xloc = player.xloc;
	player.prev_yloc = player.yloc;
}

/* Set the player's HP */
void set_player_hp(int8_t hp) {
	player.hp  = hp;
}

/* Set the player's level */
void set_player_level(uint8_t lvl) {
	player.lvl = lvl;
}

/* Set the goal location */
void set_goal(uint8_t x, uint8_t y) {
	game.xgoal = x;
	game.ygoal = y;
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
void game_init(void) {
	uint8_t x, y;
	char text[LCD_MAX_TEXT];
	for (y = 0; y < game.map_height; y++) {
		for (x = 0; x < game.map_width; x++) {
			game.room[x][y].text = pgm_read_word(&STR_ROOM_TEXT[rand() % STR_ROOM_TEXT_NUM]);
		}
	}

	player.run = false;
	player.xp_next_lvl = XP_NEXT_INC;
}

/* Intro for the game */
void game_intro(void) {
	game_text_anim(STR_TO_RAM(STR_INTRO));
	delay(TEXT_DELAY);

	show_room_text();
	travel_screen();
}

/* Check if the player has won and display information if so */
boolean game_won(void) {
	if (player.xloc == game.xgoal && player.yloc == game.ygoal) {
		char msg[LCD_MAX_TEXT];
		lcd_clear();
		lcd_write(STR_TO_RAM(STR_WIN), 0, 0);
		sprintf(msg, STR_TO_RAM(STR_LVL), player.lvl);
		lcd_write(msg, 0, 2);
		sprintf(msg, STR_TO_RAM(STR_HP), player.hp);
		lcd_write(msg, 0, 3);
		sprintf(msg, STR_TO_RAM(STR_XP), player.xp);
		lcd_write(msg, 0, 4);
		sprintf(msg, STR_TO_RAM(STR_NEXT), player.xp_next_lvl);
		lcd_write(msg, 0, 5);
		while (get_user_input() != B_SELECT);
		return true;
	}
	return false;
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
		if (player.xloc >= game.map_width - 1) {
			valid = false;
			break;
		}
		player.xloc++;
		break;
	case SOUTH:
		if (player.yloc >= game.map_height - 1) {
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

	if (game.room[player.xloc][player.yloc].iswall) {
		valid = false;
		player.xloc = player.prev_xloc;
		player.yloc = player.prev_yloc;
	}

	if (valid) {
		show_room_text();
		/* Battle all the enemies in the current room before moving on */
		uint8_t i;
		for (i = 0; i < MAX_ENEMIES_PER_ROOM && !player.run; i++) {
			battle_enemy(&player, &game.room[player.xloc][player.yloc].enemies[i]);
			if (player.hp <= 0) {
				return;
			}
		}
		if (game_won()) {
			return;
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
