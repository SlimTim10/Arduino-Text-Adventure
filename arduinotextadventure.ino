#include "const.h"
#include "hal.h"
#include "nokia5110.h"
#include "game.h"
#include "control.h"

/* Edit this function to customize the game */
void setup_world(void) {
	/* Map */
	/* [0,0] [1,0] [2,0] [3,0] */
	/* [0,1] [1,1] [2,1] [3,1]  */
	/* [0,2] [1,2] [2,2] [3,2] */
	/* [0,3] [1,3] [2,3] [3,3] */

	/* There can be at most 3 enemies in a room */
	/* Add a level 1 snail to room [2,1] with 3 HP */
	add_enemy(2, 1, "snail", 3, 1);
	/* Add a level 1 rat to room [2,1] with 5 HP */
	add_enemy(2, 1, "rat", 5, 1);

	add_enemy(2, 3, "Tim", 20, 4);
	add_enemy(2, 3, "Chris", 30, 5);
	add_enemy(3, 3, "David", 50, 10);

	/* Start the player in room [0,0] */
	set_player_location(0, 0);

	/* Player's starting HP and level */
	set_player_hp(100);
	set_player_level(1);
}

void setup_pins(void) {
	pinMode(LCD_PIN_SCE, OUTPUT);
	pinMode(LCD_PIN_RESET, OUTPUT);
	pinMode(LCD_PIN_DC, OUTPUT);
	pinMode(LCD_PIN_SDIN, OUTPUT);
	pinMode(LCD_PIN_SCLK, OUTPUT);
	pinMode(BUTTON1_PIN, INPUT);
	pinMode(BUTTON2_PIN, INPUT);
}

void setup(void) {
	setup_pins();
	setup_control();
	setup_game();

	lcd_init();
   	lcd_light(0);

	setup_world();
	game_intro();
}

void loop(void) {
	switch (get_user_input()) {
	case B_CHANGE:
		next_dir_choice();
		button1_wait();
		break;
	case B_SELECT:
		travel();
		button2_wait();
		break;
	}
}
