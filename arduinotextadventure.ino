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

	/* lcd_write_wrap("Welcome to the text adventure", 0, 0); */
	/* lcd_write(" Up", 0, 3); */
	/* lcd_write(" Down", 40, 3); */
	/* lcd_write(" Left", 0, 4); */
	/* lcd_write(" Right", 40, 4); */
	/* lcd_write(">", 0, 3); */
	/* delay(2000); */
	/* lcd_write(" ", 0, 3); */
	/* lcd_write(">", 40, 3); */
	/* delay(2000); */
	/* lcd_write(" ", 40, 3); */
	/* lcd_write(">", 0, 4); */
	/* delay(2000); */
	/* lcd_write(" ", 0, 4); */
	/* lcd_write(">", 40, 4); */
}

void loop(void) {
	;
}
