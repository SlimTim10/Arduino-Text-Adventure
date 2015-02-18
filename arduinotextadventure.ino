#include "const.h"
#include "hal.h"
#include "nokia5110.h"
#include "simple_buttons.h"
#include "game.h"

volatile boolean button1_pressed;
volatile boolean button2_pressed;

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

	lcd_init();
	lcd_contrast(0x1F);
   	lcd_light(1);

	game_intro();

	button1_pressed = false;
	button2_pressed = false;
	simple_interrupt(BUTTON1, RISING, &button1_pressed);
	simple_interrupt(BUTTON2, RISING, &button2_pressed);
}

void loop(void) {
	if (button1_pressed) {
		next_dir_choice();
		simple_debounce(BUTTON1, LOW);
		button1_pressed = false;
	}

	if (button2_pressed) {
		travel();
		simple_debounce(BUTTON2, LOW);
		button2_pressed = false;
	}
}
