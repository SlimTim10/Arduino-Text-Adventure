#include "const.h"
#include "resources.h"
#include "hal.h"
#include "PCD8544.h"
#include "lcd_extra.h"
#include "game.h"
#include "control.h"

struct lcd_pins lcd;

/* Edit this function to customize the game */
void setup_world(void) {
	/* Set map dimensions (maximum 8 by 8) */
	set_map_width(4);
	set_map_height(4);

	/* Set the goal at [3,3] */
	set_goal(3, 3);

	/* Map */
	/* [0,0] [1,0] [2,0] [3,0] */
	/* [0,1] [1,1] [2,1] [3,1]  */
	/* [0,2] [1,2] [2,2] [3,2] */
	/* [0,3] [1,3] [2,3] [3,3] */

	/* Make room [1,0] into a wall (player can't enter this room) */
	make_wall(1, 0);
	/* Make room [2,2] into a wall */
	make_wall(2, 2);
	/* Make room [3,2] into a wall */
	make_wall(3, 2);

	/* There can be at most 3 enemies in a room */
	/* Add a level 1 snail to room [2,1] with 3 HP */
	add_enemy(2, 1, "snail", 3, 1);
	/* Add a level 1 rat to room [2,1] with 5 HP */
	add_enemy(2, 1, "rat", 5, 1);
	/* Add a level 2 bee to room [3,0] with 5 HP */
	add_enemy(3, 0, "bee", 5, 2);
	/* Add a level 2 Tim to room [2,3] with 20 HP */
	add_enemy(2, 3, "Tim", 20, 2);
	/* Add a level 3 Chris to room [2,3] with 30 HP */
	add_enemy(2, 3, "Chris", 30, 3);
	/* Add a level 4 David to room [3,3] with 50 HP */
	add_enemy(3, 3, "David", 50, 4);

	/* Start the player in room [0,0] */
	set_player_location(0, 0);

	/* Player's starting HP and level */
	set_player_hp(100);
	set_player_level(1);
}

void setup_pins(void) {
	lcd.res = LCD_PIN_RESET;
	lcd.sce = LCD_PIN_SCE;
	lcd.dc = LCD_PIN_DC;
	lcd.sdin = LCD_PIN_SDIN;
	lcd.sclk = LCD_PIN_SCLK;
	
	pinMode(LCD_PIN_LIGHT, OUTPUT);

	pinMode(BUTTON1_PIN, INPUT);
	pinMode(BUTTON2_PIN, INPUT);
}

void setup(void) {
	setup_pins();
	setup_control();

	lcd_init(&lcd);
   	lcd_light(5);

	game_text(STR_TO_RAM(STR_WELCOME));

	lcd_printat(STR_TO_RAM(STR_START), 20, 4);
	while (get_user_input() != B_SELECT);

	srand(millis());

	setup_world();
	game_init();
	game_intro();
}

void loop(void) {
	switch (get_user_input()) {
	case B_CHANGE:
		next_travel_choice();
		button1_wait();
		break;
	case B_SELECT:
		travel_select();
		button2_wait();
		break;
	}

	if (is_player_dead()) {
		game_text(STR_TO_RAM(STR_WELCOME));

		lcd_printat(STR_TO_RAM(STR_START), 20, 4);
		while (get_user_input() != B_SELECT);

		setup_world();
		game_init();
		game_intro();
	}

	if (game_won()) {
		game_text(STR_TO_RAM(STR_WELCOME));

		lcd_printat(STR_TO_RAM(STR_START), 20, 4);
		while (get_user_input() != B_SELECT);

		setup_world();
		game_init();
		game_intro();
	}		
}
