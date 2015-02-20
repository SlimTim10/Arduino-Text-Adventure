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
	PLAYER_HP_X = 0,
	PLAYER_HP_Y = 0,
	ENEMY_HP_X = 0,
	ENEMY_HP_Y = 1,
};

enum curs_loc {
	CURS_ATTACK_X = ATTACK_X - 6,
	CURS_ATTACK_Y = ATTACK_Y,
	CURS_RUN_X = RUN_X - 6,
	CURS_RUN_Y = RUN_Y,
};

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

static void show_healths(struct player *pl, struct enemy *en) {
	char msg[LCD_MAX_TEXT];
	sprintf(msg, "You: %dHP", pl->hp);
	lcd_write(msg, PLAYER_HP_X, PLAYER_HP_Y);
	sprintf(msg, "%s: %dHP", en->name, en->hp);
	lcd_write(msg, ENEMY_HP_X, ENEMY_HP_Y);
}

/* Enemy attacks the player */
static void enemy_attacks(struct player *pl, struct enemy *en) {
	uint8_t dmg = rand() % (en->lvl * 10);
	pl->hp -= dmg;
	char msg[LCD_MAX_TEXT];
	sprintf(msg, "The %s attacks for %d damage!", en->name, dmg);
	game_text(msg);
	delay(TEXT_DELAY);
}

/* Player attacks the enemy */
static void player_attacks(struct player *pl, struct enemy *en) {
	uint8_t dmg = rand() % (pl->lvl * 10);
	en->hp -= dmg;
	char msg[LCD_MAX_TEXT];
	sprintf(msg, "You attack viciously for %d damage!", dmg);
	game_text(msg);
	delay(TEXT_DELAY);
}

/* Perform the currently selected choice against the enemy */
static void do_action(struct player *pl, struct enemy *en, boolean *ran) {
	switch (battle_choice) {
	case ATTACK:
		player_attacks(pl, en);
		break;
	case RUN: {
		int escape_chance;
		if (en->lvl == 1) {
			escape_chance = 50;
		} else if (en->lvl == 2) {
			escape_chance = 33;
		} else if (en->lvl == 3) {
			escape_chance = 25;
		} else {
			escape_chance = 100;
		}
		if (rand() % (100 / escape_chance) == 0) {
			*ran = true;
		} else {
			game_text("Can't escape!");
			delay(TEXT_DELAY);
		}
		break;
	}
	}
}

/* Display healths and show action options */
static void battle_screen(struct player *pl, struct enemy *en) {
	lcd_clear();
	show_healths(pl, en);
	show_battle_choices();
	battle_choice = ATTACK;
	curs_battle_choice();
}

/* Battle an enemy until one of you dies or you run away */
static void battle(struct player *pl, struct enemy *en) {
	boolean ran = false;

	battle_screen(pl, en);

	while (pl->hp > 0 && en->hp > 0 && !ran) {
		switch (get_user_input()) {
		case B_CHANGE:
			next_battle_choice();
			break;
		case B_SELECT:
			do_action(pl, en, &ran);
			if (en->hp > 0 && !ran) {
				enemy_attacks(pl, en);
			}
			if (pl->hp > 0 && en->hp > 0 && !ran) {
				battle_screen(pl, en);
			}
			break;
		}
	}

	if (pl->hp <= 0) {
		game_text("You died.");
		delay(TEXT_DELAY);
	} else if (en->hp <= 0) {
		char msg[LCD_MAX_TEXT];
		sprintf(msg, "You defeated the %s!", en->name);
		game_text(msg);
		delay(TEXT_DELAY);
	} else if (ran) {
		game_text("Got away safely!");
		delay(TEXT_DELAY);
	}
}

///TODO fix this
/* Battle all the enemies in the current room before moving on */
void battle_enemies(struct player *pl, struct enemy *enemies[]) {
	char msg[LCD_MAX_TEXT];
	uint8_t i;
	for (i = 0; i < MAX_ENEMIES_PER_ROOM; i++) {
		if (enemies[i]->hp > 0) {
			sprintf(msg, "There's a %s!", enemies[i]->name);
			game_text(msg);
			delay(TEXT_DELAY);
			battle(pl, enemies[i]);
		}
	}
}

/* Engage in battle with an enemy */
void battle_enemy(struct player *pl, struct enemy *en) {
	char msg[LCD_MAX_TEXT];
	uint8_t i;
	if (en->hp > 0) {
		sprintf(msg, "There's a %s!", en->name);
		game_text(msg);
		delay(TEXT_DELAY);
		battle(pl, en);
	}
}
