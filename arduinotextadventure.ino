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

	lcdLight(1);	// Turn light on dimly

	lcdClear();

	lcdParagraph("1234567890 1234567890", 0, 0);
	//	lcdParagraph("Test test test test test test.", 0, 0);
	delay(10000);

	lcdParagraph("Welcome to the text adventure", 0, 0);

	lcdString(" Up", 0, 3);
	lcdString(" Down", 40, 3);
	lcdString(" Left", 0, 4);
	lcdString(" Right", 40, 4);
	lcdString(">", 0, 3);
	delay(2000);
	lcdString(" ", 0, 3);
	lcdString(">", 40, 3);
	delay(2000);
	lcdString(" ", 40, 3);
	lcdString(">", 0, 4);
	delay(2000);
	lcdString(" ", 0, 4);
	lcdString(">", 40, 4);
}

void loop(void) {
	;
}
