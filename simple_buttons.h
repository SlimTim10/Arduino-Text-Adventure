#ifndef SIMPLE_INTERRUPTS_H
#define SIMPLE_INTERRUPTS_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	/* Use C library with Arduino */
#endif

	void simple_interrupt(uint8_t pin, uint8_t trig, volatile void (*flag));
void simple_debounce(uint8_t, boolean);

#ifdef __cplusplus
}
#endif

#endif
