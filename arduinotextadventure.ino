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

	lcd_init();
	lcd_contrast(0x1F);
   	lcd_light(1);

	game_intro();
}

void loop(void) {
	///TESTING
	delay(1000);

	/* Simulate button 1 presses */
	int i;
	int r = random(0, 4);
	for (i = 0; i < r; i++) {
		next_dir_choice();
		delay(1000);
	}
	/* Simulate button 2 press */
	travel();
	delay(1000);
}
