#include "const.h"
#include "resources.h"
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
	/* Add a level 4 Tim to room [2,3] with 20 HP */
	add_enemy(2, 3, "Tim", 20, 4);
	/* Add a level 5 Chris to room [2,3] with 30 HP */
	add_enemy(2, 3, "Chris", 30, 5);
	/* Add a level 10 David to room [3,3] with 20 HP */
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

	lcd_init();
   	lcd_light(5);

	game_text(STR_TO_RAM(STR_WELCOME));

	lcd_write(STR_TO_RAM(STR_START), 20, 4);
	while (get_user_input() != B_SELECT);

	srand(millis());

	setup_game();
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

	if (is_player_dead()) {
		game_text(STR_TO_RAM(STR_WELCOME));

		lcd_write(STR_TO_RAM(STR_START), 20, 4);
		while (get_user_input() != B_SELECT);

		setup_game();
		setup_world();
		game_intro();
	}
}
