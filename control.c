#include "control.h"
#include "simple_buttons.h"
#include "hal.h"

volatile boolean button1_pressed;
volatile boolean button2_pressed;

enum user_input get_user_input(void) {
	enum user_input b;
	button1_pressed = false;
	button2_pressed = false;

	simple_interrupt(BUTTON1, RISING, &button1_pressed);
	simple_interrupt(BUTTON2, RISING, &button2_pressed);

	while (!button1_pressed && !button2_pressed);

	if (button1_pressed) {
		b = B_CHANGE;
	} else if (button2_pressed) {
		b = B_SELECT;
	}

	return b;
}

void debounce_button1(void) {
	simple_debounce(BUTTON1, LOW);
	button1_pressed = false;
}

void debounce_button2(void) {
	simple_debounce(BUTTON2, LOW);
	button2_pressed = false;
}
