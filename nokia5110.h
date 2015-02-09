#ifndef _NOKIA5110_H
#define _NOKIA5110_H

#include <Arduino.h>

#ifdef __cplusplus
extern "C" {	// Use C library with Arduino
#endif

enum {
	LCD_C = LOW,
	LCD_D = HIGH,
};

enum screen {
	LCD_MAX_X = 84,
	LCD_MAX_Y = 48,
};

void lcdCharacter(char);
void lcdClear(void);
void lcdInitialize(void);
void lcdString(char const *);
void lcdWrite(byte, byte);

#ifdef __cplusplus
}
#endif

#endif
