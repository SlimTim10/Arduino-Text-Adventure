#include "control.h"
#include "simple_buttons.h"
#include "hal.h"

#define button1()	digitalRead(BUTTON1_PIN)
#define button2()	digitalRead(BUTTON2_PIN)

enum {
	DEBOUNCE_MS = 10,
};

volatile boolean button1_pressed;
volatile boolean button2_pressed;

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

	if (button1_pressed) {
		delay(DEBOUNCE_MS);
		if (button1()) {
			button1_pressed = false;
			return B_CHANGE;
		} else {
			return B_NONE;
		}
	} else if (button2_pressed) {
		delay(DEBOUNCE_MS);
		if (button2()) {
			button2_pressed = false;
			return B_SELECT;
		} else {
			return B_NONE;
		}
	} else {
		return B_NONE;
	}
}

void button1_wait(void) {
	simple_button_wait(BUTTON1_PIN, LOW);
	button1_pressed = false;
}

void button2_wait(void) {
	simple_button_wait(BUTTON2_PIN, LOW);
	button2_pressed = false;
}
