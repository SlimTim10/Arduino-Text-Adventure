#ifndef SIMPLE_BUTTONS_H
#define SIMPLE_BUTTONS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

void simple_interrupt(uint8_t, uint8_t, volatile void (*));
boolean simple_button_press(uint8_t);
void simple_button_wait(uint8_t, boolean);

#ifdef __cplusplus
}
#endif

#endif
