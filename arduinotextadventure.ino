#include "const.h"
#include "hal.h"
#include "nokia5110.h"
#include "game.h"

void setup_pins(void) {
	pinMode(LCD_PIN_SCE, OUTPUT);
	pinMode(LCD_PIN_RESET, OUTPUT);
	pinMode(LCD_PIN_DC, OUTPUT);
	pinMode(LCD_PIN_SDIN, OUTPUT);
	pinMode(LCD_PIN_SCLK, OUTPUT);
}

void setup(void) {
	setup_pins();

   	lcd_light(0);

	game_intro();
}

void loop(void) {
	;
}
