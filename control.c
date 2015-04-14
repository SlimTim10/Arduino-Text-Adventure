#include "control.h"
#include "simple_buttons.h"
#include "hal.h"
#include "PCD8544.h"

static volatile boolean button1_pressed;
static volatile boolean button2_pressed;

void setup_control(void) {
	simple_interrupt(BUTTON1_PIN, RISING, &button1_pressed);
	simple_interrupt(BUTTON2_PIN, RISING, &button2_pressed);

	button1_pressed = false;
	button2_pressed = false;
}

enum user_input get_user_input(void) {
	button1_pressed = false;
	button2_pressed = false;

	while (!button1_pressed && !button2_pressed) {
		lcd_contrast((uint8_t) (analogRead(POT_PIN) * (255.0 / 1023.0)));
	}

	if (simple_button_press(BUTTON1_PIN)) {
		return B_CHANGE;
	} else if (simple_button_press(BUTTON2_PIN)) {
		return B_SELECT;
	} else {
		return B_NONE;
	}
}

void button1_wait(void) {
	simple_button_wait(BUTTON1_PIN, LOW);
}

void button2_wait(void) {
	simple_button_wait(BUTTON2_PIN, LOW);
}
