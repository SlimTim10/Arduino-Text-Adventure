#include "battle.h"
#include "const.h"
#include "nokia5110.h"
#include "control.h"
#include "game.h"

enum battle_choices {
	ATTACK,
	RUN,
	MAX_BATTLE_CHOICE,
};

enum text_loc {
	ATTACK_X = 6,
	ATTACK_Y = 3,
	RUN_X = 6,
	RUN_Y = 4,
};

enum curs_loc {
	CURS_ATTACK_X = ATTACK_X - 6,
	CURS_ATTACK_Y = ATTACK_Y,
	CURS_RUN_X = RUN_X - 6,
	CURS_RUN_Y = RUN_Y,
};

struct player_info player;

static enum battle_choices battle_choice;

/* Show the available battle choices */
static void show_battle_choices(void) {
	lcd_write("Attack", ATTACK_X, ATTACK_Y);
	lcd_write("Run", RUN_X, RUN_Y);
}

/* Draw the cursor at the current battle choice */
static void curs_battle_choice(void) {
	lcd_write(" ", CURS_ATTACK_X, CURS_ATTACK_Y);
	lcd_write(" ", CURS_RUN_X, CURS_RUN_Y);

	switch (battle_choice) {
	case ATTACK:
		lcd_write(">", CURS_ATTACK_X, CURS_ATTACK_Y);
		break;
	case RUN:
		lcd_write(">", CURS_RUN_X, CURS_RUN_Y);
		break;
	}
}

/* Move the cursor to the next battle option */
static void next_battle_choice(void) {
	battle_choice = (battle_choice + 1) % MAX_BATTLE_CHOICE;
	curs_battle_choice();
}

/* Perform the currently selected choice against the enemy */
static void do_action(uint8_t en) {
	switch (battle_choice) {
	case ATTACK:
		player.hp -= 10;
		game_text("You got hit!");
		break;
	case RUN: {
		int escape_chance;
		if (en == 1) {
			escape_chance = 50;
		} else if (en == 2) {
			escape_chance = 33;
		} else if (en == 3) {
			escape_chance = 25;
		} else {
			escape_chance = 100;
		}
		if (random() % (100 / escape_chance) == 0) {
			game_text("Got away safely!");
		} else {
			game_text("Can't escape!");
		}
		break;
	}
	}
	delay(TEXT_DELAY);

}

/* Display message asking what to do and show options */
static void battle_screen(void) {
	game_text("What do you want to do?");
	show_battle_choices();
	battle_choice = ATTACK;
	curs_battle_choice();
}

/* Battle an enemy until one of you dies or you run away */
static void battle(uint8_t en) {
	battle_screen();

	while (player.hp > 0) {
		switch (get_user_input()) {
		case B_CHANGE:
			next_battle_choice();
			break;
		case B_SELECT:
			do_action(en);
			battle_screen();
			break;
		}
	}
}

/* Battle all the enemies in the current room before moving on */
void battle_enemies(uint8_t *en) {
	uint8_t i;
	for (i = 0; i < MAX_ENEMIES_PER_ROOM; i++) {
		if (en[i] != 0) {
			game_text("There's an enemy!");
			delay(TEXT_DELAY);
			battle(en[i]);
		}
	}
}
