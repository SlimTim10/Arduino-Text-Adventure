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
	pinMode(BUTTON1, INPUT);
	pinMode(BUTTON2, INPUT);
}

void setup(void) {
	setup_pins();
	setup_control();
	setup_game();

	lcd_init();
	lcd_contrast(0x2F);
   	lcd_light(0);

	game_intro();
}

void loop(void) {
	switch (get_user_input()) {
	case B_CHANGE:
		next_dir_choice();
		debounce_button1();
		break;
	case B_SELECT:
		travel();
		debounce_button2();
		break;
	}
}
