#include "battle.h"
#include "resources.h"
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
	lcd_write(STR_TO_RAM(STR_ATTACK), ATTACK_X, ATTACK_Y);
	lcd_write(STR_TO_RAM(STR_RUN), RUN_X, RUN_Y);
}

/* Draw the cursor at the current battle choice */
static void curs_battle_choice(void) {
	lcd_write(STR_TO_RAM(STR_SPACE), CURS_ATTACK_X, CURS_ATTACK_Y);
	lcd_write(STR_TO_RAM(STR_SPACE), CURS_RUN_X, CURS_RUN_Y);

	switch (battle_choice) {
	case ATTACK:
		lcd_write(STR_TO_RAM(STR_CURS), CURS_ATTACK_X, CURS_ATTACK_Y);
		break;
	case RUN:
		lcd_write(STR_TO_RAM(STR_CURS), CURS_RUN_X, CURS_RUN_Y);
		break;
	}
}

/* Move the cursor to the next battle option */
static void next_battle_choice(void) {
	battle_choice = (battle_choice + 1) % MAX_BATTLE_CHOICE;
	curs_battle_choice();
}

/* Show health of player and enemy */
static void show_healths(struct player *pl, struct enemy *en) {
	char msg[LCD_MAX_TEXT];
	sprintf(msg, STR_TO_RAM(STR_PLAYER_HP), pl->hp);
	lcd_write(msg, PLAYER_HP_X, PLAYER_HP_Y);
	sprintf(msg, STR_TO_RAM(STR_ENEMY_HP), en->name, en->hp);
	lcd_write(msg, ENEMY_HP_X, ENEMY_HP_Y);
}

/* Given attacker level and opponent level, calculate damage made by attacker */
static uint8_t calc_dmg(uint8_t attacker_lvl, uint8_t opponent_lvl) {
	int8_t diff = max(0, (int8_t) (opponent_lvl - attacker_lvl));
	uint8_t range = 10;
	int8_t max_dmg = max(0, (int8_t) ((attacker_lvl * 10) - (diff * 10)));
	int8_t min_dmg = max(0, (int8_t) (max_dmg - range));
	uint8_t dmg = min_dmg + (rand() % range);
	return dmg;
}

/* Enemy attacks the player */
static void enemy_attacks(struct player *pl, struct enemy *en) {
	uint8_t dmg = calc_dmg(en->lvl, pl->lvl);
	pl->hp -= dmg;
	char msg[LCD_MAX_TEXT];
	if (dmg == 0) {
		sprintf(msg, STR_TO_RAM(STR_ENEMY_MISS), en->name);
	} else {
		sprintf(msg, STR_TO_RAM(STR_ENEMY_ATTACK), en->name, dmg);
	}
	game_text(msg);
	delay(TEXT_DELAY);
}

/* Player attacks the enemy */
static void player_attacks(struct player *pl, struct enemy *en) {
	uint8_t dmg = calc_dmg(pl->lvl, en->lvl);
	en->hp -= dmg;
	char msg[LCD_MAX_TEXT];
	if (dmg == 0) {
		sprintf(msg, STR_TO_RAM(STR_PLAYER_MISS));
	} else {
		sprintf(msg, STR_TO_RAM(STR_PLAYER_ATTACK), dmg);
	}
	game_text(msg);
	delay(TEXT_DELAY);
}

/* Perform the currently selected choice against the enemy */
static void do_action(struct player *pl, struct enemy *en) {
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
			escape_chance = 10;
		}
		if (rand() % (100 / escape_chance) == 0) {
			pl->run = true;
		} else {
			game_text(STR_TO_RAM(STR_CANT_ESCAPE));
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

/* Player wins the battle */
static void battle_win(struct player *pl, struct enemy *en) {
	char msg[LCD_MAX_TEXT];
	sprintf(msg, STR_TO_RAM(STR_BATTLE_WIN), en->name);
	game_text(msg);
	delay(TEXT_DELAY);

	uint8_t xp = en->lvl * XP_GAIN;
	pl->xp += xp;
	sprintf(msg, STR_TO_RAM(STR_XP_GAIN), xp);
	game_text(msg);
	delay(TEXT_DELAY);

	if (pl->xp >= pl->xp_next_lvl && pl->lvl < MAX_LVL) {
		pl->lvl++;
		pl->hp = MAX_HP;
		pl->xp_next_lvl += XP_NEXT_INC;
		game_text_anim(STR_TO_RAM(STR_LVL_GAIN));
		delay(TEXT_DELAY);
	}

	lcd_clear();
	sprintf(msg, STR_TO_RAM(STR_LVL), pl->lvl);
	lcd_write(msg, 0, 0);
	sprintf(msg, STR_TO_RAM(STR_HP), pl->hp);
	lcd_write(msg, 0, 1);
	sprintf(msg, STR_TO_RAM(STR_XP), pl->xp);
	lcd_write(msg, 0, 2);
	sprintf(msg, STR_TO_RAM(STR_NEXT), pl->xp_next_lvl);
	lcd_write(msg, 0, 3);
	while (get_user_input() != B_SELECT);
}

/* Battle an enemy until one of you dies or you run away */
static void battle(struct player *pl, struct enemy *en) {
	battle_screen(pl, en);

	while (pl->hp > 0 && en->hp > 0 && !pl->run) {
		switch (get_user_input()) {
		case B_CHANGE:
			next_battle_choice();
			break;
		case B_SELECT:
			do_action(pl, en);
			if (en->hp > 0 && !pl->run) {
				enemy_attacks(pl, en);
			}
			if (pl->hp > 0 && en->hp > 0 && !pl->run) {
				battle_screen(pl, en);
			}
			break;
		}
	}

	if (pl->hp <= 0) {
		game_text(STR_TO_RAM(STR_PLAYER_DEATH));
		delay(TEXT_DELAY);
	} else if (en->hp <= 0) {
		battle_win(pl, en);
	} else if (pl->run) {
		game_text(STR_TO_RAM(STR_ESCAPE));
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
			sprintf(msg, STR_TO_RAM(STR_ENEMY), enemies[i]->lvl, enemies[i]->name);
			game_text_anim(msg);
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
		sprintf(msg, STR_TO_RAM(STR_ENEMY), en->lvl, en->name);
		game_text_anim(msg);
		delay(TEXT_DELAY);
		battle(pl, en);
	}
}
