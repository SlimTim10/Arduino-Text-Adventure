#include "const.h"
#include "hal.h"
#include "nokia5110.h"
#include "game.h"
#include "control.h"

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
