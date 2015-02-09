#include "hal.h"
#include "nokia5110.h"

void setup_pins(void) {
	pinMode(LCD_PIN_SCE, OUTPUT);
	pinMode(LCD_PIN_RESET, OUTPUT);
	pinMode(LCD_PIN_DC, OUTPUT);
	pinMode(LCD_PIN_SDIN, OUTPUT);
	pinMode(LCD_PIN_SCLK, OUTPUT);
}


void setup(void) {
	setup_pins();

	lcdInitialize();
	lcdClear();
	lcdString("Hello World!", 0, 0);
	delay(3000);
	lcdClear();
	lcdString("Test", 30, 0);
}

void loop(void) {
	;
}
