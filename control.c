#include "control.h"
#include "simple_buttons.h"
#include "hal.h"

volatile boolean button1_pressed;
volatile boolean button2_pressed;

void setup_control(void) {
	simple_interrupt(BUTTON1, RISING, &button1_pressed);
	simple_interrupt(BUTTON2, RISING, &button2_pressed);

	button1_pressed = false;
	button2_pressed = false;
}

enum user_input get_user_input(void) {
	button1_pressed = false;
	button2_pressed = false;

	while (!button1_pressed && !button2_pressed) {
		lcd_contrast((uint8_t) (analogRead(POT_PIN) * (255.0 / 1023.0)));
	}

	if (button1_pressed) {
		return B_CHANGE;
	} else if (button2_pressed) {
		return B_SELECT;
	} else {
		return 0;
	}
}

void debounce_button1(void) {
	simple_debounce(BUTTON1, LOW);
	button1_pressed = false;
}

void debounce_button2(void) {
	simple_debounce(BUTTON2, LOW);
	button2_pressed = false;
}
